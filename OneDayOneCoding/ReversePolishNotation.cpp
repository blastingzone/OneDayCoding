#include <vector>
#include <string>

/*

Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are + , -, *, / .Each operand may be an integer or another expression.

Some examples :
["2", "1", "+", "3", "*"] -> ( ( 2 + 1 ) * 3 ) -> 9
["4", "13", "5", "/", "+"] -> ( 4 + ( 13 / 5 ) ) -> 6

*/


using namespace std;

class Solution {
public:
	int evalRPN(vector<string> &tokens) {
		vector<int> tempStack;

		vector<string>::iterator pilot = tokens.begin();

		for (; pilot != tokens.end(); ++pilot)
		{
			if (IsOperator(pilot))
			{
				const char op = *pilot->c_str();

				int second = tempStack.back();
				tempStack.pop_back();

				int first = tempStack.back();
				tempStack.pop_back();

				tempStack.push_back(calculate(op, first, second));
			}
			else
			{
				tempStack.push_back(atoi(pilot->c_str()));
			}
		}

		return tempStack.front();
	}
private:
	// warning : only works input == integer || character
	bool IsOperator(const vector<string>::iterator& input)
	{
		// Exception : input == "0"
		if (!strcmp(input->c_str(), "0"))
		{
			return false;
		}

		return (atoi(input->c_str()) == 0 ? true : false);
	}

	int calculate(char op, int first, int second)
	{
		int result = -1;
		swtich(op)
		{
			case '+':
				result = first + second;
				break;
			case '-':
				result = first - second;
				break;
			case '*':
				result = first * second;
				break;
			case '/':
				result = first / second;
				break;			
		}
		return result;
	}
};


int main()
{
	Solution sol;
	int result = 0;

	vector<string> tempSet;
	tempSet.push_back("2");
	tempSet.push_back("1");
	tempSet.push_back("+");
	tempSet.push_back("3");
	tempSet.push_back("*");

	result = sol.evalRPN(tempSet);
	printf("2 1 + 3 * = %d\n", result);

	tempSet.clear();

	tempSet.push_back("4");
	tempSet.push_back("13");
	tempSet.push_back("5");
	tempSet.push_back("/");
	tempSet.push_back("+");

	result = sol.evalRPN(tempSet);
	printf("4 13 5 / + = %d\n", result);

	tempSet.clear();

	tempSet.push_back("0");
	tempSet.push_back("3");
	tempSet.push_back("/");

	result = sol.evalRPN(tempSet);
	printf("0 3 / + = %d\n", result);


	getchar();
}
