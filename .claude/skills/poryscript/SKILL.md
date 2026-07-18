---
name: poryscript
description: Write and edit game event scripts using Poryscript (.pory files), the high-level scripting language that compiles to pokeemerald event script. Use this skill whenever creating or modifying map scripts, NPC dialogue, cutscenes, trainer interactions, map script tables (mapscripts), movement sequences, or any file under data/maps/*/scripts.inc or data/scripts/ — even if the user doesn't say "poryscript". Also use it when asked to convert existing .inc scripts to .pory, or when a build error points at a .pory file.
---

# Poryscript

Poryscript is a higher-level language that compiles to the assembler event-script macros used by this pokeemerald-based project. It provides `if`/`elif`/`else`, `while`, `switch`, inline auto-formatted text, and inline movement — all of which replace the error-prone manual `goto_if_*` label juggling of raw `.inc` scripts.

The compiler lives at `tools/poryscript/` (git submodule, built automatically by `make tools` / the normal build). The build system compiles any `data/**/*.pory` file to a sibling `.inc` file automatically during `make`.

## The one critical rule

**Once a `.pory` file exists, its `.inc` sibling is generated output.** The Makefile rule regenerates `data/X/scripts.inc` from `data/X/scripts.pory` on every build, silently overwriting any manual edits to the `.inc`. So:

- If a map has a `scripts.pory` → edit **only** the `.pory`.
- If a map has only a `scripts.inc` → either edit the `.inc` directly (plain event script), or convert it to `.pory` first (see "Converting an existing script" below). Never create a `.pory` alongside an `.inc` without absorbing the `.inc`'s content into it — the next build would wipe the `.inc`.
- No build wiring changes are ever needed: `data/event_scripts.s` includes the `.inc` path, and that keeps working because the `.pory` compiles to that same path.

## Workflow

1. **Write/edit the `.pory` file** (e.g. `data/maps/MyMap/scripts.pory`).
2. **Validate it compiles** without running a full build:
   ```bash
   ./tools/poryscript/poryscript -i path/to/scripts.pory \
       -fc tools/poryscript/font_config.json \
       -cc tools/poryscript/command_config.json > /dev/null
   ```
   Errors print to stderr with line numbers. Drop `> /dev/null` to inspect the generated output (add `-lm=false` to suppress line markers for readability).
3. **Build**: a normal `make` regenerates the `.inc` and compiles the ROM. `make generated` regenerates all auto-generated files (including `.pory` → `.inc`) without a full build.
4. Generated `.inc` files are currently tracked in git — commit the regenerated `.inc` together with the `.pory`.

If the compiler binary is missing (fresh clone), run `git submodule update --init` then `make tools` (or `cd tools/poryscript && go build`).

## Syntax quick reference

A `.pory` file is a list of top-level statements: `script`, `text`, `movement`, `mart`, `mapscripts`, `raw`, and `const`. Comments are `#` or `//` (not allowed inside `raw`).

```pory
mapscripts MyMap_MapScripts {
    MAP_SCRIPT_ON_TRANSITION: MyMap_OnTransition   // label form
    MAP_SCRIPT_ON_RESUME {                          // inline form
        setflag(FLAG_TEMP_1)
    }
    MAP_SCRIPT_ON_FRAME_TABLE [                     // table types use [ ]
        VAR_TEMP_0, 0: MyMap_OnFrame_0
    ]
}
// Map with no map scripts: mapscripts MyMap_MapScripts {}

script MyMap_EventScript_Npc {
    lock
    faceplayer
    if (flag(FLAG_GOT_ITEM)) {
        msgbox("Already gave you one.")
    } elif (var(VAR_BADGES) >= 3 && !defeated(TRAINER_FOO)) {
        msgbox("Want this?", MSGBOX_YESNO)
        if (var(VAR_RESULT) == YES) {
            giveitem(ITEM_POTION)
            setflag(FLAG_GOT_ITEM)
        }
    } else {
        // Multi-line string: line breaks (\n, \l, \p) inserted automatically.
        // A blank line starts a new paragraph (\p).
        msgbox("Come back when you have
                three badges.")
    }
    release
    end
}

script MyMap_EventScript_Walker {
    lock
    applymovement(OBJ_EVENT_ID_PLAYER, moves(walk_left, walk_up * 3, face_down))
    waitmovement(0)
    release
}

text MyMap_Text_Shared {
    format("format() auto-wraps long prose to the textbox width. Use it for long text instead of guessing line breaks.")
}
```

Key points:

- **Commands with arguments use parentheses**: `msgbox("Hi.")`, `setvar(VAR_TEMP_0, 1)`. Bare commands need none: `lock`, `release`, `end`. The available commands are the macros in `asm/macros/event.inc`; specials are listed in `data/specials.inc`; flags/vars in `include/constants/flags.h` / `vars.h`; movement actions in `asm/macros/movement.inc`.
- **Conditions**: left side must be `flag(...)`, `var(...)`, `defeated(...)`, or an autovar command. `flag`/`defeated` compare only with `==`/`!=` truthiness; `var` supports `==, !=, <, <=, >, >=`. Implicit truthiness works: `if (flag(FLAG_X))`, `if (!var(VAR_X))`. Combine with `&&`, `||`, parentheses.
- **Autovars** streamline commands that store a result in `VAR_RESULT`: write `if (checkitem(ITEM_ROOT_FOSSIL))` instead of `checkitem` + `compare`. Configured commands (see `tools/poryscript/command_config.json`): `checkitem`, `checkitemspace`, `checkpcitem`, `random`, `getpartysize`, `checkpartymove`, `additem`, `removeitem`, `givemon`, `giveegg`, `checkplayergender`, `checkmoney`, `checkcoins`, `yesnobox`, `multichoice`, `multichoicedefault`, `multichoicegrid`, `specialvar`, `dowildbattle`, and more.
- **`switch` requires a `var()`** (or autovar) subject; cases break implicitly, no fall-through; multiple `case X:` lines stack; `default:` supported.
- **Loops**: `while (cond) { }`, bare `while { }` (infinite), `do { } while (cond)`, with `break`/`continue`.
- **Strings**: one multi-line quoted string auto-inserts `\n`/`\l`/`\p` (blank line = `\p`). Adjacent single-line strings concatenate with manual control (`"line one\n" "line two"`). `format("...")` wraps text to textbox width — the idiomatic form for long dialogue is inline: `msgbox(format("One long single-line string of prose..."))`. It cannot wrap an auto (multi-line) string — pick one style per string. Poryscript appends the `$` terminator itself.
- **Text replacements** (from `font_config.json`): `\e`→é, `\.`→…, `\m`→♂, `\f`→♀, `\qo`/`\qc`→curly quotes, `\h30`→`{PAUSE_30}`.
- **`movement`** blocks and inline `moves(...)` support `command * count` repetition; `step_end` is added automatically.
- **`mart`** defines a `pokemart` item list; `ITEM_NONE` terminator is added automatically.
- **`raw` \`...\`** passes assembler text through verbatim — for data poryscript can't express.
- **`const NAME = value`** for readable local-object IDs etc.; must be defined before use. Constants substitute into any command parameter and into condition operands/values (e.g. `applymovement(LOCALID_BOY, ...)`).
- **Scope**: `script`, `text`, `mapscripts` default to global (`::`); `movement`, `mart` default local. Override with `script(local)` / `movement(global)`.
- **Labels** inside a script: `MyLabel:` on its own line, targetable with `goto(MyLabel)`. Rarely needed given `if`/`switch`.

Naming convention: follow the repo's existing pattern — `MapName_EventScript_Description`, `MapName_Text_Description`, `MapName_MapScripts`, `MapName_Movement_Description`.

For anything beyond this summary (compile-time `poryswitch`, custom text encoding, `format()` named parameters like `numLines=`/`maxLineLength=`, font config details), read `tools/poryscript/README.md`.

## Converting an existing script to Poryscript

To migrate a map that only has `scripts.inc`:

1. Create `scripts.pory` in the same directory containing the entire old `.inc` wrapped in a raw block:
   ```pory
   raw `
   <entire contents of scripts.inc>
   `
   ```
   (The content passes through verbatim — existing `@` assembler comments are fine, but Poryscript `#`/`//` comments aren't recognized inside `raw`, and the content must not contain a backtick.)
2. Verify it compiles (step 2 of the workflow) — output should match the old `.inc` modulo line markers.
3. Migrate scripts out of the `raw` block into real `script`/`text`/`movement` statements incrementally, as needed. Full conversion is optional; mixing `raw` and native statements is fine.

When writing the compiled logic yourself would produce `goto_if_set FLAG_X, Label` chains, that's the signal the script belongs in Poryscript — write `if (flag(FLAG_X))` instead.

## Debugging

- **The validation command only checks Poryscript syntax — it does not resolve symbols.** An unknown flag, var, item, command, or trainer constant (e.g. a made-up `VAR_BADGES`) compiles fine but fails later during `make` at the assembler step with an undefined-symbol error. Always confirm constants exist in the headers listed above before using them.
- Compile errors name the `.pory` line: `line X: <message>`. Common causes: missing parentheses on a command with args, a bare expression on the left of a condition (must be `flag()`/`var()`/`defeated()`/autovar), `format()` around a multi-line auto string, comments inside `raw`.
- ROM build errors that reference a `.pory` line work because of the emitted line markers — fix the `.pory`, not the `.inc`.
- To see exactly what a construct compiles to, pipe a snippet through the compiler from stdin:
  ```bash
  echo 'script T { if (var(VAR_TEMP_0) == 2) { end } }' | \
      ./tools/poryscript/poryscript -fc tools/poryscript/font_config.json \
      -cc tools/poryscript/command_config.json -lm=false
  ```
