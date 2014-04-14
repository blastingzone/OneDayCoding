#include <vector>
#include <map>
/**
* Definition for a point.
* struct Point {
*     int x;
*     int y;
*     Point() : x(0), y(0) {}
*     Point(int a, int b) : x(a), y(b) {}
* };
*/

using namespace std;

struct Point {
	int x;
	int y;
	Point() : x( 0 ), y( 0 ) {}
	Point( int a, int b ) : x( a ), y( b ) {}
};

struct Line {
	// 각도와 절편을 저장하는 선 구조체
	float angle;
	float yInterCept;
	vector<Point> points;
	Line( float angle, float yInterCept ) : angle( angle ), yInterCept( yInterCept ) {}
};

vector<Line> g_Lines;

class Solution {

public:
	// 각도 계산
	float getAngle( Point A, Point B )
	{
		return ( B.y - A.y ) / (float)( B.x - A.x );
	}

	// 절편 계산
	float getYInterCept( Point A, Point B )
	{
		float angle = getAngle( A, B );
		float yInterCept = ( A.y - angle * A.x );

		return yInterCept;
	}

	// 중복 없이 두 점을 한 선에 집어넣는다
	void InsertPointWithoutDuplication( const Point& A, const Point& B, vector<Line>::iterator& iter )
	{
		//만약 iterator가 존재하지 않는다면 (==g_Lines.end()) 새로 라인부터 넣어줘야함
		if ( iter == g_Lines.end() )
		{
			Line* newLine = new Line( getAngle( A, B ), getYInterCept( A, B ) );
			newLine->points.push_back( A );
			newLine->points.push_back( B );
			g_Lines.push_back( *newLine );
		}
		else
		{
			if ( !IsExistAlready( A, iter ) )
				( iter->points ).push_back( A );
			if ( !IsExistAlready( B, iter ) )
				( iter->points ).push_back( B );
		}
	}

	//이미 어떤 점이 추가해야할 라인에 존재하는지 찾는 함수
	bool IsExistAlready( const Point& A, const vector<Line>::iterator& iter )
	{
		// 해당 선이 갖고 있는 점들을 돌면서
		for ( auto point = ( iter->points ).begin(); point != ( iter->points ).end(); ++point )
		{
			// x, y 값이 모두 같으면 같은 점이겠지 당연하지?
			if ( point->x == A.x && point->y == A.y )
			{
				// 이미 존재함
				return true;
			}
			else
			{
				
			}
		}
		// 없는 점입니다
		return false;
	}

	// 각도와 절편이 같은 선(그러니까 걍 같은 선)을 찾아주는 함수
	vector<Line>::iterator findLine( float Angle, float YInterCept )
	{
		for ( auto iter = g_Lines.begin(); iter != g_Lines.end(); ++iter )
		{
			if ( iter->angle == Angle && iter->yInterCept == YInterCept )
				return iter;
		}
		// 404 line not found
		return g_Lines.end();
	}

	vector<Line>::iterator findLine( const Point& A, const Point& B )
	{
		return findLine( getAngle( A, B ), getYInterCept( A, B ) );
	}

	// 두 점이 같은 X라인에 있는가?
	const bool IsOnSameXLine( const Point& A, const Point& B )
	{
		if ( A.x == B.x )
			return true;
		else
			return false;
	}

	// 두 점이 같은 Y라인에 있는가?
	const bool IsOnSameYLine( const Point& A, const Point& B )
	{
		if ( A.y == B.y )
			return true;
		else
			return false;
	}

	// 수직선 중에 가장 많은 점을 가진 녀석
	const int FindMaxPointNumberOfVertical( const vector<Point> &points )
	{
		map<int, int> xcoordPoints;
		auto iter = points.begin();
		++iter;
		for ( ; iter != points.end(); ++iter )
		{
			auto pilot = xcoordPoints.find( iter->x );
			// 찾는 점의 X좌표가 없으면 첫 점이다
			if ( pilot == xcoordPoints.end() )
			{
				xcoordPoints.insert( map<int, int>::value_type( iter->x, 1 ) );
			}
			// 찾는 점의 X좌표가 있으면 기존의 값에 1 추가해준다
			else
			{
				pilot->second++;
			}
		}

		//마지막으로 다 돌면서 제일 큰 value 값을 찾는다
		int biggest = 0;
		for ( auto iter = xcoordPoints.begin(); iter != xcoordPoints.end(); ++iter )
		{
			biggest = ( biggest < iter->second ? iter->second : biggest );
		}

		return biggest;
	}

	// 수평선 중에 가장 많은 점을 가진 녀석
	const int FindMaxPointNumberOfHorizon( const vector<Point> &points )
	{
		map<int, int> ycoordPoints;
		auto iter = points.begin();
		++iter;
		for ( ; iter != points.end(); ++iter )
		{
			auto pilot = ycoordPoints.find( iter->y );
			// 찾는 점의 X좌표가 없으면 첫 점이다
			if ( pilot == ycoordPoints.end() )
			{
				ycoordPoints.insert( map<int, int>::value_type( iter->y, 1 ) );
			}
			// 찾는 점의 X좌표가 있으면 기존의 값에 1 추가해준다
			else
			{
				pilot->second++;
			}
		}

		//마지막으로 다 돌면서 제일 큰 value 값을 찾는다
		int biggest = 0;
		for ( auto iter = ycoordPoints.begin(); iter != ycoordPoints.end(); ++iter )
		{
			biggest = ( biggest < iter->second ? iter->second : biggest );
		}

		return biggest;
	}

	// 마지막으로 가장 많은 점을 가진 Line의 점 숫자
	const int FIndMaxPointNumberOfAllLines()
	{
		unsigned int biggest = 0;
		auto iter = g_Lines.begin();
		for ( ; iter != g_Lines.end(); ++iter )
		{
			biggest = ( biggest < ( iter->points ).size() ? ( iter->points ).size() : biggest );
		}

		return biggest;
	}


public:
	int maxPoints( vector<Point> &points ) {
		// 1. 점이 3개보다 작으면 무조건 점 개수(0, 1, 2)이다.
		if ( points.size() < 3 )
		{
			return points.size();
		}

		// 2. 우선 가로 세로 선 위에 있는 점들을 골라낸다.
		// 이 점들의 숫자가 임시 MAX 숫자가 된다. 이후부터는 X나 Y좌표가 같은 점들을 신경쓰지 않아도 된다.
		int result = ( FindMaxPointNumberOfHorizon( points ) < FindMaxPointNumberOfVertical( points ) ?
			FindMaxPointNumberOfVertical( points ) : FindMaxPointNumberOfHorizon( points ) );

		// 3. 모든 점들을 순회하면서 두 점을 고른다.
		// 두 점이 이루는 직선이 나오면 두 점을 해당 직선에 할당한다.
		// 이때 그 직선에는 중복 점이 존재하지 않는다.
		for ( auto iter = points.begin(); iter != points.end(); ++iter )
		{
			auto pivot = iter;
			// 한 칸 증가하고 생각한다
			for ( ++pivot; pivot != points.end(); ++pivot )
			{
				// 두 점이 같은 수직, 수평선 위에 있지 않을 때
				if ( !IsOnSameXLine( *iter, *pivot ) && !IsOnSameYLine( *iter, *pivot ) )
				{
					InsertPointWithoutDuplication( *iter, *pivot, findLine( *iter, *pivot ) );
				}
			}
		}
		// 수직 / 수평선에 있는 점들과 다른 선분 위에 있는 점들을 모두 세서 가장 점이 많은 직선상의 점 갯수를 반환
		result = ( FIndMaxPointNumberOfAllLines() < result ? result : FIndMaxPointNumberOfAllLines() );
		return result;
	}
};

int main()
{
	vector<Point> testSet;
	testSet.push_back( Point( 1, 2 ) );
	testSet.push_back( Point( 2, 4 ) );
	testSet.push_back( Point( 10, 25 ) );
	testSet.push_back( Point( 3, 6 ) );
	testSet.push_back( Point( 3, 5 ) );
	testSet.push_back( Point( 3, 10 ) );
	testSet.push_back( Point( 3, 11 ) );

	Solution solution;

	printf(" Result : %d", solution.maxPoints( testSet ));

	getchar();
}