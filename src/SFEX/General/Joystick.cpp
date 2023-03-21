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

#include <SFEX/General/Joystick.hpp>

namespace sfex
{

struct JoystickPairHash;
std::unordered_map<std::pair<unsigned int, unsigned int>, bool, Joystick::JoystickPairHash> Joystick::m_buttonsForDown;
std::unordered_map<std::pair<unsigned int, unsigned int>, bool, Joystick::JoystickPairHash> Joystick::m_buttonsForUp;

bool Joystick::isConnected(unsigned int joystick)
{
    return sf::Joystick::isConnected(joystick);
}

unsigned int Joystick::getButtonCount(unsigned int joystick)
{
    return sf::Joystick::getButtonCount(joystick);
}

bool Joystick::hasAxis(unsigned int joystick, Axis axis)
{
    return sf::Joystick::hasAxis(joystick, axis);
}

bool Joystick::getButton(unsigned int joystick, unsigned int button)
{
    return sf::Joystick::isButtonPressed(joystick, button);
}

bool Joystick::getButtonDown(unsigned int joystick, unsigned int button)
{
    if(Joystick::m_buttonsForDown[{joystick, button}])
    {
        Joystick::m_buttonsForDown[{joystick, button}] = Joystick::getButton(joystick, button);
        return false;
    }
    Joystick::m_buttonsForDown[{joystick, button}] = Joystick::getButton(joystick, button);
    return Joystick::m_buttonsForDown[{joystick, button}];
}

bool Joystick::getButtonUp(unsigned int joystick, unsigned int button)
{
    if(Joystick::m_buttonsForUp[{joystick, button}])
    {
        Joystick::m_buttonsForUp[{joystick, button}] = Joystick::getButton(joystick, button);
        return !Joystick::m_buttonsForUp[{joystick, button}];
    }
    Joystick::m_buttonsForUp[{joystick, button}] = Joystick::getButton(joystick, button);
    return false;
}

float Joystick::getAxisPosition(unsigned int joystick, Axis axis, float minSensitivity)
{
    if(!Joystick::hasAxis(joystick, axis)) return 0.0f;
    float axisPos = sf::Joystick::getAxisPosition(joystick, axis) / 100.0f;
    if(axisPos*axisPos < minSensitivity*minSensitivity) return 0.0f;
    return axisPos;
}

Joystick::Identification Joystick::getIdentification(unsigned int joystick)
{
    return sf::Joystick::getIdentification(joystick);
}

void Joystick::update()
{
    sf::Joystick::update();
}

} // namespace sfex