#define _CRT_SECURE_NO_WARNINGS
#include "List.h"
#include "tweet.h"
#include <iostream>
using namespace std;

int main(void)
{
    List<tweet> Tweets;
    string      Text;

    Tweets.format("Tweet\n--->\n", "\n", "\n--->\n");
    while (true)
    {
        cout << "\nNachricht: ";
        cin >> Text;
        if (Text == "quit")
            break;
        Tweets.insertFront(tweet(Text));

        cout << Tweets;
    }

    return 0;
}