//
// MIT License
//
// Copyright (c) 2023 Yunus Emre Aydın
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include <SFEX/Graphics/Animation.hpp>

namespace sfex
{

Animation::Animation(): m_currentIndex(0), m_loop(true), m_animationSpeed(1.0f), m_stopwatch(), m_spritePtr(nullptr), m_frames()
{
}

Animation::Animation(sf::Sprite& sprite, bool loop): m_currentIndex(0), m_animationSpeed(1.0f), m_loop(loop), m_stopwatch(), m_spritePtr(&sprite), m_frames()
{
    if(!loop)
    {
        pause();
        restart();
    }
}

void Animation::setLoop(bool loop)
{
    m_loop = loop;
}

bool Animation::getLoop()
{
    return m_loop;
}

void Animation::setAnimationSpeed(float animSpeed)
{
    m_animationSpeed = animSpeed;
}

float Animation::getAnimationSpeed()
{
    return m_animationSpeed;
}

void Animation::autoGenerateFrames(const sf::IntRect &topleftRect, const sf::Time& duration)
{
    if(!m_spritePtr) return;

    clearFrames();
    int left = topleftRect.left;
    int top = topleftRect.top;
    int rect_width = topleftRect.width;
    int rect_height = topleftRect.height;

    std::size_t width = m_spritePtr->getTexture()->getSize().x - left;
    std::size_t height = m_spritePtr->getTexture()->getSize().y - top;

    std::size_t frame_count_x = (width / rect_width);
    std::size_t frame_count_y = (height / rect_height);
    m_frames.reserve(frame_count_x * frame_count_y);

    for(std::size_t y = 0; y < frame_count_y; y++)
    {
        for(std::size_t x = 0; x < frame_count_x; x++)
        {
            m_frames.push_back({sf::IntRect(left + x*rect_width, top + y*rect_height, rect_width, rect_height), duration});
        }
    }
    setFrameIndex(0);
}

void Animation::insertFrame(const sf::IntRect &rect, const sf::Time& duration, std::size_t index)
{
    insertFrame({rect, duration}, index);
}

void Animation::insertFrame(const Frame& frame, std::size_t index)
{
    if(index >= m_frames.size())
    {
        if(m_frames.empty())
        {
            restart();
            setFrameIndex(0);
        }

        m_frames.push_back(frame);
    }
    else
    {
        m_frames[index] = frame;
    }
}

void Animation::removeFrame(std::size_t index)
{
    if(index >= m_frames.size()) return;
    m_frames.erase(m_frames.begin() + index);
}

void Animation::clearFrames()
{
    m_currentIndex = 0;
    m_frames.clear();
}

void Animation::setFrameIndex(std::size_t index)
{
    if(!m_spritePtr) return;

    m_currentIndex = index;
    restart();
    if(m_currentIndex >= m_frames.size())
    {
        if(!m_loop)
        {
            pause();
            restart();
        }
        m_currentIndex = 0;
    }
    else
        m_spritePtr->setTextureRect(m_frames[m_currentIndex].rect);
}

void Animation::update()
{
    if(m_frames.empty()) return;

    if(m_animationSpeed > 0 && m_stopwatch.getElapsedTime() * m_animationSpeed >= m_frames[m_currentIndex].duration)
    {
        setFrameIndex(m_currentIndex + 1);
    }
    else if(m_animationSpeed < 0 && m_stopwatch.getElapsedTime() * -m_animationSpeed >= m_frames[m_currentIndex].duration)
    {
        if(m_currentIndex == 0) m_currentIndex = m_frames.size();
        setFrameIndex(m_currentIndex - 1);
    }
}

void Animation::pause()
{
    m_stopwatch.pause();
}

void Animation::play()
{
    m_stopwatch.resume();
    m_spritePtr->setTextureRect(m_frames[m_currentIndex].rect);
}

void Animation::restart()
{
    m_stopwatch.restart();
}

bool Animation::isPaused()
{
    return m_stopwatch.isPaused();
}

}