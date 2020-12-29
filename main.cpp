#include<bits/stdc++.h>

using namespace std;

double blockProb(int serverNum, int queueNum, double lambda, double mu) {
    /* 1000000 */
    double timeUnit = 0.01;
    double inProb = 1 - exp((-lambda) * timeUnit);
    int totalArrival = 0;
    int blockCnt = 0;
    int currInServed = 0;
    int currInQueue = 0;
    srand(time(NULL));
    for(double time = 0; time < 1000; time += timeUnit) {
        double outProb = 1- exp((-mu) * timeUnit * currInServed);
        if(currInServed > 0 && (double)rand() / RAND_MAX <= outProb) {
            // go out
            currInServed--;
            if(currInQueue > 0) {
                // pop queue
                currInQueue--;
                currInServed++;
            }
        }
        if((double)rand() / RAND_MAX <= inProb) {
            // come in
            totalArrival++;
            if(currInServed < serverNum)
                currInServed++;
            else if(currInQueue < queueNum)
                currInQueue++;
            else
                blockCnt++;
        }
    }
    return (double)blockCnt / totalArrival;
}

double averageBlockProb(int serverNum, int queueNum, double lambda, double mu) {
    double avg = 0;
    for(int i = 0; i < 10; i++) {
        avg += blockProb(serverNum, queueNum, lambda, mu);
    }
    return (double)avg / 10;
}

int main() {
    ofstream fout;
    fout.precision(6);
    int sArr[] = {1, 5, 10};
    int i = 1, j = 1;

    /* queue = 0 */
    fout.open("queue_0.txt");
    fout << setw(82) << setfill('-') << '\n';
    fout << "   " << setw(26) << setfill(' ') << "S=1|" << setw(26) << "S=5|" << setw(27) << "S=10|\n";
    fout << setw(82) << setfill('-') << '\n';
    fout << "   " << setw(13) << setfill(' ') << "lambda/mu|" << setw(13) << "BP|" << setw(13) << "lambda/mu|" << setw(13) << "BP|" << setw(13) << "lambda/mu|" << setw(14) << "BP|\n";
    fout << setw(82) << setfill('-') << '\n';
    for(double lambda = 0.01; lambda <= 10; lambda *= 10) {
        for(double mu = 0.01; mu <= 10.24; mu *= 4) {
            fout << setw(2) << setfill(' ') << i++ << ") ";
            for(auto& s: sArr) {
                fout << setw(11) << setfill(' ') << fixed << lambda / mu << "| ";
                fout << setw(11) << setfill(' ') << fixed << averageBlockProb(s, 0, lambda, mu) << "| ";
            }
            fout << '\n';
            fout << setw(82) << setfill('-') << '\n';
        }
    }
    fout.close();

    /* queue = s */
    fout.open("queue_s.txt");
    fout << setw(82) << setfill('-') << '\n';
    fout << "   " << setw(26) << setfill(' ') << "S=1|" << setw(26) << "S=5|" << setw(27) << "S=10|\n";
    fout << setw(82) << setfill('-') << '\n';
    fout << "   " << setw(13) << setfill(' ') << "lambda/mu|" << setw(13) << "BP|" << setw(13) << "lambda/mu|" << setw(13) << "BP|" << setw(13) << "lambda/mu|" << setw(14) << "BP|\n";
    fout << setw(82) << setfill('-') << '\n';
    for(double lambda = 0.01; lambda <= 10; lambda *= 10) {
        for(double mu = 0.01; mu <= 10.24; mu *= 4) {
            fout << setw(2) << setfill(' ') << j++ << ") ";
            for(auto& s: sArr) {
                fout << setw(11) << setfill(' ') << fixed << lambda / mu << "| ";
                fout << setw(11) << setfill(' ') << fixed << averageBlockProb(s, s, lambda, mu) << "| ";
            }
            fout << '\n';
            fout << setw(82) << setfill('-') << '\n';
        }
    }
    fout.close();
}
