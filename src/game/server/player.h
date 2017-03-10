/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_SERVER_PLAYER_H
#define GAME_SERVER_PLAYER_H

// this include should perhaps be removed
#include "entities/character.h"
#include "gamecontext.h"

// player object
class CPlayer
{
	MACRO_ALLOC_POOL_ID()

	friend class CSaveTee;

public:
	CPlayer(CGameContext *pGameServer, int ClientID, int Team);
	~CPlayer();

	void Reset();

	void TryRespawn();
	void Respawn();
	CCharacter* ForceSpawn(vec2 Pos); // required for loading savegames
	void SetTeam(int Team, bool DoChatMsg=true);
	int GetTeam() const { return m_Team; };
	int GetCID() const { return m_ClientID; };

	void Tick();
	void PostTick();
	void Snap(int SnappingClient);
	void FakeSnap(int SnappingClient);

	void OnDirectInput(CNetObj_PlayerInput *NewInput);
	void OnPredictedInput(CNetObj_PlayerInput *NewInput);
	void OnDisconnect(const char *pReason);

	void ThreadKillCharacter(int Weapon = WEAPON_GAME);
	void KillCharacter(int Weapon = WEAPON_GAME);
	CCharacter *GetCharacter();

	void FindDuplicateSkins();

	void MoneyTransaction(int Amount, const char *Description);

	//---------------------------------------------------------
	// this is used for snapping so we know how we can clip the view for the player
	vec2 m_ViewPos;
	int m_TuneZone;
	int m_TuneZoneOld;

	// states if the client is chatting, accessing a menu etc.
	int m_PlayerFlags;

	// used for snapping to just update latency if the scoreboard is active
	int m_aActLatency[MAX_CLIENTS];

	// used for spectator mode
	int m_SpectatorID;

	bool m_IsReady;

	//
	int m_Vote;
	int m_VotePos;
	//
	int m_LastVoteCall;
	int m_LastVoteTry;
	int m_LastChat;
	int m_LastSetTeam;
	int m_LastSetSpectatorMode;
	int m_LastChangeInfo;
	int m_LastEmote;
	int m_LastKill;
	int m_LastCommands[4];
	int m_LastCommandPos;
	int m_LastWhisperTo;

	int m_SendVoteIndex;





	// TODO: clean this up
	struct
	{
		char m_SkinName[64];
		int m_UseCustomColor;
		int m_ColorBody;
		int m_ColorFeet;
	} m_TeeInfos;

	int m_RespawnTick;
	int m_DieTick;
	int m_Score;
	//int m_xp;
	int m_ScoreStartTick;
	bool m_ForceBalanced;
	int m_LastActionTick;
	bool m_StolenSkin;
	int m_TeamChangeTick;
	struct
	{
		int m_TargetX;
		int m_TargetY;
	} m_LatestActivity;

	// network latency calculations
	struct
	{
		int m_Accum;
		int m_AccumMin;
		int m_AccumMax;
		int m_Avg;
		int m_Min;
		int m_Max;
	} m_Latency;

private:
	CCharacter *m_pCharacter;
	int m_NumInputs;
	CGameContext *m_pGameServer;

	CGameContext *GameServer() const { return m_pGameServer; }
	IServer *Server() const;

	//
	bool m_Spawning;
	int m_ClientID;
	int m_Team;


	// DDRace
public:
	enum
	{
		PAUSED_NONE=0,
		PAUSED_SPEC,
		PAUSED_PAUSED,
		PAUSED_FORCE
	};

	int m_Paused;
	bool m_DND;
	int64 m_NextPauseTick;
	char m_TimeoutCode[64];

	void ProcessPause();
	int m_ForcePauseTime;
	bool IsPlaying();
	int64 m_Last_KickVote;
	int64 m_Last_Team;
	int m_Authed;
	int m_ClientVersion;
	bool m_ShowOthers;
	bool m_ShowAll;
	bool m_SpecTeam;
	bool m_NinjaJetpack;
	bool m_Afk;
	int m_KillMe;

	int m_ChatScore;

	bool AfkTimer(int new_target_x, int new_target_y); //returns true if kicked
	void AfkVoteTimer(CNetObj_PlayerInput *NewTarget);
	int64 m_LastPlaytime;
	int64 m_LastEyeEmote;
	int m_LastTarget_x;
	int m_LastTarget_y;
	CNetObj_PlayerInput m_LastTarget;
	int m_Sent1stAfkWarning; // afk timer's 1st warning after 50% of sv_max_afk_time
	int m_Sent2ndAfkWarning; // afk timer's 2nd warning after 90% of sv_max_afk_time
	char m_pAfkMsg[160];
	bool m_EyeEmote;
	int m_TimerType;
	int m_DefEmote;
	int m_DefEmoteReset;
	bool m_Halloween;
	bool m_FirstPacket;

	//zCatch ChillerDragon
	int aCatchedID[64] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };

	bool m_IsDummy;

	// dummy 32 vars
	bool m_Dummy_32dummy;
	int m_Dummy_32look;


	//dummy 33 vars (Chillintelligenz)
	long m_ci_lowest_dest_dist = 2147483646; //max long len 2147483647
	long m_ci_latest_dest_dist = 0;


	//###########
	//minigames
	//###########

	//bomb (moved character.h)
	//bool m_IsBomb;
	//bool m_IsBombing;
	//bool m_IsBombReady;
	//moved to gamecontext.cpp
	//int m_BombColor;
	//bool m_bwff; //black whithe flip flip
	
	//bomb stats
	int m_BombGamesPlayed;
	int m_BombGamesWon;
	int m_BombBanTime;

	//chidraqul3 (minigame)
	int m_GoldRespawnDelay;
	int m_GoldPos;
	bool m_GoldAlive;
	int m_HashGold;
	int m_Minigameworld_size_x;
	char m_HashSkin[12];
	int m_HashPos;
	int m_HashPosY;
	bool m_BoughtGame;
	bool m_IsMinigame;

	//profiles
	int m_ProfileStyle;
	int m_ProfileViews;
	char m_ProfileStatus[50];
	char m_ProfileSkype[50];
	char m_ProfileYoutube[50];
	char m_ProfileEmail[50];
	char m_ProfileHomepage[50];
	char m_ProfileTwitter[50];



	//PvP-arena ChillerDragon
	int m_pvp_arena_tickets;
	//bool m_IsHammerfight; //moved to character and renamed to --> m_IsHammerarena
	int m_PVP_return_posX;
	int m_PVP_return_posY;

	int m_pvp_arena_games_played;
	int m_pvp_arena_kills;
	int m_pvp_arena_deaths;

	//zCatch ChillerDragon (instagib)
	int m_GrenadeKills;
	int m_GrenadeDeaths;
	int m_GrenadeSpree;
	int m_GrenadeShots;
	int m_GrenadeWins;
	int m_RifleKills;
	int m_RifleDeaths;
	int m_RifleSpree;
	int m_RifleShots;
	int m_RifleWins;

	//city stuff
	//int m_broadcast_animation; //idk if this var will be used. plan: check for a running animation and animate it //try in gamecontext.cpp
	bool m_cheats_aimbot;
	bool m_dummy_member; //trusted by dummy

	//##########
	//city stuff
	//##########

	//Account stuff:
	//Moderator and SuperModerator
	bool m_IsModerator;
	bool m_IsSuperModerator;
	bool m_IsSuperModSpawn;

	bool m_IsAccFrozen; //cant use the sql acc if true

	char m_LastLogoutIGN1[32]; 
	char m_LastLogoutIGN2[32];
	char m_LastLogoutIGN3[32];
	char m_LastLogoutIGN4[32];
	char m_LastLogoutIGN5[32];



	int m_homing_missiles_ammo;



	//money and traiding

	int m_StockMarket_item_Cucumbers;

	char m_money_transaction0[512];
	char m_money_transaction1[512];
	char m_money_transaction2[512];
	char m_money_transaction3[512];
	char m_money_transaction4[512];
	char m_money_transaction5[512];
	char m_money_transaction6[512];
	char m_money_transaction7[512];
	char m_money_transaction8[512];
	char m_money_transaction9[512];

	//other

	bool m_IsTest;
	bool m_TaserOn;
	bool m_PoliceHelper;
	int m_TaserLevel;
	int m_TaserPrice;
	int64 m_JailTime;
	int m_failed_escapes;
	int m_escape_skill;
	bool m_escape_plan;
	bool m_escape_plan_b;
	bool m_escape_plan_c;
	int m_PoliceRank;
	bool m_BoughtRoom;
	int m_aliveplusxp;
	int m_shit;
	int m_money;
	int m_level;
	int m_max_level; //used to stop give players xp at a specific level. just increase the value in player.cpp (init) if u update the level syetem
	int64 m_xp;
	bool m_xpmsg;
	bool m_hidejailmsg;
	bool m_MoneyTilePlus;
	bool m_fake_admin;
	int64 m_LastGift;
	int64 m_LastFight;
	int m_AccountID;
	int64 m_neededxp;

	void Save();
	void Logout();
	void CheckLevel();
	void CalcExp();

	bool m_HammerRequest;

	int m_DummyMode;
	int m_dmm25; //change dummy modes in the mode 25  ( choose sub modes)
	float m_Dummy_nn_latest_Distance;
	float m_Dummy_nn_highest_Distance;
	float m_Dummy_nn_highest_Distance_touched;
	float m_Dummy_nn_latest_fitness;
	float m_Dummy_nn_highest_fitness;
	int m_Dummy_nn_time;

	//########
	//extras
	//########

	// infinite cosmetics
	bool m_InfRainbow;
	bool m_InfBloody;
	bool m_InfAtom;
	bool m_InfTrail;
	// cosmetic offers
	int m_rainbow_offer;
	int m_bloody_offer;
	int m_atom_offer;
	int m_trail_offer;

	int m_KillStreak;
	bool m_IsJailed;
	int64 m_EscapeTime;
	bool m_InBank;
	bool m_ExitBank;

	//BLOCK POINTS

	int m_BlockPoints;
	int m_BlockPoints_Kills; //Block points (blocked others)
	int m_BlockPoints_Deaths; //Block -points (blocked by others)
	int m_LastToucherID; //The id of the last person who touched this tee (if none -1)

	//bool m_hammerfight;
	//bool m_isHeal;
	bool m_ninjasteam;
	bool m_disarm;
	//bool m_freezeShotgun;
	int m_RainbowColor;
#if defined(CONF_SQL)
	int64 m_LastSQLQuery;
#endif

	int64 m_LastWarning;
	int m_ChilliWarnings;
	bool m_trolled;
	bool m_RconFreeze;
};

#endif
