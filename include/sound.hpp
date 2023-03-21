#ifndef SOUND_HPP
#define SOUND_HPP

#include <SFML/Audio.hpp>

namespace gh {
class sound {
   public:
    void load();
    void play_score();
    void play_hit();
    void play_fly();

   private:
    sf::SoundBuffer m_score_buffer;
    sf::SoundBuffer m_fly_buffer;
    sf::SoundBuffer m_hit_buffer;

    sf::Sound m_score_sound;
    sf::Sound m_fly_sound;
    sf::Sound m_hit_sound;
};
}  // namespace gh
#endif