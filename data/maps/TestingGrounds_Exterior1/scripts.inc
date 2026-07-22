TestingGrounds_Exterior1_MapScripts::
# 5 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, TestingGrounds_Exterior1_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

TestingGrounds_Exterior1_MapScripts_MAP_SCRIPT_ON_TRANSITION:
# 6 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	setflag FLAG_TEMP_2
	return


TestingGrounds_Exterior1_EventScript_GiftNpc::
# 15 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	lock
# 16 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	faceplayer
# 17 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	goto_if_set FLAG_UNUSED_0x020, TestingGrounds_Exterior1_EventScript_GiftNpc_2
# 24 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_BufferGymProgress
# 25 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_GiftIntro
# 26 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_GiveGymStarters
# 27 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq TestingGrounds_Exterior1_EventScript_GiftNpc_5
# 32 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	setflag FLAG_UNUSED_0x020
# 33 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 34 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 35 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	message TestingGrounds_Exterior1_Text_GiftReceived
# 36 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	waitfanfare
# 37 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	waitmessage
# 38 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_AssignSignatureTM
# 39 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq TestingGrounds_Exterior1_EventScript_GiftNpc_8
# 46 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_SignatureTMNoRoom
TestingGrounds_Exterior1_EventScript_GiftNpc_7:
# 48 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_BufferRankInfo
# 49 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_GiftExplainRules
# 50 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	release
	end

TestingGrounds_Exterior1_EventScript_GiftNpc_2:
# 19 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_AssignSignatureTM
# 20 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_GiftPostGift
# 21 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	release
	end

TestingGrounds_Exterior1_EventScript_GiftNpc_5:
# 28 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_GiftNoRoom
# 29 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	release
	end

TestingGrounds_Exterior1_EventScript_GiftNpc_8:
# 40 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	playfanfare MUS_OBTAIN_TMHM
# 41 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	message TestingGrounds_Exterior1_Text_ReceivedSignatureTM
# 42 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	waitfanfare
# 43 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	waitmessage
# 44 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_ExplainSignatureTM
	goto TestingGrounds_Exterior1_EventScript_GiftNpc_7


TestingGrounds_Exterior1_EventScript_GymAttendant::
# 61 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	lock
# 62 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	faceplayer
# 63 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_OpenGymPrompt, MSGBOX_YESNO
# 64 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, NO
	goto_if_eq TestingGrounds_Exterior1_EventScript_GymAttendant_2
# 69 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	message TestingGrounds_Exterior1_Text_ChooseTeamSource
# 70 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	waitmessage
# 71 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	dynmultichoice 0, 0, FALSE, 7, 0, DYN_MULTICHOICE_CB_NONE, TestingGrounds_Exterior1_Text_SourceParty, TestingGrounds_Exterior1_Text_Team1, TestingGrounds_Exterior1_Text_Team2, TestingGrounds_Exterior1_Text_Team3, TestingGrounds_Exterior1_Text_Team4, TestingGrounds_Exterior1_Text_Team5, TestingGrounds_Exterior1_Text_SourceCancel
# 79 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, MULTI_B_PRESSED
	goto_if_eq TestingGrounds_Exterior1_EventScript_GymAttendant_5
# 79 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, 6
	goto_if_eq TestingGrounds_Exterior1_EventScript_GymAttendant_5
# 84 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq TestingGrounds_Exterior1_EventScript_GymAttendant_10
# 87 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	copyvar VAR_0x8004, VAR_RESULT
# 88 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	subvar VAR_0x8004, 1
# 89 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymTeams_LoadTeamIntoParty
# 90 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq TestingGrounds_Exterior1_EventScript_GymAttendant_16
TestingGrounds_Exterior1_EventScript_GymAttendant_9:
# 96 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_BufferRankInfo
# 97 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_PickDefenders
# 98 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	fadescreen FADE_TO_BLACK
# 99 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_ChooseGymParty
# 100 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq TestingGrounds_Exterior1_EventScript_GymAttendant_14
# 106 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special ReducePlayerPartyToSelectedMons
# 107 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_Begin
# 108 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	switch VAR_RESULT
# 109 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	case GYM_TEAM_WRONG_SIZE, TestingGrounds_Exterior1_EventScript_GymAttendant_20
# 115 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	case GYM_TEAM_OVERLEVELED, TestingGrounds_Exterior1_EventScript_GymAttendant_21
# 121 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	case GYM_TEAM_WRONG_TYPE, TestingGrounds_Exterior1_EventScript_GymAttendant_22
# 128 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_GymIsOpen
# 129 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_GetStreakTier
# 130 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	switch VAR_RESULT
# 131 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	case 0, TestingGrounds_Exterior1_EventScript_GymAttendant_25
# 132 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	case 1, TestingGrounds_Exterior1_EventScript_GymAttendant_26
# 133 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	case 2, TestingGrounds_Exterior1_EventScript_GymAttendant_27
# 134 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	case 3, TestingGrounds_Exterior1_EventScript_GymAttendant_28
TestingGrounds_Exterior1_EventScript_GymAttendant_23:
# 136 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	closemessage
# 137 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	setvar VAR_TEMP_3, 0
TestingGrounds_Exterior1_EventScript_GymAttendant_30:
# 138 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_TEMP_3, GYM_NUM_CHALLENGES_PER_WAVE
	goto_if_lt TestingGrounds_Exterior1_EventScript_GymAttendant_31
# 186 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_End
# 187 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special LoadPlayerParty
# 188 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special HealPlayerParty
# 189 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_GymDayComplete
# 190 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_IsRankUpUnlocked
# 191 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq TestingGrounds_Exterior1_EventScript_GymAttendant_34
TestingGrounds_Exterior1_EventScript_GymAttendant_33:
# 194 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	release
	end

TestingGrounds_Exterior1_EventScript_GymAttendant_2:
# 65 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_ComeBackAnytime
# 66 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	release
	end

TestingGrounds_Exterior1_EventScript_GymAttendant_5:
# 80 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_ComeBackAnytime
# 81 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	release
	end

TestingGrounds_Exterior1_EventScript_GymAttendant_10:
# 85 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special SavePlayerParty
	goto TestingGrounds_Exterior1_EventScript_GymAttendant_9

TestingGrounds_Exterior1_EventScript_GymAttendant_14:
# 101 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special LoadPlayerParty
# 102 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_ComeBackAnytime
# 103 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	release
	end

TestingGrounds_Exterior1_EventScript_GymAttendant_16:
# 91 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_TeamUnavailable
# 92 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	release
	end

TestingGrounds_Exterior1_EventScript_GymAttendant_20:
# 110 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special LoadPlayerParty
# 111 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_BufferRankInfo
# 112 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_TeamWrongSize
# 113 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	release
	end

TestingGrounds_Exterior1_EventScript_GymAttendant_21:
# 116 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special LoadPlayerParty
# 117 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_BufferRankInfo
# 118 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_TeamOverleveled
# 119 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	release
	end

TestingGrounds_Exterior1_EventScript_GymAttendant_22:
# 122 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special LoadPlayerParty
# 123 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_BufferGymProgress
# 124 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_TeamWrongType
# 125 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	release
	end

TestingGrounds_Exterior1_EventScript_GymAttendant_25:
# 131 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_StreakPhraseCalm
	goto TestingGrounds_Exterior1_EventScript_GymAttendant_23

TestingGrounds_Exterior1_EventScript_GymAttendant_26:
# 132 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_StreakPhraseStirring
	goto TestingGrounds_Exterior1_EventScript_GymAttendant_23

TestingGrounds_Exterior1_EventScript_GymAttendant_27:
# 133 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_StreakPhraseSpreading
	goto TestingGrounds_Exterior1_EventScript_GymAttendant_23

TestingGrounds_Exterior1_EventScript_GymAttendant_28:
# 134 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_StreakPhrasePeak
	goto TestingGrounds_Exterior1_EventScript_GymAttendant_23

TestingGrounds_Exterior1_EventScript_GymAttendant_31:
# 139 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_TEMP_3, 0
	goto_if_gt TestingGrounds_Exterior1_EventScript_GymAttendant_37
TestingGrounds_Exterior1_EventScript_GymAttendant_36:
# 143 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_PickChallenger
# 144 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	addobject LOCALID_TESTING_GYM_CHALLENGER
# 145 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	applymovement LOCALID_TESTING_GYM_CHALLENGER, TestingGrounds_Exterior1_EventScript_GymAttendant_Movement_0
# 146 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	waitmovement 0
# 147 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_0x8006, GYM_TIER_STRONG
	goto_if_eq TestingGrounds_Exterior1_EventScript_GymAttendant_40
TestingGrounds_Exterior1_EventScript_GymAttendant_39:
# 152 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_BufferChallengerIntro
# 153 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox gStringVar4
# 154 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special HealPlayerParty
# 155 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_StartBattle
# 156 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 157 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_ne TestingGrounds_Exterior1_EventScript_GymAttendant_43
# 171 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_ChallengerDefeated
# 172 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_AwardVictoryPoints
# 173 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	playfanfare MUS_OBTAIN_B_POINTS
# 174 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	message TestingGrounds_Exterior1_Text_EarnedGymPoints
# 175 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	waitfanfare
# 176 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	waitmessage
# 177 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq TestingGrounds_Exterior1_EventScript_GymAttendant_46
TestingGrounds_Exterior1_EventScript_GymAttendant_45:
# 180 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	closemessage
# 181 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	applymovement LOCALID_TESTING_GYM_CHALLENGER, TestingGrounds_Exterior1_EventScript_GymAttendant_Movement_1
# 182 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	waitmovement 0
# 183 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	removeobject LOCALID_TESTING_GYM_CHALLENGER
# 184 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	addvar VAR_TEMP_3, 1
	goto TestingGrounds_Exterior1_EventScript_GymAttendant_30

TestingGrounds_Exterior1_EventScript_GymAttendant_34:
# 192 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_ExamAvailable
	goto TestingGrounds_Exterior1_EventScript_GymAttendant_33

TestingGrounds_Exterior1_EventScript_GymAttendant_37:
# 140 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_NextChallengerArrived
# 141 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	closemessage
	goto TestingGrounds_Exterior1_EventScript_GymAttendant_36

TestingGrounds_Exterior1_EventScript_GymAttendant_40:
# 148 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_StrongChallengerWarning
# 149 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	closemessage
	goto TestingGrounds_Exterior1_EventScript_GymAttendant_39

TestingGrounds_Exterior1_EventScript_GymAttendant_43:
# 158 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_RecordLoss
# 159 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_LeaderLost
# 160 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	closemessage
# 161 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	applymovement LOCALID_TESTING_GYM_CHALLENGER, TestingGrounds_Exterior1_EventScript_GymAttendant_Movement_1
# 162 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	waitmovement 0
# 163 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	removeobject LOCALID_TESTING_GYM_CHALLENGER
# 164 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_End
# 165 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special LoadPlayerParty
# 166 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special HealPlayerParty
# 167 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_GymClosedAfterLoss
# 168 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	release
	end

TestingGrounds_Exterior1_EventScript_GymAttendant_46:
# 178 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_BarFilled
	goto TestingGrounds_Exterior1_EventScript_GymAttendant_45


TestingGrounds_Exterior1_EventScript_TeamKeeper::
# 203 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	lock
# 204 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	faceplayer
# 205 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_TeamKeeperIntro
TestingGrounds_Exterior1_EventScript_TeamKeeper_2:
# 207 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	message TestingGrounds_Exterior1_Text_ChooseTeam
# 208 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	waitmessage
# 209 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	dynmultichoice 0, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, TestingGrounds_Exterior1_Text_Team1, TestingGrounds_Exterior1_Text_Team2, TestingGrounds_Exterior1_Text_Team3, TestingGrounds_Exterior1_Text_Team4, TestingGrounds_Exterior1_Text_Team5, TestingGrounds_Exterior1_Text_TeamMenuExit
# 216 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, MULTI_B_PRESSED
	goto_if_eq TestingGrounds_Exterior1_EventScript_TeamKeeper_5
# 216 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, GYM_NUM_SAVED_TEAMS
	goto_if_eq TestingGrounds_Exterior1_EventScript_TeamKeeper_5
# 219 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	copyvar VAR_0x8004, VAR_RESULT
# 220 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	copyvar VAR_TEMP_1, VAR_RESULT
# 221 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	addvar VAR_TEMP_1, 1
# 222 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	buffernumberstring STR_VAR_2, VAR_TEMP_1
# 223 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymTeams_BufferTeam
# 224 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq TestingGrounds_Exterior1_EventScript_TeamKeeper_10
# 227 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_TeamMembers
TestingGrounds_Exterior1_EventScript_TeamKeeper_9:
# 229 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	closemessage
# 230 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, TestingGrounds_Exterior1_Text_TeamActionRegister, TestingGrounds_Exterior1_Text_TeamActionClear, TestingGrounds_Exterior1_Text_TeamActionBack
# 234 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	switch VAR_RESULT
# 235 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	case 0, TestingGrounds_Exterior1_EventScript_TeamKeeper_14
# 238 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	case 1, TestingGrounds_Exterior1_EventScript_TeamKeeper_15
	goto TestingGrounds_Exterior1_EventScript_TeamKeeper_2

TestingGrounds_Exterior1_EventScript_TeamKeeper_1:
# 243 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_TeamKeeperBye
# 244 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	release
	end

TestingGrounds_Exterior1_EventScript_TeamKeeper_5:
	goto TestingGrounds_Exterior1_EventScript_TeamKeeper_1

TestingGrounds_Exterior1_EventScript_TeamKeeper_10:
# 225 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_TeamEmpty
	goto TestingGrounds_Exterior1_EventScript_TeamKeeper_9

TestingGrounds_Exterior1_EventScript_TeamKeeper_14:
# 236 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymTeams_RegisterParty
# 237 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_TeamRegistered
	goto TestingGrounds_Exterior1_EventScript_TeamKeeper_2

TestingGrounds_Exterior1_EventScript_TeamKeeper_15:
# 239 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymTeams_ClearTeam
# 240 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_TeamCleared
	goto TestingGrounds_Exterior1_EventScript_TeamKeeper_2


TestingGrounds_Exterior1_EventScript_RankExaminer::
# 253 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	lock
# 254 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	faceplayer
# 255 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_BufferRankInfo
# 256 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_RankInfo
# 257 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_BufferSignatureMove
# 258 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_SignatureMoveInfo
# 259 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_GYM_RANK, 3
	goto_if_ge TestingGrounds_Exterior1_EventScript_RankExaminer_2
TestingGrounds_Exterior1_EventScript_RankExaminer_1:
# 262 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_BufferGymProgress
# 263 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_GymProgress
# 264 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_BufferStreak
# 265 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_StreakInfo
# 266 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_CanUpgradeSignatureTM
# 267 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq TestingGrounds_Exterior1_EventScript_RankExaminer_5
TestingGrounds_Exterior1_EventScript_RankExaminer_4:
# 293 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_IsRankUpUnlocked
# 294 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq TestingGrounds_Exterior1_EventScript_RankExaminer_8
TestingGrounds_Exterior1_EventScript_RankExaminer_7:
# 297 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_GYM_RANK, GYM_RANK_MAX
	goto_if_ge TestingGrounds_Exterior1_EventScript_RankExaminer_15
# 302 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_TestRankUpPrompt, MSGBOX_YESNO
# 303 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq TestingGrounds_Exterior1_EventScript_RankExaminer_20
TestingGrounds_Exterior1_EventScript_RankExaminer_19:
# 308 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	release
	end

TestingGrounds_Exterior1_EventScript_RankExaminer_2:
# 260 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_OffTypeInfo
	goto TestingGrounds_Exterior1_EventScript_RankExaminer_1

TestingGrounds_Exterior1_EventScript_RankExaminer_5:
# 268 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_UpgradeOffer
# 269 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	message TestingGrounds_Exterior1_Text_UpgradeChoosePrompt
# 270 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	waitmessage
# 271 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_BufferSignatureUpgradeChoices
# 272 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, gStringVar1, gStringVar2, TestingGrounds_Exterior1_Text_UpgradeLater
# 276 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq TestingGrounds_Exterior1_EventScript_RankExaminer_10
# 276 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq TestingGrounds_Exterior1_EventScript_RankExaminer_10
	goto TestingGrounds_Exterior1_EventScript_RankExaminer_4

TestingGrounds_Exterior1_EventScript_RankExaminer_8:
# 295 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_ExamUnlockedNote
	goto TestingGrounds_Exterior1_EventScript_RankExaminer_7

TestingGrounds_Exterior1_EventScript_RankExaminer_10:
# 277 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	copyvar VAR_0x8004, VAR_RESULT
# 278 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_UpgradeConfirmWarn, MSGBOX_YESNO
# 279 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq TestingGrounds_Exterior1_EventScript_RankExaminer_17
	goto TestingGrounds_Exterior1_EventScript_RankExaminer_4

TestingGrounds_Exterior1_EventScript_RankExaminer_15:
# 298 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_MaxRank
# 299 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	release
	end

TestingGrounds_Exterior1_EventScript_RankExaminer_17:
# 280 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_UpgradeSignatureTM
# 281 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq TestingGrounds_Exterior1_EventScript_RankExaminer_22
# 288 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_SignatureTMNoRoom
	goto TestingGrounds_Exterior1_EventScript_RankExaminer_4

TestingGrounds_Exterior1_EventScript_RankExaminer_20:
# 304 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_RankUp
# 305 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_BufferRankInfo
# 306 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_RankedUp
	goto TestingGrounds_Exterior1_EventScript_RankExaminer_19

TestingGrounds_Exterior1_EventScript_RankExaminer_22:
# 282 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	playfanfare MUS_OBTAIN_TMHM
# 283 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	message TestingGrounds_Exterior1_Text_UpgradeReceived
# 284 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	waitfanfare
# 285 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	waitmessage
# 286 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_UpgradeDone
	goto TestingGrounds_Exterior1_EventScript_RankExaminer_4


# 145 "data/maps/TestingGrounds_Exterior1/scripts.pory"
TestingGrounds_Exterior1_EventScript_GymAttendant_Movement_0:
# 145 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	walk_down
# 145 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	walk_down
	step_end

# 161 "data/maps/TestingGrounds_Exterior1/scripts.pory"
TestingGrounds_Exterior1_EventScript_GymAttendant_Movement_1:
# 161 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	walk_up
# 161 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	walk_up
	step_end

TestingGrounds_Exterior1_Text_GiftIntro::
# 312 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Ah, our new GYM LEADER!\p"
	.string "A LEADER needs POKéMON of the GYM's\n"
	.string "own type.\p"
	.string "Take these three {STR_VAR_1}-type\n"
	.string "partners!$"

TestingGrounds_Exterior1_Text_GiftReceived::
# 320 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "{PLAYER} received three\n"
	.string "{STR_VAR_1}-type POKéMON!$"

TestingGrounds_Exterior1_Text_GiftExplainRules::
# 325 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "At rank {STR_VAR_1}, you defend with\n"
	.string "{STR_VAR_3} POKéMON at level {STR_VAR_2}\l"
	.string "or below.\p"
	.string "Register teams with the TEAM KEEPER,\n"
	.string "then speak to the attendant to open\l"
	.string "your GYM!$"

TestingGrounds_Exterior1_Text_ReceivedSignatureTM::
# 334 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "{PLAYER} received {STR_VAR_2}!$"

TestingGrounds_Exterior1_Text_ExplainSignatureTM::
# 338 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "That TM teaches {STR_VAR_3} -\n"
	.string "your GYM's signature move!\p"
	.string "One day, outsider POKéMON that\n"
	.string "learn it may fight by your side.$"

TestingGrounds_Exterior1_Text_SignatureTMNoRoom::
# 345 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Oh! There's no room in your BAG\n"
	.string "for the GYM's signature TM.\p"
	.string "Come see me when you've made\n"
	.string "space.$"

TestingGrounds_Exterior1_Text_GiftPostGift::
# 352 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "How are your POKéMON doing?\p"
	.string "Defend your GYM well and it will\n"
	.string "grow in rank!$"

TestingGrounds_Exterior1_Text_GiftNoRoom::
# 358 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Oh! You don't have room for three\n"
	.string "more POKéMON.\p"
	.string "Come back when you've made space.$"

TestingGrounds_Exterior1_Text_OpenGymPrompt::
# 364 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Welcome, GYM LEADER {PLAYER}!\p"
	.string "Shall we open the GYM and accept\n"
	.string "challenges?$"

TestingGrounds_Exterior1_Text_ComeBackAnytime::
# 370 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Very well. Come back whenever\n"
	.string "you're ready.$"

TestingGrounds_Exterior1_Text_ChooseTeamSource::
# 375 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Who defends the GYM today?$"

TestingGrounds_Exterior1_Text_SourceParty::
# 379 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "CURRENT PARTY$"

TestingGrounds_Exterior1_Text_SourceCancel::
# 383 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "CANCEL$"

TestingGrounds_Exterior1_Text_TeamUnavailable::
# 387 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Hmm… I can't find any of that\n"
	.string "team's members.\p"
	.string "Have they been released or\n"
	.string "traded away?$"

TestingGrounds_Exterior1_Text_PickDefenders::
# 394 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Now, pick the {STR_VAR_3} POKéMON\n"
	.string "that will defend the GYM!$"

TestingGrounds_Exterior1_Text_TeamWrongSize::
# 399 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Hmm… At rank {STR_VAR_1}, a LEADER\n"
	.string "defends with up to {STR_VAR_3} POKéMON.\p"
	.string "Please adjust your party and\n"
	.string "come back.$"

TestingGrounds_Exterior1_Text_TeamOverleveled::
# 406 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Hmm… At rank {STR_VAR_1}, your POKéMON\n"
	.string "must be level {STR_VAR_2} or below.\p"
	.string "Please adjust your party and\n"
	.string "come back.$"

TestingGrounds_Exterior1_Text_TeamWrongType::
# 413 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Hmm… This is a {STR_VAR_1}-type GYM.\p"
	.string "Your team may only include POKéMON\n"
	.string "of the GYM's type, or an outsider\l"
	.string "that knows your signature move.\p"
	.string "Please adjust your party and\n"
	.string "come back.$"

TestingGrounds_Exterior1_Text_GymIsOpen::
# 422 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "The GYM is now open!\p"
	.string "Three TRAINERS signed up to\n"
	.string "challenge you today.\p"
	.string "Here comes the first one!$"

TestingGrounds_Exterior1_Text_StreakPhraseCalm::
# 429 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "ATTENDANT: Mostly first-timers in\n"
	.string "line today.\p"
	.string "A calm day at the GYM, I'd say.$"

TestingGrounds_Exterior1_Text_StreakPhraseStirring::
# 435 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "ATTENDANT: A few familiar faces in\n"
	.string "line today…\p"
	.string "Some of them have clearly been\n"
	.string "training for this.$"

TestingGrounds_Exterior1_Text_StreakPhraseSpreading::
# 442 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "ATTENDANT: Word of your streak is\n"
	.string "spreading, LEADER.\p"
	.string "Serious TRAINERS are starting to\n"
	.string "line up outside.$"

TestingGrounds_Exterior1_Text_StreakPhrasePeak::
# 449 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "ATTENDANT: The line is full of\n"
	.string "hardened TRAINERS today!\p"
	.string "Every one of them has come to end\n"
	.string "your streak. Stay sharp!$"

TestingGrounds_Exterior1_Text_StrongChallengerWarning::
# 456 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "ATTENDANT: Careful, LEADER…\p"
	.string "This one has the look of a real\n"
	.string "contender!$"

TestingGrounds_Exterior1_Text_StreakInfo::
# 462 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Your current win streak:\n"
	.string "{STR_VAR_1} in a row.$"

TestingGrounds_Exterior1_Text_EarnedGymPoints::
# 467 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "{PLAYER} earned {STR_VAR_1} GYM POINTS!$"

TestingGrounds_Exterior1_Text_BarFilled::
# 471 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "ATTENDANT: Incredible!\p"
	.string "Your GYM's reputation has reached\n"
	.string "its peak for this rank!\p"
	.string "You may take the RANK-UP EXAM\n"
	.string "whenever you feel ready!$"

TestingGrounds_Exterior1_Text_ExamAvailable::
# 479 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "ATTENDANT: Remember, the RANK-UP\n"
	.string "EXAM awaits whenever you're ready!$"

TestingGrounds_Exterior1_Text_ChallengerDefeated::
# 484 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "{STR_VAR_1}: Aww… You really are\n"
	.string "the GYM LEADER!\p"
	.string "I'll train harder and challenge\n"
	.string "you again!$"

TestingGrounds_Exterior1_Text_NextChallengerArrived::
# 491 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "ATTENDANT: Well defended!\p"
	.string "Your POKéMON have been healed.\n"
	.string "The next challenger has arrived!$"

TestingGrounds_Exterior1_Text_LeaderLost::
# 497 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "{STR_VAR_1}: I… I won?!\p"
	.string "I beat a GYM LEADER! Wait till\n"
	.string "everyone hears about this!$"

TestingGrounds_Exterior1_Text_GymClosedAfterLoss::
# 503 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "ATTENDANT: Oh no…\p"
	.string "We'll close the GYM for today.\n"
	.string "Rest up and try again tomorrow!$"

TestingGrounds_Exterior1_Text_GymDayComplete::
# 509 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "ATTENDANT: That was the last\n"
	.string "challenger for today!\p"
	.string "You defended your GYM perfectly,\n"
	.string "LEADER {PLAYER}!\p"
	.string "Keep this up and the GYM's rank\n"
	.string "will surely rise!$"

TestingGrounds_Exterior1_Text_TeamKeeperIntro::
# 518 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Hello, LEADER! I keep your\n"
	.string "registered GYM TEAMS.\p"
	.string "A team remembers its members even\n"
	.string "if you move them around the PC.$"

TestingGrounds_Exterior1_Text_ChooseTeam::
# 525 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Which team shall we look at?$"

TestingGrounds_Exterior1_Text_Team1::
# 529 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "TEAM 1$"

TestingGrounds_Exterior1_Text_Team2::
# 533 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "TEAM 2$"

TestingGrounds_Exterior1_Text_Team3::
# 537 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "TEAM 3$"

TestingGrounds_Exterior1_Text_Team4::
# 541 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "TEAM 4$"

TestingGrounds_Exterior1_Text_Team5::
# 545 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "TEAM 5$"

TestingGrounds_Exterior1_Text_TeamMenuExit::
# 549 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "EXIT$"

TestingGrounds_Exterior1_Text_TeamEmpty::
# 553 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "TEAM {STR_VAR_2} is empty.$"

TestingGrounds_Exterior1_Text_TeamMembers::
# 557 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "TEAM {STR_VAR_2}:\p"
	.string "{STR_VAR_1}$"

TestingGrounds_Exterior1_Text_TeamActionRegister::
# 562 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "REGISTER PARTY$"

TestingGrounds_Exterior1_Text_TeamActionClear::
# 566 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "CLEAR TEAM$"

TestingGrounds_Exterior1_Text_TeamActionBack::
# 570 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "BACK$"

TestingGrounds_Exterior1_Text_TeamRegistered::
# 574 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Done! Your current party is now\n"
	.string "TEAM {STR_VAR_2}.$"

TestingGrounds_Exterior1_Text_TeamCleared::
# 579 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "TEAM {STR_VAR_2} has been cleared.$"

TestingGrounds_Exterior1_Text_TeamKeeperBye::
# 583 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Come back anytime, LEADER!$"

TestingGrounds_Exterior1_Text_RankInfo::
# 587 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "EXAMINER: You preside at rank\n"
	.string "{STR_VAR_1}, LEADER.\p"
	.string "Your GYM team may have {STR_VAR_3}\n"
	.string "POKéMON of level {STR_VAR_2} or below.$"

TestingGrounds_Exterior1_Text_SignatureMoveInfo::
# 594 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Your GYM's signature move is\n"
	.string "{STR_VAR_1}.$"

TestingGrounds_Exterior1_Text_OffTypeInfo::
# 599 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "At your rank, one team member may\n"
	.string "be an outsider type…\p"
	.string "…as long as it knows {STR_VAR_1},\n"
	.string "your signature move!$"

TestingGrounds_Exterior1_Text_GymProgress::
# 606 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "You lead a {STR_VAR_1}-type GYM.\p"
	.string "Reputation this rank:\n"
	.string "{STR_VAR_2} of {STR_VAR_3} points.$"

TestingGrounds_Exterior1_Text_UpgradeOffer::
# 612 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Ah, one more thing, LEADER!\p"
	.string "A GYM of your rank may adopt a\n"
	.string "stronger signature move!$"

TestingGrounds_Exterior1_Text_UpgradeChoosePrompt::
# 618 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Which move shall represent\n"
	.string "your GYM?$"

TestingGrounds_Exterior1_Text_UpgradeLater::
# 623 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "LATER$"

TestingGrounds_Exterior1_Text_UpgradeConfirmWarn::
# 627 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Once you adopt the new move, only\n"
	.string "it will count as your signature.\p"
	.string "Outsiders that know only the old\n"
	.string "move will no longer qualify.\p"
	.string "Proceed?$"

TestingGrounds_Exterior1_Text_UpgradeReceived::
# 635 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "{PLAYER} received {STR_VAR_2}!$"

TestingGrounds_Exterior1_Text_UpgradeDone::
# 639 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "{STR_VAR_3} is now your GYM's\n"
	.string "signature move!\p"
	.string "May it strike fear into every\n"
	.string "challenger!$"

TestingGrounds_Exterior1_Text_ExamUnlockedNote::
# 646 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Your reputation is at its peak!\n"
	.string "The RANK-UP EXAM awaits you.$"

TestingGrounds_Exterior1_Text_MaxRank::
# 651 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "You stand at the very top,\n"
	.string "LEADER. There is no higher rank!$"

TestingGrounds_Exterior1_Text_TestRankUpPrompt::
# 656 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "(TEST) Advance to the next rank\n"
	.string "right now?$"

TestingGrounds_Exterior1_Text_RankedUp::
# 661 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Congratulations, LEADER!\p"
	.string "You now preside at rank {STR_VAR_1}!\p"
	.string "New rules: {STR_VAR_3} POKéMON of\n"
	.string "level {STR_VAR_2} or below.$"
