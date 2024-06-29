// ProgressBar.h

#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <string>

/**
 * @class ProgressBar
 * @brief Editable string progress bar.
 */
class ProgressBar
{
private:
    int _units;
    int _percentage;
    int _barWidth;
    std::string _emptyChar;
    std::string _fullChar;
    std::string _firstEdgeOverride[2];
    std::string _lastEdgeOverride[2];
    struct
    {
        bool isCharSplit;
        std::string charSplit;
    } _split;

    std::string bar;
    std::string barArray;

public:
    /**
     * @brief Constructor to initialize the ProgressBar object.
     * @param percentage How much of the progress bar should be filled (a number between 1 and 100).
     * @param barWidth How long should the bar be?
     * @param emptyChar What should be displayed for parts of the bar that are empty.
     * @param fullChar What should be displayed for parts of the bar that are filled.
     * @param firstEdgeOverride Override first bar char with something else. Make sure it is similar to this {"emptyChar", "fullChar"}.
     * @param lastEdgeOverride Override last bar char with something else. Make sure it is similar to this {"emptyChar", "fullChar"}.
     */
    ProgressBar(int percentage, int barWidth, std::string emptyChar, std::string fullChar, std::string firstEdgeOverride[], std::string lastEdgeOverride[]);

    void updateBar();
    void charSplit(std::string charSplit);

    void setPercentage(int percentage);
    int getPercentage() const;

    void setBarWidth(int barWidth);
    int getBarWidth() const;

    void setEmptyChar(std::string emptyChar);
    std::string getEmptyChar() const;

    void setFullChar(std::string fullChar);
    std::string getFullChar() const;

    void setFirstEdgeOverride(std::string firstEdgeOverride[2]);
    std::string *getFirstEdgeOverride();

    void setLastEdgeOverride(std::string lastEdgeOverride[2]);
    std::string *getLastEdgeOverride();

    std::string getBar() const;
};

#endif // PROGRESSBAR_H
