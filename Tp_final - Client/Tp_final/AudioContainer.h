#pragma once
#include <string>
#include <math.h>				/* pow */
#include <iostream>
#include "AllegroClass.h"

#define FOLDER_AUDIO ("audio")

#define FOLDER_TOM ("tom")
#define FOLDER_NICK ("nick")
#define FOLDER_PURPLE ("purple")
#define FOLDER_CRAZY ("crazy")
#define FOLDER_FATTY ("fatty")
#define FOLDER_FIRE ("fire")
#define FOLDER_SNOW ("snow")
#define FOLDER_BALL ("ball")

#define FILE_DEATH_SOUND ("death-soundEffect.ogg")
#define FILE_JUMP_SOUND ("jump-soundEffect.wav")
#define FILE_ATTACK_SOUND ("attack-soundEffect.wav")
#define FILE_WALK_SOUND ("walk-soundEffect.wav")

#define FILE_IMPACT_SOUND ("impact-soundEffect.wav")
#define FILE_MOVE_SOUND ("move-soundEffect.wav")

#define FOLDER_MAIN_SONG ("main song")
#define FILE_MAIN_SONG ("one-punch-man-8-bit-cover.ogg")


#define CHARA_QUANTITY (5)
#define SAMPLES_PER_CHARA (4)
#define PROYECTILE_QUANTITY (2)
#define SAMPLES_PER_PROY (2)
#define BALL_QUANTITY (1)
#define SAMPLES_PER_BALL (2)
#define MAIN_SONG_QUANTITY (1)
#define SAMPLES_QUANTITY (CHARA_QUANTITY * SAMPLES_PER_CHARA + PROYECTILE_QUANTITY * SAMPLES_PER_PROY + BALL_QUANTITY * SAMPLES_PER_BALL + MAIN_SONG_QUANTITY)

class AudioContainer
{
public:
	AudioContainer();
	~AudioContainer();

	typedef struct character_samples {
		ALLEGRO_SAMPLE* death_soundEffect;
		ALLEGRO_SAMPLE* jump_soundEffect;
		ALLEGRO_SAMPLE* shot_soundEffect;
		ALLEGRO_SAMPLE* walk_soundEffect;
	}character_samples;

	typedef struct proyectile_samples {
		ALLEGRO_SAMPLE* impact_soundEffect;
		ALLEGRO_SAMPLE* move_soundEffect;
	}proyectle_samples;

	typedef struct ball_samples {
		ALLEGRO_SAMPLE* impact_soundEffect;
		ALLEGRO_SAMPLE* move_soundEffect;
	}ball_samples;

	typedef struct proyectile_soundEffects {
		proyectle_samples fire;
		proyectle_samples snow;
	}proyectile_samples_container;

	typedef struct chara_soundEffects {
		character_samples tom;
		character_samples nick;
		character_samples purple;
		character_samples fatty;
		character_samples crazy;
	}character_samples_container;

	character_samples_container my_character_samples_container;
	proyectile_samples_container my_proyectile_samples_container;
	ball_samples my_ball_samples;
	ALLEGRO_SAMPLE* main_song;

	void play_main_song(void);
	void stop_main_song(void);

private:
	//enemy samples
	void load_enemy_samples();
	void load_purple_samples();
	void load_fatty_samples();
	void load_crazy_samples();

	//projectile samples
	void load_projectile_samples();
	void load_snow_samples();
	void load_fire_samples();

	//ball samples
	void load_ball_samples();

	//main song
	void load_main_song();

	//player samples
	void load_player_samples();
	void load_tom_samples();
	void load_nick_samples();

	void load_all_samples(unsigned int samples_cuantity);
	void load_sample(ALLEGRO_SAMPLE** sample, std::string folder1, std::string folder2, std::string file);

	ALLEGRO_SAMPLE_ID* main_song_ID;

	void destroy_all_samples();
	void destroy_player_samples();
	void destroy_enemy_samples();
	void destroy_proyectile_samples();
	void destroy_ball_samples();
};

