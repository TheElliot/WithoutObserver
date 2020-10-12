#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <math.h>

using namespace std;

class CalcScoreDisplay {
    private:
        float runRate;

    public:
        void update(int runs, int hits,
                float win_average) {

            runRate = (hits > 0) ? (ceilf(((float)runs/(float)hits)*1000)/1000) : 0;
            display();
        }

        void display() {
            cout << "\nRuns Per Hit: \n" << runRate << "\n";
        }
};

// A class to display score. Data of this class is
// updated by SportsData
class CurrentScoreDisplay {
    private:
        int runs, hits;
        float win_average;

    public:
        void update(int new_runs, int new_hits,
                    float new_win_average) {
                runs = new_runs;
                hits = new_hits;
                win_average = new_win_average;
                display();
        }

        void display() {
            cout << "\nCurrent Score Display:\n" << "Runs: ";
            cout << runs << "\nHits:" << hits;
            cout << "\nWin Average: " << win_average << "\n";
        }
};

class SportsData {
    private:
        int data_runs, data_hits;
        float data_win_average;
        CurrentScoreDisplay *currentScoreDisplay;
        CalcScoreDisplay *calcScoreDisplay;

    public:
        SportsData(CurrentScoreDisplay *new_cur_score_display,
                   CalcScoreDisplay *new_calc_score_display) {
            currentScoreDisplay = new_cur_score_display;
            calcScoreDisplay = new_calc_score_display;
            srand(time(0));
        }

        // This method is used update displays when data changes
        void dataChanged() {
            //get latest data
            data_hits = getLatestHits();
            data_runs = getLatestRuns();
            data_win_average = getLatestWinAverage();

            currentScoreDisplay->update(data_runs, data_hits, data_win_average);
            calcScoreDisplay->update(data_runs, data_hits, data_win_average);
        }

    private:
        int getLatestRuns() {
                int value = rand() % 10;
                return (value > data_hits) ? data_hits : value;
        }


        int getLatestHits() {
                return (rand() % 10);
        }

        // get latest win_average from stadium
        float getLatestWinAverage() {
                return floorf(((float) rand() / (RAND_MAX)) * 1000) / 1000;
        }
};



int main() {
    // Create objects for testing
    CalcScoreDisplay calcScoreDisplay = CalcScoreDisplay();
    CurrentScoreDisplay currentScoreDisplay = CurrentScoreDisplay();

    // Pass the displays to Sports data
    SportsData sportsData = SportsData(&currentScoreDisplay,
                                       &calcScoreDisplay);

    // In real app you would have some logic to call this
    // function when data changes
    sportsData.dataChanged();
}