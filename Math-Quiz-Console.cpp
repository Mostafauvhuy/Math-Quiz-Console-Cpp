#include <iostream>
#include <string>
#include <cmath>
#include <queue>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;
enum enlevels
{
    easy = 1,
    mid = 2,
    hard = 3,
    L_mix = 4
};
enum enOpType
{
    add = 1,
    sub = 2,
    mul = 3,
    divi = 4,
    mix = 5
};

struct stGameInfo
{

    short NumOfQuestion = 0;
    enlevels level;
    enOpType OPtype;
    short NumOfRightAnswer = 0;
    short NumOfWrongAnswer = 0;
};

int RandomNumber(int form, int to)
{
    int randomNum;

    randomNum = rand() % (to - form + 1) + form;

    return randomNum;
}

int enterAnswer()
{
    int number;
    cin >> number;
    return number;
}

int howManyQuestion(string message)
{
    int number;
    cout << message << endl;
    cin >> number;

    return number;
}

int enterQuestionLevel()
{
    int number;
    cout << "easy=[1],mid=[2],hard=[3],mix=[4] ? ";
    cin >> number;

    return number;
}

int enterOpType()
{
    int number;
    cout << "add = 1,sub=2,mul=3,div=4,mix=5 ? ";
    cin >> number;

    return number;
}

enlevels getyourLevelchoise(int num)
{

    return enlevels(num);
}

enOpType getyourOpTypechoise(int num)
{

    return enOpType(num);
}

int calactExptation(int num, int num2, enOpType op)
{
    switch (op)
    {
    case enOpType::add:
        return (num + num2);
    case enOpType::sub:
        return (num - num2);
    case enOpType::divi:
        return (num / num2);
    case enOpType::mul:
        return (num * num2);
    }
}

enOpType whatoptypeplayerchoise(enOpType Optype)
{
    switch (Optype)
    {
    case enOpType::add:
        return enOpType::add;
    case enOpType::divi:
        return enOpType::divi;
    case enOpType::mul:
        return enOpType::mul;
    case enOpType::sub:
        return enOpType::sub;
    case enOpType::mix:
        return getyourOpTypechoise(RandomNumber(1, 4));
    }
}

string Opname(enOpType op)
{
    string opetor[5] = {"+", "-", "*", "/", "mix"};
    return (opetor[op - 1]);
}

string LevelNume(enlevels enlevel)
{
    string opetor[4] = {"easy", "mid", "hard", "mix"};
    return (opetor[enlevel - 1]);
}

int giveNumAccordingLevel(enlevels level)
{
    int num;
    if (level == enlevels::easy)
    {
        num = RandomNumber(1, 10);
    }
    else if (level == enlevels::mid)
    {
        num = RandomNumber(10, 50);
    }
    else if (level == enlevels::hard)
    {
        num = RandomNumber(50, 100);
    }
    else if (level == enlevels::L_mix)
    {
        num = RandomNumber(1, 100);
    }
    return num;
}

bool AreAnswerCorrect(int result, int yourAnswr)
{
    return (result == yourAnswr);
}

void showQuestion(int num1, int num2, enOpType op, int numOfQuestion)
{
    string charOp = Opname(op);
    cout << endl
         << "the question No" << numOfQuestion << endl
         << num1 << endl
         << charOp << endl
         << num2 << endl;
}

void getQuestion(enlevels level, enOpType Optype, int &result, int numOfQuestion)
{
    int num1 = giveNumAccordingLevel(level);
    int num2 = giveNumAccordingLevel(level);
    enOpType op = whatoptypeplayerchoise(Optype);
    result = calactExptation(num1, num2, op);
    showQuestion(num1, num2, op, numOfQuestion);
}

void ShowWhanCorrectAnswered()
{
    cout << "your answer is correct :)";
    system("color 2f");
}

void ShowWhanInCorrectAnswered(int corectAnswer)
{
    cout << "your answer is incorrect :(" << endl;
    system("color 4f");
    cout << "the correct answer is " << corectAnswer;
}

bool arepassQuestion(stGameInfo gameInfo)
{
    return (gameInfo.NumOfRightAnswer >= gameInfo.NumOfWrongAnswer);
}

void signOfGame(bool arepass)
{
    if (arepass)
    {
        cout << endl
             << endl
             << endl
             << "\n-------------------------------------------------------" << endl;
        cout << "               you passed the question :)" << endl;
        cout << "---------------------------------------------------------" << endl;
        system("color 2f");
    }
    else
    {
        cout << endl
             << endl
             << endl
             << "\n--------------------------------------------------------" << endl;
        cout << "                you failed the question :(" << endl;
        cout << "\a--------------------------------------------------------" << endl;
        system("color 4f");
    }
}

void showFainalQuestionResult(stGameInfo gameInfo)
{

    signOfGame(arepassQuestion(gameInfo));

    cout << endl
         << "-------------------------------------------------------\n";
    cout << "             num of question  = " << gameInfo.NumOfQuestion << endl;
    cout << "             Type of opartor  = " << Opname(gameInfo.OPtype) << endl;
    cout << "             question level  = " << LevelNume(gameInfo.level) << endl;
    cout << "             num of right ans = " << gameInfo.NumOfRightAnswer << endl;
    cout << "             num of wrong ans = " << gameInfo.NumOfWrongAnswer << endl;
    cout << endl
         << "-------------------------------------------------------\n";
}

void game()
{
    stGameInfo gameInfo;
    int QuestionNum = howManyQuestion("how many questions you want to answer ?");
    enlevels level = getyourLevelchoise(enterQuestionLevel());
    enOpType Optype = getyourOpTypechoise(enterOpType());
    int result;
    for (int i = 1; i <= QuestionNum; i++)
    {

        result = 0;
        getQuestion(level, Optype, result, i);
        int yourAnswr = enterAnswer();

        if (AreAnswerCorrect(result, yourAnswr))
        {
            gameInfo.NumOfRightAnswer++;

            ShowWhanCorrectAnswered();
        }
        else
        {
            gameInfo.NumOfWrongAnswer++;
            ShowWhanInCorrectAnswered(result);
        }
    }

    gameInfo.level = level;
    gameInfo.OPtype = Optype;
    gameInfo.NumOfQuestion = QuestionNum;

    showFainalQuestionResult(gameInfo);
}

int main()
{
    game();
}
