// ProgressBar.cpp

#include "ProgressBar.h"
#include <iostream>
#include <cmath>

ProgressBar::ProgressBar(int percentage, int barWidth, std::string emptyChar, std::string fullChar, std::string firstEdgeOverride[], std::string lastEdgeOverride[])
{
    // Initialize member variables
    _percentage = percentage;
    _barWidth = barWidth;
    _emptyChar = emptyChar;
    _fullChar = fullChar;
    _firstEdgeOverride[0] = firstEdgeOverride[0];
    _firstEdgeOverride[1] = firstEdgeOverride[1];
    _lastEdgeOverride[0] = lastEdgeOverride[0];
    _lastEdgeOverride[1] = lastEdgeOverride[1];

    // Update the progress bar
    updateBar();
}

void ProgressBar::updateBar()
{
    _units = std::floor((_percentage / 100.0) * _barWidth);
    std::string barArray;

    for (int i = 0; i < _barWidth; ++i)
    {
        std::string currentChar;
        if (i < _units)
        {
            if (_firstEdgeOverride[0] != "" && _lastEdgeOverride[0] != "" && _units == 100)
            {
                i == 0 ? currentChar = _firstEdgeOverride[0] : i == _barWidth - 1 ? currentChar = _lastEdgeOverride[0]
                                                                                  : currentChar = _fullChar;
            }
            else
            {
                currentChar = _fullChar;
            }
        }
        else
        {
            if (_firstEdgeOverride[1] != "" && _lastEdgeOverride[1] != "" && _units == 100)
            {
                i == 0 ? currentChar = _firstEdgeOverride[1] : i == _barWidth - 1 ? currentChar = _lastEdgeOverride[1]
                                                                                  : currentChar = _emptyChar;
            }
            else
            {
                currentChar = _emptyChar;
            }
        }
        barArray += currentChar;
    }

    bar = barArray;
}

void ProgressBar::charSplit(std::string charSplit)
{
    if (_lastEdgeOverride[0] != "" && _percentage == 100)
    {
        return;
    }

    if (!_split.isCharSplit)
    {
        _split.isCharSplit = true;
        _split.charSplit = charSplit;
    }

    if (charSplit != _split.charSplit)
    {
        _split.charSplit = charSplit;
    }

    barArray[_units - 1] = charSplit[0];
    bar = barArray;
}

// Implement getters and setters
void ProgressBar::setPercentage(int percentage)
{
    if (percentage > 100 || percentage < 0)
    {
        throw std::invalid_argument("Invalid percentage value");
    }
    _percentage = percentage;
    updateBar();
}

int ProgressBar::getPercentage() const
{
    return _percentage;
}

void ProgressBar::setBarWidth(int barWidth)
{
    if (barWidth <= 0)
    {
        throw std::invalid_argument("Invalid barWidth value");
    }
    _barWidth = barWidth;
    updateBar();
}

int ProgressBar::getBarWidth() const
{
    return _barWidth;
}

void ProgressBar::setEmptyChar(std::string emptyChar)
{
    _emptyChar = emptyChar;
    updateBar();
}

std::string ProgressBar::getEmptyChar() const
{
    return _emptyChar;
}

void ProgressBar::setFullChar(std::string fullChar)
{
    _fullChar = fullChar;
    updateBar();
}

std::string ProgressBar::getFullChar() const
{
    return _fullChar;
}

void ProgressBar::setFirstEdgeOverride(std::string firstEdgeOverride[2])
{
    _firstEdgeOverride[0] = firstEdgeOverride[0];
    _firstEdgeOverride[1] = firstEdgeOverride[1];
    updateBar();
}

std::string *ProgressBar::getFirstEdgeOverride()
{
    return _firstEdgeOverride;
}

void ProgressBar::setLastEdgeOverride(std::string lastEdgeOverride[2])
{
    _lastEdgeOverride[0] = lastEdgeOverride[0];
    _lastEdgeOverride[1] = lastEdgeOverride[1];
    updateBar();
}

std::string *ProgressBar::getLastEdgeOverride()
{
    return _lastEdgeOverride;
}

std::string ProgressBar::getBar() const
{
    return bar;
}
