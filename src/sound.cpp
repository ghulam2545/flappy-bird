#include "../include/sound.hpp"

namespace gh {
void sound::load() {
    // load all sound assets
    m_score_buffer.loadFromFile("../assets/score.wav");
    m_fly_buffer.loadFromFile("../assets/fly.wav");
    m_hit_buffer.loadFromFile("../assets/hit.wav");

    m_score_sound.setBuffer(m_score_buffer);
    m_fly_sound.setBuffer(m_fly_buffer);
    m_hit_sound.setBuffer(m_hit_buffer);
}

void sound::play_score() { m_score_sound.play(); }

void sound::play_fly() { m_fly_sound.play(); }

void sound::play_hit() { m_hit_sound.play(); }
}  // namespace gh