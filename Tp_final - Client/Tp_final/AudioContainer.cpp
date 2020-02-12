#include "AudioContainer.h"

AudioContainer::AudioContainer()
{
	load_all_samples(SAMPLES_QUANTITY);
	main_song_ID = new ALLEGRO_SAMPLE_ID;
}

AudioContainer::~AudioContainer()
{
	destroy_all_samples();
	delete main_song_ID;
}

void AudioContainer::load_player_samples()
{
	load_tom_samples();
	load_nick_samples();
}

void AudioContainer::load_all_samples(unsigned int samples_cuantity)
{
	al_reserve_samples(samples_cuantity);
	load_enemy_samples();
	load_projectile_samples();
	load_player_samples();
	load_ball_samples();
	load_main_song();
}

void AudioContainer::load_sample(ALLEGRO_SAMPLE** sample, std::string folder1, std::string folder2, std::string file)
{
	std::string sample_dir = folder1 + '/' + folder2 + '/' + file;
	*sample = al_load_sample(sample_dir.c_str());
}

void AudioContainer::load_tom_samples()
{
	load_sample(&my_character_samples_container.tom.death_soundEffect, FOLDER_AUDIO, FOLDER_TOM, FILE_DEATH_SOUND);
	load_sample(&my_character_samples_container.tom.jump_soundEffect, FOLDER_AUDIO, FOLDER_TOM, FILE_JUMP_SOUND);
	load_sample(&my_character_samples_container.tom.shot_soundEffect, FOLDER_AUDIO, FOLDER_TOM, FILE_ATTACK_SOUND);
	load_sample(&my_character_samples_container.tom.walk_soundEffect, FOLDER_AUDIO, FOLDER_TOM, FILE_WALK_SOUND);
}

void AudioContainer::load_nick_samples()
{
	load_sample(&my_character_samples_container.nick.death_soundEffect, FOLDER_AUDIO, FOLDER_NICK, FILE_DEATH_SOUND);
	load_sample(&my_character_samples_container.nick.jump_soundEffect, FOLDER_AUDIO, FOLDER_NICK, FILE_JUMP_SOUND);
	load_sample(&my_character_samples_container.nick.shot_soundEffect, FOLDER_AUDIO, FOLDER_NICK, FILE_ATTACK_SOUND);
	load_sample(&my_character_samples_container.nick.walk_soundEffect, FOLDER_AUDIO, FOLDER_NICK, FILE_WALK_SOUND);
}

void AudioContainer::load_purple_samples()
{
	load_sample(&my_character_samples_container.purple.death_soundEffect, FOLDER_AUDIO, FOLDER_PURPLE, FILE_DEATH_SOUND);
	load_sample(&my_character_samples_container.purple.jump_soundEffect, FOLDER_AUDIO, FOLDER_PURPLE, FILE_JUMP_SOUND);
	load_sample(&my_character_samples_container.purple.shot_soundEffect, FOLDER_AUDIO, FOLDER_PURPLE, FILE_ATTACK_SOUND);
	load_sample(&my_character_samples_container.purple.walk_soundEffect, FOLDER_AUDIO, FOLDER_PURPLE, FILE_WALK_SOUND);
}

void AudioContainer::load_crazy_samples()
{
	load_sample(&my_character_samples_container.crazy.death_soundEffect, FOLDER_AUDIO, FOLDER_CRAZY, FILE_DEATH_SOUND);
	load_sample(&my_character_samples_container.crazy.jump_soundEffect, FOLDER_AUDIO, FOLDER_CRAZY, FILE_JUMP_SOUND);
	load_sample(&my_character_samples_container.crazy.shot_soundEffect, FOLDER_AUDIO, FOLDER_CRAZY, FILE_ATTACK_SOUND);
	load_sample(&my_character_samples_container.crazy.walk_soundEffect, FOLDER_AUDIO, FOLDER_CRAZY, FILE_WALK_SOUND);
}

void AudioContainer::load_fatty_samples()
{
	load_sample(&my_character_samples_container.fatty.death_soundEffect, FOLDER_AUDIO, FOLDER_FATTY, FILE_DEATH_SOUND);
	load_sample(&my_character_samples_container.fatty.jump_soundEffect, FOLDER_AUDIO, FOLDER_FATTY, FILE_JUMP_SOUND);
	load_sample(&my_character_samples_container.fatty.shot_soundEffect, FOLDER_AUDIO, FOLDER_FATTY, FILE_ATTACK_SOUND);
	load_sample(&my_character_samples_container.fatty.walk_soundEffect, FOLDER_AUDIO, FOLDER_FATTY, FILE_WALK_SOUND);
}

void AudioContainer::destroy_all_samples()
{
	void destroy_chara_samples();
	void destroy_enemy_samples();
	void destroy_proyectile_samples();
	void destroy_ball_samples();
}

void AudioContainer::destroy_player_samples()
{
	al_destroy_sample(my_character_samples_container.tom.death_soundEffect);
	al_destroy_sample(my_character_samples_container.tom.jump_soundEffect);
	al_destroy_sample(my_character_samples_container.purple.shot_soundEffect);

	al_destroy_sample(my_character_samples_container.nick.death_soundEffect);
	al_destroy_sample(my_character_samples_container.nick.jump_soundEffect);
	al_destroy_sample(my_character_samples_container.nick.shot_soundEffect);
}

void AudioContainer::destroy_enemy_samples()
{
	al_destroy_sample(my_character_samples_container.purple.death_soundEffect);
	al_destroy_sample(my_character_samples_container.purple.jump_soundEffect);
	al_destroy_sample(my_character_samples_container.purple.shot_soundEffect);

	al_destroy_sample(my_character_samples_container.crazy.death_soundEffect);
	al_destroy_sample(my_character_samples_container.crazy.jump_soundEffect);
	al_destroy_sample(my_character_samples_container.crazy.shot_soundEffect);

	al_destroy_sample(my_character_samples_container.fatty.death_soundEffect);
	al_destroy_sample(my_character_samples_container.fatty.jump_soundEffect);
	al_destroy_sample(my_character_samples_container.fatty.shot_soundEffect);
}

void AudioContainer::destroy_proyectile_samples()
{
	al_destroy_sample(my_proyectile_samples_container.fire.impact_soundEffect);
	al_destroy_sample(my_proyectile_samples_container.snow.impact_soundEffect);
}

void AudioContainer::destroy_ball_samples()
{
	al_destroy_sample(my_ball_samples.impact_soundEffect);
	al_destroy_sample(my_ball_samples.move_soundEffect);
}

void AudioContainer::play_main_song(void)
{
	al_play_sample(main_song, 0.7, 0, 1.0, ALLEGRO_PLAYMODE_LOOP, main_song_ID);
}

void AudioContainer::stop_main_song(void)
{
	al_stop_sample(main_song_ID);
}

void AudioContainer::load_enemy_samples()
{
	load_purple_samples();
	load_fatty_samples();
	load_crazy_samples();
}

void AudioContainer::load_projectile_samples()
{
	load_snow_samples();
	load_fire_samples();
}

void AudioContainer::load_fire_samples()
{
	load_sample(&my_proyectile_samples_container.fire.impact_soundEffect, FOLDER_AUDIO, FOLDER_SNOW, FILE_IMPACT_SOUND);
	load_sample(&my_proyectile_samples_container.fire.move_soundEffect, FOLDER_AUDIO, FOLDER_FIRE, FILE_MOVE_SOUND);
}

void AudioContainer::load_ball_samples()
{
	load_sample(&my_ball_samples.impact_soundEffect, FOLDER_AUDIO, FOLDER_BALL, FILE_IMPACT_SOUND);
	load_sample(&my_ball_samples.move_soundEffect, FOLDER_AUDIO, FOLDER_BALL, FILE_MOVE_SOUND);
}

void AudioContainer::load_main_song()
{
	load_sample(&main_song, FOLDER_AUDIO, FOLDER_MAIN_SONG, FILE_MAIN_SONG);
}

void AudioContainer::load_snow_samples()
{
	load_sample(&my_proyectile_samples_container.snow.impact_soundEffect, FOLDER_AUDIO, FOLDER_SNOW, FILE_IMPACT_SOUND);
	load_sample(&my_proyectile_samples_container.snow.move_soundEffect, FOLDER_AUDIO, FOLDER_SNOW, FILE_MOVE_SOUND);
}