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
enum enGender
{
    male = 1,
    female = 0
};
enum enSelectionList
{
    enGenerateQuiz = 1,
    enQuizInfo = 2,
    enstartQuizz = 3,
    displayAllstudent = 4,
    quiryUsingID = 5,
    DeletStudentUsingID = 6,
    Exit = 7
};

struct stStudentInfo
{

    string FullName;
    int Age = 18;
    string ID;
    enGender Gender = enGender::male;
    int TotalMark = 0;
    bool IsPass = false;
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
    bool IsPass = false;
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
    cout << "enter your Id XXXX: ";
    cin >> Id;
    return Id;
}

enGender getStudentGender()
{

    int sex = 1;
    do
    {
        cout << "enter your sex (male[1] and female[0])  1/0: ";
        cin >> sex;

    } while (sex != 1 && sex != 0);

    return enGender(sex);
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

void ListofChoices()
{
    cout << string(55, '=') << "\n";
    cout << setw(30) << right << "=== The Menu ===" << "\n";
    cout << string(55, '=') << "\n\n";

    cout << left << setw(30) << "1. Generate Quiz"
         << "\n"
         << left << setw(30) << "2. Quiz Info"
         << "\n"
         << left << setw(30) << "3. Start Quiz"
         << "\n"
         << left << setw(30) << "4. Display All Students"
         << "\n"
         << left << setw(30) << "5. Query Using ID"
         << "\n"
         << left << setw(30) << "6. Delete Student Using ID"
         << "\n"
         << left << setw(30) << "7. Exit"
         << "\n";

    cout << string(30, '_') << endl;
}

int choiseSelectionList()
{
    int num = 1;
    do

    {

        ListofChoices();

        cin >> num;
        if (num > 7 || num < 1)
        {
            system("cls");

            cout << "plase enter number between [1:7] \n";
        }

    } while (num > 7 || num < 1);

    return num;
}

enSelectionList getSelectionList()
{

    return enSelectionList(choiseSelectionList());
}

int HowManyStudent()
{
    int NumOfStudent = 1;

    do
    {

        cout << "How many students do you want to teach them?[1:100] ";
        cin >> NumOfStudent;

    } while (NumOfStudent < 0 || NumOfStudent > 100);

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
    default:
        return (num + num2);
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

bool ispassQuiz(stQuizInfo QuizInfo)
{
    return ((QuizInfo.NumOfRightAnswer >= QuizInfo.NumOfWrongAnswer));
}

string GetWordSucceededOrFailed(bool ResultExam)
{
    if (ResultExam)
    {
        return "Succeeded";
    }
    else
    {
        return "Failed";
    }
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

string NameOfGender(enGender Sex)
{
    if (Sex == enGender::male)
    {
        return "male";
    }
    else
    {
        return "female";
    }
}

float CalculatePercentage(int Marks, int NumOfQustion)
{

    float percentage = ((float)Marks / NumOfQustion) * 100;

    return percentage;
}

void showStudentInfo(stQuizInfo QuizInfo, int numOfStudent)
{
    float percentage = CalculatePercentage(QuizInfo.StudentInfo[numOfStudent].TotalMark, QuizInfo.NumOfQuestion);

    cout << "\n"
         << tab(5) << " -------------------- Student [" << numOfStudent + 1 << "] -------------------- \n\n";

    cout << tab(7) << left << setw(15) << "Full Name" << " : " << QuizInfo.StudentInfo[numOfStudent].FullName << endl;
    cout << tab(7) << left << setw(15) << "Age" << " : " << QuizInfo.StudentInfo[numOfStudent].Age << endl;
    cout << tab(7) << left << setw(15) << "ID" << " : " << QuizInfo.StudentInfo[numOfStudent].ID << endl;
    cout << tab(7) << left << setw(15) << "Gender" << " : " << NameOfGender(QuizInfo.StudentInfo[numOfStudent].Gender) << endl;
    cout << tab(7) << left << setw(15) << "Mark" << " : " << QuizInfo.StudentInfo[numOfStudent].TotalMark << endl;
    cout << tab(7) << left << setw(15) << "percentage" << " : " << percentage << '%' << endl;
    cout << tab(7) << left << setw(15) << "Student status" << " : " << GetWordSucceededOrFailed(QuizInfo.StudentInfo[numOfStudent].IsPass) << endl;
    cout << "\n"
         << tab(5) << " -------------------------------------------------------\n";
}

void ShowFinalQuizResult(stQuizInfo QuizInfo, int numStudent)
{
    signOfFinalQuiz(ispassQuiz(QuizInfo));
    showStudentInfo(QuizInfo, numStudent);
}

void ShowQuizeInfo(stQuizInfo QuizInfo)
{

    cout << tab(5) << left << setw(20) << string(55, '=') << "\n";
    ;
    cout << tab(7) << left << setw(20) << "Basic information for the Quiz\n";
    cout << tab(5) << left << setw(20) << string(55, '=') << "\n";

    cout << endl
         << tab(5) << string(55, '-') << "\n";
    cout << tab(7) << left << setw(20) << "Number of Questions"
         << " : " << QuizInfo.NumOfQuestion << endl;

    cout << tab(7) << left << setw(20) << "Operator Type"
         << " : " << getOpSymbol(QuizInfo.QuizOPtype) << endl;

    cout << tab(7) << left << setw(20) << "Question Level"
         << " : " << LevelNume(QuizInfo.Quizlevel) << endl;

    cout << tab(5) << string(55, '-') << "\n";
}

stStudentInfo getStudentInfo(stStudentInfo &StusentInfo)
{
    stStudentInfo StudentInfo;
    StudentInfo.FullName = getStudentName();
    StudentInfo.Age = getStudentAge();
    StudentInfo.ID = getStusentId();
    StudentInfo.Gender = getStudentGender();

    return StudentInfo;
}

stQustionInfo CreateQuestion(enlevels level, enOpType optype)
{
    stQustionInfo QustionInfo;

    QustionInfo.FirstNum = getNumAccordingLevel(level);
    QustionInfo.SecondNum = getNumAccordingLevel(level);
    QustionInfo.QuestionOPtype = getyOpTypeQuiz(whatOptypeOfQuestion(optype));

    return QustionInfo;
}

int AskStudent(stQustionInfo QustionInfo, int i)
{
    showQuestion(QustionInfo, i);

    return getStudentAnswer();
}

stQustionInfo GenerateQuestion(enlevels level, enOpType optype, int i)
{
    stQustionInfo QustionInfo;

    QustionInfo = CreateQuestion(level, optype);
    QustionInfo.correctAnswer = CalculateExpression(QustionInfo.FirstNum, QustionInfo.SecondNum, QustionInfo.QuestionOPtype);
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

void GenerateQuizAndExamStudent(stQuizInfo &QuizInfo)
{

    for (int i = 0; i < QuizInfo.NumOfQuestion; i++)
    {

        QuizInfo.Qustion[i] = GenerateQuestion(QuizInfo.Quizlevel, QuizInfo.QuizOPtype, i);
        QuizInfo.Qustion[i].StudentAnswer = AskStudent(QuizInfo.Qustion[i], i);
        QuizInfo.Qustion[i].isStudentAnswerCorrect = isAnswerCorrect(QuizInfo.Qustion[i].correctAnswer, QuizInfo.Qustion[i].StudentAnswer);
        ViewQuestionStatus(QuizInfo.Qustion[i]);
        UpdataToNumOfCorrectAnsAndnot(QuizInfo, i);
    }
    QuizInfo.IsPass = ispassQuiz(QuizInfo);
}

void displayMarksAllStudent(stQuizInfo QuizInfo)
{

    cout << left << setw(20) << "Name"
         << setw(10) << "Marks"
         << setw(15) << "ID"
         << setw(10) << "Gender"
         << setw(15) << "percentage"
         << setw(15) << "Student status"
         << endl;

    cout << string(80, '-') << endl;

    for (int i = 0; i < QuizInfo.NumOfStudent; i++)
    {
        float percentage = CalculatePercentage(QuizInfo.StudentInfo[i].TotalMark, QuizInfo.NumOfQuestion);
        string spercentage = to_string(percentage) + "%";

        cout << left << setw(20) << QuizInfo.StudentInfo[i].FullName
             << setw(10) << QuizInfo.StudentInfo[i].TotalMark
             << setw(15) << QuizInfo.StudentInfo[i].ID
             << setw(10) << NameOfGender(QuizInfo.StudentInfo[i].Gender)
             << setw(15) << spercentage
             << setw(15) << GetWordSucceededOrFailed(QuizInfo.StudentInfo[i].IsPass)
             << endl;
    }
}

stQuizInfo ChoiseInfoQuiz()
{
    stQuizInfo QuizInfo;

    cout << "        enter  Quiz info        " << endl;
    QuizInfo.NumOfStudent = HowManyStudent();
    QuizInfo.NumOfQuestion = howManyQuestion();
    QuizInfo.QuizOPtype = getyOpTypeQuiz(enterOpType());
    QuizInfo.Quizlevel = getLevelQuiz();

    cout << "\nSuccessfully created the exam\n";

    return QuizInfo;
}

void startQuizz(stQuizInfo &QuizInfo)
{

    for (int i = 0; i < QuizInfo.NumOfStudent; i++)
    {

        QuizInfo.StudentInfo[i] = getStudentInfo(QuizInfo.StudentInfo[i]);
        GenerateQuizAndExamStudent(QuizInfo);
        QuizInfo.StudentInfo[i].TotalMark = QuizInfo.NumOfRightAnswer;
        QuizInfo.StudentInfo[i].IsPass = QuizInfo.IsPass;
        ShowFinalQuizResult(QuizInfo, i);
        QuizInfo.NumOfRightAnswer = 0;
        QuizInfo.NumOfWrongAnswer = 0;
        QuizInfo.IsPass = false;

        this_thread::sleep_for(chrono::seconds(5)); // يوقف خمس ثواني

        system("cls");
    }
    cout << tab(7) << "Exams are over\n";
}

string enterIdStudent(string message)
{
    string ID;
    cout << message;
    cin >> ID;
    return ID;
}

int SearchPostionStudent(stQuizInfo QuizInfo, string ID)
{
    for (int i = 0; i < QuizInfo.NumOfStudent; i++)
    {
        if (QuizInfo.StudentInfo[i].ID == ID)
        {
            return i;
        }
    }
    return -1;
}

void displayInfoStudentUsingID(stQuizInfo QuizInfo, string ID)
{
    int pos = SearchPostionStudent(QuizInfo, ID);

    if (pos == -1)
    {
        cout << "the student is not exist\n";
        return;
    }
    showStudentInfo(QuizInfo, pos);
}

void deleteStudentUsingID(stQuizInfo &QuizInfo, string ID)
{
    int pos = SearchPostionStudent(QuizInfo, ID);
    if (pos == -1)
    {
        cout << "the student is not found !!!\n";
        return;
    }
    for (int i = pos; i < QuizInfo.NumOfStudent - 1; i++)
    {
        QuizInfo.StudentInfo[i] = QuizInfo.StudentInfo[i + 1];
    }

    QuizInfo.NumOfStudent--;

    cout << tab(7) << "Deleted successfully\n";
}

bool AskIfSureDeleteStudent(stQuizInfo &QuizInfo, string ID)
{

    char sure = 'y';

    displayInfoStudentUsingID(QuizInfo, ID);

    cout << "\nare you sure you want to delete student [y/n]? ";
    cin >> sure;
    while (sure == 'Y' || sure == 'y')
    {
        return true;
    }
    return false;
}

void Game()
{
    stQuizInfo QuizInfo;
    char backOprions = 'n';

    bool IsQuizExist = false;
    bool DidStudentTakeExam = false;
    do
    {
        system("cls");
        enSelectionList SelectionList = getSelectionList();

        switch (SelectionList)

        {
        case enSelectionList::enGenerateQuiz:
            QuizInfo = ChoiseInfoQuiz();
            IsQuizExist = true;
            break;
        case enSelectionList::enQuizInfo:
            if (IsQuizExist)
            {
                ShowQuizeInfo(QuizInfo);
            }
            else
            {
                cout << "there is no exam yet\n";
            }
            break;
        case enSelectionList::enstartQuizz:
            if (IsQuizExist)
            {
                startQuizz(QuizInfo);
                DidStudentTakeExam = true;
            }
            else
            {
                cout << "there is no exam yet\n";
            }

            break;
        case enSelectionList::displayAllstudent:
            if (IsQuizExist && DidStudentTakeExam)
            {
                displayMarksAllStudent(QuizInfo);
            }
            else
            {
                cout << "there is no exam yet\n";
            }
            break;
        case enSelectionList::quiryUsingID:
            if (IsQuizExist && DidStudentTakeExam)
            {
                string Id = enterIdStudent("Enter the student ID whose info you want to view : ");
                displayInfoStudentUsingID(QuizInfo, Id);
            }
            else
            {
                cout << "there is no exam yet\nor\nNo students have taken exams yet.\n";
            }

            break;
        case enSelectionList::DeletStudentUsingID:

            if (IsQuizExist && DidStudentTakeExam)
            {
                string Id = enterIdStudent("Enter the student ID you want to delete  : ");
                if (AskIfSureDeleteStudent(QuizInfo, Id))
                {
                    deleteStudentUsingID(QuizInfo, Id);
                }
            }
            else
            {
                cout << "There are no students yet.\n";
            }
            break;
        case enSelectionList::Exit:

            return;

            break;
        default:

            QuizInfo = ChoiseInfoQuiz();
            IsQuizExist = true;
            break;
        }

        cout << "do you want to return to proivse options [y/n] ";
        cin >> backOprions;

    } while (backOprions == 'y' || backOprions == 'Y');
}

int main()
{

    srand((unsigned)(time(NULL)));

    Game();
}
