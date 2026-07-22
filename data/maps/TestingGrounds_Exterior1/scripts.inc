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
# 196 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_End
# 197 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special LoadPlayerParty
# 198 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special HealPlayerParty
# 199 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_GymDayComplete
# 200 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_IsRankUpUnlocked
# 201 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq TestingGrounds_Exterior1_EventScript_GymAttendant_34
TestingGrounds_Exterior1_EventScript_GymAttendant_33:
# 204 "data/maps/TestingGrounds_Exterior1/scripts.pory"
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
# 157 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	switch VAR_RESULT
# 158 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	case 0, TestingGrounds_Exterior1_EventScript_GymAttendant_52
# 159 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	case 1, TestingGrounds_Exterior1_EventScript_GymAttendant_53
# 160 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	case 2, TestingGrounds_Exterior1_EventScript_GymAttendant_54
# 161 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	case 3, TestingGrounds_Exterior1_EventScript_GymAttendant_55
TestingGrounds_Exterior1_EventScript_GymAttendant_39:
# 164 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special HealPlayerParty
# 165 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_StartBattle
# 166 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 167 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_ne TestingGrounds_Exterior1_EventScript_GymAttendant_44
# 181 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_ChallengerDefeated
# 182 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_AwardVictoryPoints
# 183 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	playfanfare MUS_OBTAIN_B_POINTS
# 184 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	message TestingGrounds_Exterior1_Text_EarnedGymPoints
# 185 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	waitfanfare
# 186 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	waitmessage
# 187 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq TestingGrounds_Exterior1_EventScript_GymAttendant_57
TestingGrounds_Exterior1_EventScript_GymAttendant_56:
# 190 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	closemessage
# 191 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	applymovement LOCALID_TESTING_GYM_CHALLENGER, TestingGrounds_Exterior1_EventScript_GymAttendant_Movement_1
# 192 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	waitmovement 0
# 193 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	removeobject LOCALID_TESTING_GYM_CHALLENGER
# 194 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	addvar VAR_TEMP_3, 1
	goto TestingGrounds_Exterior1_EventScript_GymAttendant_30

TestingGrounds_Exterior1_EventScript_GymAttendant_34:
# 202 "data/maps/TestingGrounds_Exterior1/scripts.pory"
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
# 150 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	switch VAR_RESULT
# 151 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	case 0, TestingGrounds_Exterior1_EventScript_GymAttendant_47
# 152 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	case 1, TestingGrounds_Exterior1_EventScript_GymAttendant_48
# 153 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	case 2, TestingGrounds_Exterior1_EventScript_GymAttendant_49
# 154 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	case 3, TestingGrounds_Exterior1_EventScript_GymAttendant_50
	goto TestingGrounds_Exterior1_EventScript_GymAttendant_39

TestingGrounds_Exterior1_EventScript_GymAttendant_44:
# 168 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_RecordLoss
# 169 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_LeaderLost
# 170 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	closemessage
# 171 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	applymovement LOCALID_TESTING_GYM_CHALLENGER, TestingGrounds_Exterior1_EventScript_GymAttendant_Movement_1
# 172 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	waitmovement 0
# 173 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	removeobject LOCALID_TESTING_GYM_CHALLENGER
# 174 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_End
# 175 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special LoadPlayerParty
# 176 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special HealPlayerParty
# 177 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_GymClosedAfterLoss
# 178 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	release
	end

TestingGrounds_Exterior1_EventScript_GymAttendant_47:
# 151 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_IntroVito
	goto TestingGrounds_Exterior1_EventScript_GymAttendant_39

TestingGrounds_Exterior1_EventScript_GymAttendant_48:
# 152 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_IntroNadia
	goto TestingGrounds_Exterior1_EventScript_GymAttendant_39

TestingGrounds_Exterior1_EventScript_GymAttendant_49:
# 153 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_IntroIvan
	goto TestingGrounds_Exterior1_EventScript_GymAttendant_39

TestingGrounds_Exterior1_EventScript_GymAttendant_50:
# 154 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_IntroMara
	goto TestingGrounds_Exterior1_EventScript_GymAttendant_39

TestingGrounds_Exterior1_EventScript_GymAttendant_52:
# 158 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_IntroBenny
	goto TestingGrounds_Exterior1_EventScript_GymAttendant_39

TestingGrounds_Exterior1_EventScript_GymAttendant_53:
# 159 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_IntroDino
	goto TestingGrounds_Exterior1_EventScript_GymAttendant_39

TestingGrounds_Exterior1_EventScript_GymAttendant_54:
# 160 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_IntroRika
	goto TestingGrounds_Exterior1_EventScript_GymAttendant_39

TestingGrounds_Exterior1_EventScript_GymAttendant_55:
# 161 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_IntroTommy
	goto TestingGrounds_Exterior1_EventScript_GymAttendant_39

TestingGrounds_Exterior1_EventScript_GymAttendant_57:
# 188 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_BarFilled
	goto TestingGrounds_Exterior1_EventScript_GymAttendant_56


TestingGrounds_Exterior1_EventScript_TeamKeeper::
# 213 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	lock
# 214 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	faceplayer
# 215 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_TeamKeeperIntro
TestingGrounds_Exterior1_EventScript_TeamKeeper_2:
# 217 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	message TestingGrounds_Exterior1_Text_ChooseTeam
# 218 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	waitmessage
# 219 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	dynmultichoice 0, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, TestingGrounds_Exterior1_Text_Team1, TestingGrounds_Exterior1_Text_Team2, TestingGrounds_Exterior1_Text_Team3, TestingGrounds_Exterior1_Text_Team4, TestingGrounds_Exterior1_Text_Team5, TestingGrounds_Exterior1_Text_TeamMenuExit
# 226 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, MULTI_B_PRESSED
	goto_if_eq TestingGrounds_Exterior1_EventScript_TeamKeeper_5
# 226 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, GYM_NUM_SAVED_TEAMS
	goto_if_eq TestingGrounds_Exterior1_EventScript_TeamKeeper_5
# 229 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	copyvar VAR_0x8004, VAR_RESULT
# 230 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	copyvar VAR_TEMP_1, VAR_RESULT
# 231 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	addvar VAR_TEMP_1, 1
# 232 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	buffernumberstring STR_VAR_2, VAR_TEMP_1
# 233 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymTeams_BufferTeam
# 234 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq TestingGrounds_Exterior1_EventScript_TeamKeeper_10
# 237 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_TeamMembers
TestingGrounds_Exterior1_EventScript_TeamKeeper_9:
# 239 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	closemessage
# 240 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, TestingGrounds_Exterior1_Text_TeamActionRegister, TestingGrounds_Exterior1_Text_TeamActionClear, TestingGrounds_Exterior1_Text_TeamActionBack
# 244 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	switch VAR_RESULT
# 245 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	case 0, TestingGrounds_Exterior1_EventScript_TeamKeeper_14
# 248 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	case 1, TestingGrounds_Exterior1_EventScript_TeamKeeper_15
	goto TestingGrounds_Exterior1_EventScript_TeamKeeper_2

TestingGrounds_Exterior1_EventScript_TeamKeeper_1:
# 253 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_TeamKeeperBye
# 254 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	release
	end

TestingGrounds_Exterior1_EventScript_TeamKeeper_5:
	goto TestingGrounds_Exterior1_EventScript_TeamKeeper_1

TestingGrounds_Exterior1_EventScript_TeamKeeper_10:
# 235 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_TeamEmpty
	goto TestingGrounds_Exterior1_EventScript_TeamKeeper_9

TestingGrounds_Exterior1_EventScript_TeamKeeper_14:
# 246 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymTeams_RegisterParty
# 247 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_TeamRegistered
	goto TestingGrounds_Exterior1_EventScript_TeamKeeper_2

TestingGrounds_Exterior1_EventScript_TeamKeeper_15:
# 249 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymTeams_ClearTeam
# 250 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_TeamCleared
	goto TestingGrounds_Exterior1_EventScript_TeamKeeper_2


TestingGrounds_Exterior1_EventScript_RankExaminer::
# 263 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	lock
# 264 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	faceplayer
# 265 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_BufferRankInfo
# 266 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_RankInfo
# 267 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_BufferSignatureMove
# 268 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_SignatureMoveInfo
# 269 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_GYM_RANK, 3
	goto_if_ge TestingGrounds_Exterior1_EventScript_RankExaminer_2
TestingGrounds_Exterior1_EventScript_RankExaminer_1:
# 272 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_BufferGymProgress
# 273 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_GymProgress
# 274 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_BufferStreak
# 275 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_StreakInfo
# 276 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_IsRankUpUnlocked
# 277 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq TestingGrounds_Exterior1_EventScript_RankExaminer_5
TestingGrounds_Exterior1_EventScript_RankExaminer_4:
# 280 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_GYM_RANK, GYM_RANK_MAX
	goto_if_ge TestingGrounds_Exterior1_EventScript_RankExaminer_8
# 285 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_TestRankUpPrompt, MSGBOX_YESNO
# 286 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq TestingGrounds_Exterior1_EventScript_RankExaminer_11
TestingGrounds_Exterior1_EventScript_RankExaminer_10:
# 291 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	release
	end

TestingGrounds_Exterior1_EventScript_RankExaminer_2:
# 270 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_OffTypeInfo
	goto TestingGrounds_Exterior1_EventScript_RankExaminer_1

TestingGrounds_Exterior1_EventScript_RankExaminer_5:
# 278 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_ExamUnlockedNote
	goto TestingGrounds_Exterior1_EventScript_RankExaminer_4

TestingGrounds_Exterior1_EventScript_RankExaminer_8:
# 281 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_MaxRank
# 282 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	release
	end

TestingGrounds_Exterior1_EventScript_RankExaminer_11:
# 287 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_RankUp
# 288 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	special GymChallenge_BufferRankInfo
# 289 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	msgbox TestingGrounds_Exterior1_Text_RankedUp
	goto TestingGrounds_Exterior1_EventScript_RankExaminer_10


# 145 "data/maps/TestingGrounds_Exterior1/scripts.pory"
TestingGrounds_Exterior1_EventScript_GymAttendant_Movement_0:
# 145 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	walk_down
# 145 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	walk_down
	step_end

# 171 "data/maps/TestingGrounds_Exterior1/scripts.pory"
TestingGrounds_Exterior1_EventScript_GymAttendant_Movement_1:
# 171 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	walk_up
# 171 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	walk_up
	step_end

TestingGrounds_Exterior1_Text_GiftIntro::
# 295 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Ah, our new GYM LEADER!\p"
	.string "A LEADER needs POKéMON of the GYM's\n"
	.string "own type.\p"
	.string "Take these three {STR_VAR_1}-type\n"
	.string "partners!$"

TestingGrounds_Exterior1_Text_GiftReceived::
# 303 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "{PLAYER} received three\n"
	.string "{STR_VAR_1}-type POKéMON!$"

TestingGrounds_Exterior1_Text_GiftExplainRules::
# 308 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "At rank {STR_VAR_1}, you defend with\n"
	.string "{STR_VAR_3} POKéMON at level {STR_VAR_2}\l"
	.string "or below.\p"
	.string "Register teams with the TEAM KEEPER,\n"
	.string "then speak to the attendant to open\l"
	.string "your GYM!$"

TestingGrounds_Exterior1_Text_ReceivedSignatureTM::
# 317 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "{PLAYER} received {STR_VAR_2}!$"

TestingGrounds_Exterior1_Text_ExplainSignatureTM::
# 321 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "That TM teaches {STR_VAR_3} -\n"
	.string "your GYM's signature move!\p"
	.string "One day, outsider POKéMON that\n"
	.string "learn it may fight by your side.$"

TestingGrounds_Exterior1_Text_SignatureTMNoRoom::
# 328 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Oh! There's no room in your BAG\n"
	.string "for the GYM's signature TM.\p"
	.string "Come see me when you've made\n"
	.string "space.$"

TestingGrounds_Exterior1_Text_GiftPostGift::
# 335 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "How are your POKéMON doing?\p"
	.string "Defend your GYM well and it will\n"
	.string "grow in rank!$"

TestingGrounds_Exterior1_Text_GiftNoRoom::
# 341 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Oh! You don't have room for three\n"
	.string "more POKéMON.\p"
	.string "Come back when you've made space.$"

TestingGrounds_Exterior1_Text_OpenGymPrompt::
# 347 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Welcome, GYM LEADER {PLAYER}!\p"
	.string "Shall we open the GYM and accept\n"
	.string "challenges?$"

TestingGrounds_Exterior1_Text_ComeBackAnytime::
# 353 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Very well. Come back whenever\n"
	.string "you're ready.$"

TestingGrounds_Exterior1_Text_ChooseTeamSource::
# 358 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Who defends the GYM today?$"

TestingGrounds_Exterior1_Text_SourceParty::
# 362 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "CURRENT PARTY$"

TestingGrounds_Exterior1_Text_SourceCancel::
# 366 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "CANCEL$"

TestingGrounds_Exterior1_Text_TeamUnavailable::
# 370 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Hmm… I can't find any of that\n"
	.string "team's members.\p"
	.string "Have they been released or\n"
	.string "traded away?$"

TestingGrounds_Exterior1_Text_PickDefenders::
# 377 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Now, pick the {STR_VAR_3} POKéMON\n"
	.string "that will defend the GYM!$"

TestingGrounds_Exterior1_Text_TeamWrongSize::
# 382 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Hmm… At rank {STR_VAR_1}, a LEADER\n"
	.string "defends with up to {STR_VAR_3} POKéMON.\p"
	.string "Please adjust your party and\n"
	.string "come back.$"

TestingGrounds_Exterior1_Text_TeamOverleveled::
# 389 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Hmm… At rank {STR_VAR_1}, your POKéMON\n"
	.string "must be level {STR_VAR_2} or below.\p"
	.string "Please adjust your party and\n"
	.string "come back.$"

TestingGrounds_Exterior1_Text_TeamWrongType::
# 396 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Hmm… This is a {STR_VAR_1}-type GYM.\p"
	.string "Your team may only include POKéMON\n"
	.string "of the GYM's type, or an outsider\l"
	.string "that knows your signature move.\p"
	.string "Please adjust your party and\n"
	.string "come back.$"

TestingGrounds_Exterior1_Text_GymIsOpen::
# 405 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "The GYM is now open!\p"
	.string "Three TRAINERS signed up to\n"
	.string "challenge you today.\p"
	.string "Here comes the first one!$"

TestingGrounds_Exterior1_Text_StreakPhraseCalm::
# 412 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "ATTENDANT: Mostly first-timers in\n"
	.string "line today.\p"
	.string "A calm day at the GYM, I'd say.$"

TestingGrounds_Exterior1_Text_StreakPhraseStirring::
# 418 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "ATTENDANT: A few familiar faces in\n"
	.string "line today…\p"
	.string "Some of them have clearly been\n"
	.string "training for this.$"

TestingGrounds_Exterior1_Text_StreakPhraseSpreading::
# 425 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "ATTENDANT: Word of your streak is\n"
	.string "spreading, LEADER.\p"
	.string "Serious TRAINERS are starting to\n"
	.string "line up outside.$"

TestingGrounds_Exterior1_Text_StreakPhrasePeak::
# 432 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "ATTENDANT: The line is full of\n"
	.string "hardened TRAINERS today!\p"
	.string "Every one of them has come to end\n"
	.string "your streak. Stay sharp!$"

TestingGrounds_Exterior1_Text_StrongChallengerWarning::
# 439 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "ATTENDANT: Careful, LEADER…\p"
	.string "This one has the look of a real\n"
	.string "contender!$"

TestingGrounds_Exterior1_Text_StreakInfo::
# 445 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Your current win streak:\n"
	.string "{STR_VAR_1} in a row.$"

TestingGrounds_Exterior1_Text_IntroBenny::
# 450 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "{STR_VAR_1}: So you're the new GYM\n"
	.string "LEADER?\p"
	.string "My POOCHYENA and I are gonna take\n"
	.string "your badge, mister!$"

TestingGrounds_Exterior1_Text_IntroDino::
# 457 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "{STR_VAR_1}: I found sooo many BUG\n"
	.string "POKéMON in the woods!\p"
	.string "Let's see them squish your\n"
	.string "POKéMON!$"

TestingGrounds_Exterior1_Text_IntroRika::
# 464 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "{STR_VAR_1}: My FIGHTING-type\n"
	.string "POKéMON train every day!\p"
	.string "Show me what a real GYM LEADER\n"
	.string "can do. Prepare yourself!$"

TestingGrounds_Exterior1_Text_IntroTommy::
# 471 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "{STR_VAR_1}: I studied all about\n"
	.string "type matchups in school!\p"
	.string "Today's lesson: beating a GYM\n"
	.string "LEADER!$"

TestingGrounds_Exterior1_Text_IntroVito::
# 478 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "{STR_VAR_1}: I've watched every one\n"
	.string "of your GYM battles, LEADER.\p"
	.string "My team was built to take\n"
	.string "yours apart!$"

TestingGrounds_Exterior1_Text_IntroNadia::
# 485 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "{STR_VAR_1}: A win here would make\n"
	.string "my career.\p"
	.string "I picked my POKéMON just\n"
	.string "for your GYM. Let's go!$"

TestingGrounds_Exterior1_Text_IntroIvan::
# 492 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "{STR_VAR_1}: I foresaw your every\n"
	.string "move before I walked in.\p"
	.string "This battle is already\n"
	.string "decided!$"

TestingGrounds_Exterior1_Text_IntroMara::
# 499 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "{STR_VAR_1}: Hee hee… Your GYM has\n"
	.string "such a lovely aura…\p"
	.string "Let's see if it survives\n"
	.string "my little curse.$"

TestingGrounds_Exterior1_Text_EarnedGymPoints::
# 506 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "{PLAYER} earned {STR_VAR_1} GYM POINTS!$"

TestingGrounds_Exterior1_Text_BarFilled::
# 510 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "ATTENDANT: Incredible!\p"
	.string "Your GYM's reputation has reached\n"
	.string "its peak for this rank!\p"
	.string "You may take the RANK-UP EXAM\n"
	.string "whenever you feel ready!$"

TestingGrounds_Exterior1_Text_ExamAvailable::
# 518 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "ATTENDANT: Remember, the RANK-UP\n"
	.string "EXAM awaits whenever you're ready!$"

TestingGrounds_Exterior1_Text_ChallengerDefeated::
# 523 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "{STR_VAR_1}: Aww… You really are\n"
	.string "the GYM LEADER!\p"
	.string "I'll train harder and challenge\n"
	.string "you again!$"

TestingGrounds_Exterior1_Text_NextChallengerArrived::
# 530 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "ATTENDANT: Well defended!\p"
	.string "Your POKéMON have been healed.\n"
	.string "The next challenger has arrived!$"

TestingGrounds_Exterior1_Text_LeaderLost::
# 536 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "{STR_VAR_1}: I… I won?!\p"
	.string "I beat a GYM LEADER! Wait till\n"
	.string "everyone hears about this!$"

TestingGrounds_Exterior1_Text_GymClosedAfterLoss::
# 542 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "ATTENDANT: Oh no…\p"
	.string "We'll close the GYM for today.\n"
	.string "Rest up and try again tomorrow!$"

TestingGrounds_Exterior1_Text_GymDayComplete::
# 548 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "ATTENDANT: That was the last\n"
	.string "challenger for today!\p"
	.string "You defended your GYM perfectly,\n"
	.string "LEADER {PLAYER}!\p"
	.string "Keep this up and the GYM's rank\n"
	.string "will surely rise!$"

TestingGrounds_Exterior1_Text_TeamKeeperIntro::
# 557 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Hello, LEADER! I keep your\n"
	.string "registered GYM TEAMS.\p"
	.string "A team remembers its members even\n"
	.string "if you move them around the PC.$"

TestingGrounds_Exterior1_Text_ChooseTeam::
# 564 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Which team shall we look at?$"

TestingGrounds_Exterior1_Text_Team1::
# 568 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "TEAM 1$"

TestingGrounds_Exterior1_Text_Team2::
# 572 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "TEAM 2$"

TestingGrounds_Exterior1_Text_Team3::
# 576 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "TEAM 3$"

TestingGrounds_Exterior1_Text_Team4::
# 580 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "TEAM 4$"

TestingGrounds_Exterior1_Text_Team5::
# 584 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "TEAM 5$"

TestingGrounds_Exterior1_Text_TeamMenuExit::
# 588 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "EXIT$"

TestingGrounds_Exterior1_Text_TeamEmpty::
# 592 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "TEAM {STR_VAR_2} is empty.$"

TestingGrounds_Exterior1_Text_TeamMembers::
# 596 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "TEAM {STR_VAR_2}:\p"
	.string "{STR_VAR_1}$"

TestingGrounds_Exterior1_Text_TeamActionRegister::
# 601 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "REGISTER PARTY$"

TestingGrounds_Exterior1_Text_TeamActionClear::
# 605 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "CLEAR TEAM$"

TestingGrounds_Exterior1_Text_TeamActionBack::
# 609 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "BACK$"

TestingGrounds_Exterior1_Text_TeamRegistered::
# 613 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Done! Your current party is now\n"
	.string "TEAM {STR_VAR_2}.$"

TestingGrounds_Exterior1_Text_TeamCleared::
# 618 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "TEAM {STR_VAR_2} has been cleared.$"

TestingGrounds_Exterior1_Text_TeamKeeperBye::
# 622 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Come back anytime, LEADER!$"

TestingGrounds_Exterior1_Text_RankInfo::
# 626 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "EXAMINER: You preside at rank\n"
	.string "{STR_VAR_1}, LEADER.\p"
	.string "Your GYM team may have {STR_VAR_3}\n"
	.string "POKéMON of level {STR_VAR_2} or below.$"

TestingGrounds_Exterior1_Text_SignatureMoveInfo::
# 633 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Your GYM's signature move is\n"
	.string "{STR_VAR_1}.$"

TestingGrounds_Exterior1_Text_OffTypeInfo::
# 638 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "At your rank, one team member may\n"
	.string "be an outsider type…\p"
	.string "…as long as it knows {STR_VAR_1},\n"
	.string "your signature move!$"

TestingGrounds_Exterior1_Text_GymProgress::
# 645 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "You lead a {STR_VAR_1}-type GYM.\p"
	.string "Reputation this rank:\n"
	.string "{STR_VAR_2} of {STR_VAR_3} points.$"

TestingGrounds_Exterior1_Text_ExamUnlockedNote::
# 651 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Your reputation is at its peak!\n"
	.string "The RANK-UP EXAM awaits you.$"

TestingGrounds_Exterior1_Text_MaxRank::
# 656 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "You stand at the very top,\n"
	.string "LEADER. There is no higher rank!$"

TestingGrounds_Exterior1_Text_TestRankUpPrompt::
# 661 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "(TEST) Advance to the next rank\n"
	.string "right now?$"

TestingGrounds_Exterior1_Text_RankedUp::
# 666 "data/maps/TestingGrounds_Exterior1/scripts.pory"
	.string "Congratulations, LEADER!\p"
	.string "You now preside at rank {STR_VAR_1}!\p"
	.string "New rules: {STR_VAR_3} POKéMON of\n"
	.string "level {STR_VAR_2} or below.$"
