TestingGrounds_Exterior1_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TestingGrounds_Exterior1_OnTransition
	.byte 0

TestingGrounds_Exterior1_OnTransition::
	setflag FLAG_TEMP_2 @ Keep the challenger object hidden until one arrives
	end

@ ---------------------------------------------------------------------------
@ Gift NPC: hands out two Normal-type Pokémon that meet the rank 1 gym rules.
@ ---------------------------------------------------------------------------
TestingGrounds_Exterior1_EventScript_GiftNpc::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x020, TestingGrounds_Exterior1_EventScript_GiftAlreadyGiven
	msgbox TestingGrounds_Exterior1_Text_GiftIntro, MSGBOX_DEFAULT
	givemon SPECIES_ZIGZAGOON, 14
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, TestingGrounds_Exterior1_EventScript_GiftNoRoom
	givemon SPECIES_WHISMUR, 14
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, TestingGrounds_Exterior1_EventScript_GiftNoRoom
	setflag FLAG_UNUSED_0x020
	playfanfare MUS_OBTAIN_ITEM
	message TestingGrounds_Exterior1_Text_GiftReceived
	waitfanfare
	waitmessage
	msgbox TestingGrounds_Exterior1_Text_GiftExplainRules, MSGBOX_DEFAULT
	release
	end

TestingGrounds_Exterior1_EventScript_GiftAlreadyGiven::
	msgbox TestingGrounds_Exterior1_Text_GiftPostGift, MSGBOX_DEFAULT
	release
	end

TestingGrounds_Exterior1_EventScript_GiftNoRoom::
	msgbox TestingGrounds_Exterior1_Text_GiftNoRoom, MSGBOX_DEFAULT
	release
	end

@ ---------------------------------------------------------------------------
@ Gym attendant: validates the leader's team, then runs the challenge loop.
@ ---------------------------------------------------------------------------
TestingGrounds_Exterior1_EventScript_GymAttendant::
	lock
	faceplayer
	msgbox TestingGrounds_Exterior1_Text_OpenGymPrompt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, TestingGrounds_Exterior1_EventScript_DeclineOpen
	special GymChallenge_Begin
	switch VAR_RESULT
	case GYM_TEAM_WRONG_SIZE, TestingGrounds_Exterior1_EventScript_TeamWrongSize
	case GYM_TEAM_OVERLEVELED, TestingGrounds_Exterior1_EventScript_TeamOverleveled
	case GYM_TEAM_WRONG_TYPE, TestingGrounds_Exterior1_EventScript_TeamWrongType
	msgbox TestingGrounds_Exterior1_Text_GymIsOpen, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_3, 0
TestingGrounds_Exterior1_EventScript_NextChallenger::
	special GymChallenge_PickChallenger
	addobject LOCALID_TESTING_GYM_CHALLENGER
	applymovement LOCALID_TESTING_GYM_CHALLENGER, TestingGrounds_Exterior1_Movement_ChallengerEnter
	waitmovement 0
	switch VAR_RESULT
	case 0, TestingGrounds_Exterior1_EventScript_IntroBenny
	case 1, TestingGrounds_Exterior1_EventScript_IntroDino
	case 2, TestingGrounds_Exterior1_EventScript_IntroRika
	case 3, TestingGrounds_Exterior1_EventScript_IntroTommy
TestingGrounds_Exterior1_EventScript_DoChallengeBattle::
	special HealPlayerParty
	special GymChallenge_StartBattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, TestingGrounds_Exterior1_EventScript_LeaderLost
	msgbox TestingGrounds_Exterior1_Text_ChallengerDefeated, MSGBOX_DEFAULT
	special GymChallenge_AwardVictoryPoints
	playfanfare MUS_OBTAIN_B_POINTS
	message TestingGrounds_Exterior1_Text_EarnedGymPoints
	waitfanfare
	waitmessage
	goto_if_eq VAR_RESULT, TRUE, TestingGrounds_Exterior1_EventScript_AnnounceBarFilled
TestingGrounds_Exterior1_EventScript_ChallengerLeaves::
	closemessage
	applymovement LOCALID_TESTING_GYM_CHALLENGER, TestingGrounds_Exterior1_Movement_ChallengerExit
	waitmovement 0
	removeobject LOCALID_TESTING_GYM_CHALLENGER
	addvar VAR_TEMP_3, 1
	goto_if_ne VAR_TEMP_3, GYM_RANK1_NUM_CHALLENGES, TestingGrounds_Exterior1_EventScript_AnnounceNext
	special GymChallenge_End
	special HealPlayerParty
	msgbox TestingGrounds_Exterior1_Text_GymDayComplete, MSGBOX_DEFAULT
	special GymChallenge_IsRankUpUnlocked
	goto_if_eq VAR_RESULT, TRUE, TestingGrounds_Exterior1_EventScript_ExamReminder
	release
	end

TestingGrounds_Exterior1_EventScript_AnnounceBarFilled::
	msgbox TestingGrounds_Exterior1_Text_BarFilled, MSGBOX_DEFAULT
	goto TestingGrounds_Exterior1_EventScript_ChallengerLeaves

TestingGrounds_Exterior1_EventScript_ExamReminder::
	msgbox TestingGrounds_Exterior1_Text_ExamAvailable, MSGBOX_DEFAULT
	release
	end

TestingGrounds_Exterior1_EventScript_AnnounceNext::
	msgbox TestingGrounds_Exterior1_Text_NextChallengerArrived, MSGBOX_DEFAULT
	closemessage
	goto TestingGrounds_Exterior1_EventScript_NextChallenger

TestingGrounds_Exterior1_EventScript_LeaderLost::
	msgbox TestingGrounds_Exterior1_Text_LeaderLost, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_TESTING_GYM_CHALLENGER, TestingGrounds_Exterior1_Movement_ChallengerExit
	waitmovement 0
	removeobject LOCALID_TESTING_GYM_CHALLENGER
	special GymChallenge_End
	special HealPlayerParty
	msgbox TestingGrounds_Exterior1_Text_GymClosedAfterLoss, MSGBOX_DEFAULT
	release
	end

TestingGrounds_Exterior1_EventScript_IntroBenny::
	msgbox TestingGrounds_Exterior1_Text_IntroBenny, MSGBOX_DEFAULT
	goto TestingGrounds_Exterior1_EventScript_DoChallengeBattle

TestingGrounds_Exterior1_EventScript_IntroDino::
	msgbox TestingGrounds_Exterior1_Text_IntroDino, MSGBOX_DEFAULT
	goto TestingGrounds_Exterior1_EventScript_DoChallengeBattle

TestingGrounds_Exterior1_EventScript_IntroRika::
	msgbox TestingGrounds_Exterior1_Text_IntroRika, MSGBOX_DEFAULT
	goto TestingGrounds_Exterior1_EventScript_DoChallengeBattle

TestingGrounds_Exterior1_EventScript_IntroTommy::
	msgbox TestingGrounds_Exterior1_Text_IntroTommy, MSGBOX_DEFAULT
	goto TestingGrounds_Exterior1_EventScript_DoChallengeBattle

TestingGrounds_Exterior1_EventScript_DeclineOpen::
	msgbox TestingGrounds_Exterior1_Text_ComeBackAnytime, MSGBOX_DEFAULT
	release
	end

TestingGrounds_Exterior1_EventScript_TeamWrongSize::
	msgbox TestingGrounds_Exterior1_Text_TeamWrongSize, MSGBOX_DEFAULT
	release
	end

TestingGrounds_Exterior1_EventScript_TeamOverleveled::
	msgbox TestingGrounds_Exterior1_Text_TeamOverleveled, MSGBOX_DEFAULT
	release
	end

TestingGrounds_Exterior1_EventScript_TeamWrongType::
	msgbox TestingGrounds_Exterior1_Text_TeamWrongType, MSGBOX_DEFAULT
	release
	end

TestingGrounds_Exterior1_Movement_ChallengerEnter:
	walk_down
	walk_down
	step_end

TestingGrounds_Exterior1_Movement_ChallengerExit:
	walk_up
	walk_up
	step_end

TestingGrounds_Exterior1_Text_GiftIntro:
	.string "Ah, our new GYM LEADER!\p"
	.string "A LEADER needs POKéMON that follow\n"
	.string "the GYM rules. Take these two!$"

TestingGrounds_Exterior1_Text_GiftReceived:
	.string "{PLAYER} received ZIGZAGOON\n"
	.string "and WHISMUR!$"

TestingGrounds_Exterior1_Text_GiftExplainRules:
	.string "At rank 1, your GYM allows up to two\n"
	.string "NORMAL-type POKéMON at level 15\l"
	.string "or below.\p"
	.string "Keep only those two in your party,\n"
	.string "then speak to the attendant to open\l"
	.string "your GYM!$"

TestingGrounds_Exterior1_Text_GiftPostGift:
	.string "How are your POKéMON doing?\p"
	.string "Defend your GYM well and it will\n"
	.string "grow in rank!$"

TestingGrounds_Exterior1_Text_GiftNoRoom:
	.string "Oh! You have no room for them.\n"
	.string "Come back when you've made space.$"

TestingGrounds_Exterior1_Text_OpenGymPrompt:
	.string "Welcome, GYM LEADER {PLAYER}!\p"
	.string "Shall we open the GYM and accept\n"
	.string "challenges?$"

TestingGrounds_Exterior1_Text_ComeBackAnytime:
	.string "Very well. Come back whenever\n"
	.string "you're ready.$"

TestingGrounds_Exterior1_Text_TeamWrongSize:
	.string "Hmm… At rank 1, a LEADER defends\n"
	.string "with one or two POKéMON.\p"
	.string "Please adjust your party and\n"
	.string "come back.$"

TestingGrounds_Exterior1_Text_TeamOverleveled:
	.string "Hmm… At rank 1, your POKéMON must\n"
	.string "be level 15 or below.\p"
	.string "Please adjust your party and\n"
	.string "come back.$"

TestingGrounds_Exterior1_Text_TeamWrongType:
	.string "Hmm… This is a NORMAL-type GYM.\p"
	.string "Every POKéMON on your team must be\n"
	.string "NORMAL type. Please adjust your\l"
	.string "party and come back.$"

TestingGrounds_Exterior1_Text_GymIsOpen:
	.string "The GYM is now open!\p"
	.string "Three TRAINERS signed up to\n"
	.string "challenge you today.\p"
	.string "Here comes the first one!$"

TestingGrounds_Exterior1_Text_IntroBenny:
	.string "{STR_VAR_1}: So you're the new GYM\n"
	.string "LEADER?\p"
	.string "My POOCHYENA and I are gonna take\n"
	.string "your badge, mister!$"

TestingGrounds_Exterior1_Text_IntroDino:
	.string "{STR_VAR_1}: I found sooo many BUG\n"
	.string "POKéMON in the woods!\p"
	.string "Let's see them squish your\n"
	.string "NORMAL types!$"

TestingGrounds_Exterior1_Text_IntroRika:
	.string "{STR_VAR_1}: A NORMAL-type GYM?\p"
	.string "My FIGHTING-type POKéMON have the\n"
	.string "clear advantage. Prepare yourself!$"

TestingGrounds_Exterior1_Text_IntroTommy:
	.string "{STR_VAR_1}: I studied all about\n"
	.string "type matchups in school!\p"
	.string "Today's lesson: beating a GYM\n"
	.string "LEADER!$"

TestingGrounds_Exterior1_Text_EarnedGymPoints:
	.string "{PLAYER} earned {STR_VAR_1} GYM POINTS!$"

TestingGrounds_Exterior1_Text_BarFilled:
	.string "ATTENDANT: Incredible!\p"
	.string "Your GYM's reputation has reached\n"
	.string "its peak for this rank!\p"
	.string "You may take the RANK-UP EXAM\n"
	.string "whenever you feel ready!$"

TestingGrounds_Exterior1_Text_ExamAvailable:
	.string "ATTENDANT: Remember, the RANK-UP\n"
	.string "EXAM awaits whenever you're ready!$"

TestingGrounds_Exterior1_Text_ChallengerDefeated:
	.string "{STR_VAR_1}: Aww… You really are\n"
	.string "the GYM LEADER!\p"
	.string "I'll train harder and challenge\n"
	.string "you again!$"

TestingGrounds_Exterior1_Text_NextChallengerArrived:
	.string "ATTENDANT: Well defended!\p"
	.string "Your POKéMON have been healed.\n"
	.string "The next challenger has arrived!$"

TestingGrounds_Exterior1_Text_LeaderLost:
	.string "{STR_VAR_1}: I… I won?!\p"
	.string "I beat a GYM LEADER! Wait till\n"
	.string "everyone hears about this!$"

TestingGrounds_Exterior1_Text_GymClosedAfterLoss:
	.string "ATTENDANT: Oh no…\p"
	.string "We'll close the GYM for today.\n"
	.string "Rest up and try again tomorrow!$"

TestingGrounds_Exterior1_Text_GymDayComplete:
	.string "ATTENDANT: That was the last\n"
	.string "challenger for today!\p"
	.string "You defended your GYM perfectly,\n"
	.string "LEADER {PLAYER}!\p"
	.string "Keep this up and the GYM's rank\n"
	.string "will surely rise!$"
