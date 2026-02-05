#include <iostream>
#include <string>
#include <cmath>
#include <queue>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iomanip>

#include <thread> // sleep_for
#include <chrono> // seconds
// #include <windows.h> // system("cls")

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

struct stStudentInfo
{

    string FullName;
    int Age;
    string ID;
    bool six;
    int TotalMark = 0;
};

struct stQustionInfo
{
    short QuestionNumber = 0;
    int FirstNum = 0;
    int SecondNum = 0;
    enlevels Questionlevel = enlevels::easy;
    enOpType QuestionOPtype = enOpType::add;
    int correctAnswer = 0;
    int StudentAnswer = 0;
    bool isStudentAnswerCorrect = true;
};

struct stQuizInfo
{

    stQustionInfo Qustion[100];
    stStudentInfo StudentInfo[100];
    short NumOfQuestion = 0;
    short NumOfStudent = 0;
    enlevels Quizlevel = enlevels::easy;
    enOpType QuizOPtype = enOpType::add;
    short NumOfRightAnswer = 0;
    short NumOfWrongAnswer = 0;
    bool IsPass = true;
};

// functions of strudent info

string getStudentName()
{
    string FullName;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "enter your FullName : ";
    getline(cin, FullName);

    return FullName;
}

int getStudentAge()
{
    int age = 18;
    cout << "enter your age (>18) : ";
    cin >> age;
    while (age <= 18)
    {
        cout << "\nplease enter age > 18 : ";
        cin >> age;
    }
    return age;
}

string getStusentId()
{
    string Id;
    cout << "enter your Id : ";
    cin >> Id;
    return Id;
}

bool getStudentSix()
{

    bool six = true;
    cout << "enter your six (male[1] and female[0])  1/0: ";
    cin >> six;
    return six;
}

int HowManyStudent()
{
    int NumOfStudent = 1;

    do
    {

        cout << "How many students do you want to teach them?[1:100] ";
        cin >> NumOfStudent;

    } while (NumOfStudent < 0 && NumOfStudent > 100);

    return NumOfStudent;
}

int RandomNumber(int form, int to)
{
    int randomNum;

    randomNum = rand() % (to - form + 1) + form;

    return randomNum;
}

int getStudentAnswer()
{
    int number = 0;
    cin >> number;
    return number;
}

int howManyQuestion()
{
    int number;
    cout << "how many questions you want to answer ? ";
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

string tab(int numoftab)
{
    string tab = "";
    while (numoftab--)
    {
        tab += "    ";
    }
    return tab;
}

enlevels getLevelQuiz()
{

    return enlevels(enterQuestionLevel());
}

enOpType getyOpTypeQuiz(int num)
{

    return enOpType(num);
}

int CalculateExpression(int num, int num2, enOpType op)
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

enOpType whatOptypeOfQuestion(enOpType Optype)
{
    if (Optype == enOpType::mix)
    {
        return getyOpTypeQuiz(RandomNumber(1, 4));
    }
    else
    {
        return Optype;
    }
}

string getOpSymbol(enOpType op)
{
    string opetor[5] = {"+", "-", "*", "/", "mix"};
    return (opetor[op - 1]);
}

string LevelNume(enlevels enlevel)
{
    string opetor[4] = {"easy", "mid", "hard", "mix"};
    return (opetor[enlevel - 1]);
}

int getNumAccordingLevel(enlevels level)
{
    int num = 5;
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

bool isAnswerCorrect(int correctAnswer, int StudentAnswr)
{
    return (correctAnswer == StudentAnswr);
}

void showQuestion(stQustionInfo QustionInfo, short numQuestion)
{
    string symbolOp = getOpSymbol(QustionInfo.QuestionOPtype);
    cout << endl
         << "the question No" << numQuestion + 1 << endl
         << QustionInfo.FirstNum << endl
         << symbolOp << endl
         << QustionInfo.SecondNum << endl
         << "_______________\n";
}

void ViewQuestionStatus(stQustionInfo QustionInfo)
{
    if (QustionInfo.isStudentAnswerCorrect)
    {
        cout << "your answer is correct :)";
        system("color 2f");
    }
    else
    {
        cout << "your answer is incorrect :(" << endl;
        system("color 4f");
        cout << "the correct answer is " << QustionInfo.correctAnswer;
    }
}

bool ispassQuiz(stQuizInfo &QuizInfo)
{
    return (QuizInfo.IsPass = (QuizInfo.NumOfRightAnswer >= QuizInfo.NumOfWrongAnswer));
}

void signOfFinalQuiz(bool ispass)
{
    cout << endl
         << tab(5) << string(60, '-') << endl;

    if (ispass)
    {
        cout << tab(7) << left << setw(30) << "Result"
             << " : You passed the quiz :)" << endl;
        system("color 2f");
    }
    else
    {
        cout << tab(7) << left << setw(30) << "Result"
             << " : You failed the quiz :(" << endl;
        system("color 4f");
    }

    cout << tab(5) << string(60, '-') << endl;
}

string NameOfSix(bool Six)
{
    if (Six)
    {
        return "male";
    }
    else
    {
        return "female";
    }
}

void showStudentInfo(stStudentInfo StusentInfo, int numOfStudent)
{
    cout << "\n"
         << tab(5) << " -------------------- Student [" << numOfStudent + 1 << "] -------------------- \n\n";

    cout << tab(7) << left << setw(15) << "Full Name" << " : " << StusentInfo.FullName << endl;
    cout << tab(7) << left << setw(15) << "Age" << " : " << StusentInfo.Age << endl;
    cout << tab(7) << left << setw(15) << "ID" << " : " << StusentInfo.ID << endl;
    cout << tab(7) << left << setw(15) << "Gender" << " : " << NameOfSix(StusentInfo.six) << endl;

    cout << "\n"
         << tab(5) << " -------------------------------------------------------\n";
}

void ShowFinalQuizResult(stQuizInfo QuizInfo, int numStudent)
{

    signOfFinalQuiz(ispassQuiz(QuizInfo));
    showStudentInfo(QuizInfo.StudentInfo[numStudent], numStudent);

    cout << endl
         << tab(5) << string(55, '-') << "\n";
    cout << tab(7) << left << setw(20) << "Number of Questions"
         << " : " << QuizInfo.NumOfQuestion << endl;

    cout << tab(7) << left << setw(20) << "Operator Type"
         << " : " << getOpSymbol(QuizInfo.QuizOPtype) << endl;

    cout << tab(7) << left << setw(20) << "Question Level"
         << " : " << LevelNume(QuizInfo.Quizlevel) << endl;

    cout << tab(7) << left << setw(20) << "Right Answers"
         << " : " << QuizInfo.NumOfRightAnswer << endl;

    cout << tab(7) << left << setw(20) << "Wrong Answers"
         << " : " << QuizInfo.NumOfWrongAnswer << endl;

    cout << tab(5) << string(55, '-') << "\n";
}

stStudentInfo getStudentInfo(stStudentInfo &StusentInfo)
{
    stStudentInfo StudentInfo;
    StudentInfo.FullName = getStudentName();
    StudentInfo.Age = getStudentAge();
    StudentInfo.ID = getStusentId();
    StudentInfo.six = getStudentSix();

    return StudentInfo;
}

stQustionInfo GenerateQuestion(enlevels level, enOpType optype, int i)
{
    stQustionInfo QustionInfo;

    QustionInfo.FirstNum = getNumAccordingLevel(level);
    QustionInfo.SecondNum = getNumAccordingLevel(level);
    QustionInfo.QuestionOPtype = getyOpTypeQuiz(whatOptypeOfQuestion(optype));
    QustionInfo.correctAnswer = CalculateExpression(QustionInfo.FirstNum, QustionInfo.SecondNum, QustionInfo.QuestionOPtype);
    showQuestion(QustionInfo, i);
    QustionInfo.StudentAnswer = getStudentAnswer();
    QustionInfo.isStudentAnswerCorrect = isAnswerCorrect(QustionInfo.correctAnswer, QustionInfo.StudentAnswer);

    return QustionInfo;
}

void UpdataToNumOfCorrectAnsAndnot(stQuizInfo &QuizInfo, short numQuestion)
{

    if (QuizInfo.Qustion[numQuestion].isStudentAnswerCorrect)
    {
        QuizInfo.NumOfRightAnswer++;
    }
    else
    {
        QuizInfo.NumOfWrongAnswer++;
    }
}

void GenerateQuiz(stQuizInfo &QuizInfo)
{

    for (int i = 0; i < QuizInfo.NumOfQuestion; i++)
    {

        QuizInfo.Qustion[i] = GenerateQuestion(QuizInfo.Quizlevel, QuizInfo.QuizOPtype, i);
        ViewQuestionStatus(QuizInfo.Qustion[i]);
        UpdataToNumOfCorrectAnsAndnot(QuizInfo, i);
    }
}

void displayMarksAllStudent(stQuizInfo QuizInfo)
{
    cout << left << setw(20) << "Name"
         << setw(10) << "Marks"
         << setw(15) << "ID"
         << setw(10) << "Gender" << endl;

    cout << string(55, '-') << endl;

    for (int i = 0; i < QuizInfo.NumOfStudent; i++)
    {
        cout << left << setw(20) << QuizInfo.StudentInfo[i].FullName
             << setw(10) << QuizInfo.StudentInfo[i].TotalMark
             << setw(15) << QuizInfo.StudentInfo[i].ID
             << setw(10) << NameOfSix(QuizInfo.StudentInfo[i].six)
             << endl;
    }
}

void game()
{
    stQuizInfo QuizInfo;

    cout << "        enter  Quiz info        " << endl;
    QuizInfo.NumOfStudent = HowManyStudent();
    QuizInfo.NumOfQuestion = howManyQuestion();
    QuizInfo.QuizOPtype = getyOpTypeQuiz(enterOpType());
    QuizInfo.Quizlevel = getLevelQuiz();

    system("cls");

    for (int i = 0; i < QuizInfo.NumOfStudent; i++)
    {

        QuizInfo.StudentInfo[i] = getStudentInfo(QuizInfo.StudentInfo[i]);
        GenerateQuiz(QuizInfo);
        QuizInfo.StudentInfo[i].TotalMark = QuizInfo.NumOfRightAnswer;
        ShowFinalQuizResult(QuizInfo, i);
        QuizInfo.NumOfRightAnswer = 0;
        QuizInfo.NumOfWrongAnswer = 0;

        this_thread::sleep_for(chrono::seconds(5)); // يوقف خمس ثواني

        system("cls");
    }

    char display = 'y';

    cout << "do you want display marks all students ? ";
    cin >> display;
    if (display == 'y' || display == 'Y')
    {

        displayMarksAllStudent(QuizInfo);
    }
}

int main()
{
    srand((unsigned)(time(NULL)));
    game();
}
