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
	// ������ ������ �����ϴ� �� ����ü
	float angle;
	float yInterCept;
	vector<Point> points;
	Line( float angle, float yInterCept ) : angle( angle ), yInterCept( yInterCept ) {}
};

vector<Line> g_Lines;

class Solution {

public:
	// ���� ���
	float getAngle( Point A, Point B )
	{
		return ( B.y - A.y ) / (float)( B.x - A.x );
	}

	// ���� ���
	float getYInterCept( Point A, Point B )
	{
		float angle = getAngle( A, B );
		float yInterCept = ( A.y - angle * A.x );

		return yInterCept;
	}

	// �ߺ� ���� �� ���� �� ���� ����ִ´�
	void InsertPointWithoutDuplication( const Point& A, const Point& B, vector<Line>::iterator& iter )
	{
		//���� iterator�� �������� �ʴ´ٸ� (==g_Lines.end()) ���� ���κ��� �־������
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

	//�̹� � ���� �߰��ؾ��� ���ο� �����ϴ��� ã�� �Լ�
	bool IsExistAlready( const Point& A, const vector<Line>::iterator& iter )
	{
		// �ش� ���� ���� �ִ� ������ ���鼭
		for ( auto point = ( iter->points ).begin(); point != ( iter->points ).end(); ++point )
		{
			// x, y ���� ��� ������ ���� ���̰��� �翬����?
			if ( point->x == A.x && point->y == A.y )
			{
				// �̹� ������
				return true;
			}
			else
			{
				
			}
		}
		// ���� ���Դϴ�
		return false;
	}

	// ������ ������ ���� ��(�׷��ϱ� �� ���� ��)�� ã���ִ� �Լ�
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

	// �� ���� ���� X���ο� �ִ°�?
	const bool IsOnSameXLine( const Point& A, const Point& B )
	{
		if ( A.x == B.x )
			return true;
		else
			return false;
	}

	// �� ���� ���� Y���ο� �ִ°�?
	const bool IsOnSameYLine( const Point& A, const Point& B )
	{
		if ( A.y == B.y )
			return true;
		else
			return false;
	}

	// ������ �߿� ���� ���� ���� ���� �༮
	const int FindMaxPointNumberOfVertical( const vector<Point> &points )
	{
		map<int, int> xcoordPoints;
		auto iter = points.begin();
		++iter;
		for ( ; iter != points.end(); ++iter )
		{
			auto pilot = xcoordPoints.find( iter->x );
			// ã�� ���� X��ǥ�� ������ ù ���̴�
			if ( pilot == xcoordPoints.end() )
			{
				xcoordPoints.insert( map<int, int>::value_type( iter->x, 1 ) );
			}
			// ã�� ���� X��ǥ�� ������ ������ ���� 1 �߰����ش�
			else
			{
				pilot->second++;
			}
		}

		//���������� �� ���鼭 ���� ū value ���� ã�´�
		int biggest = 0;
		for ( auto iter = xcoordPoints.begin(); iter != xcoordPoints.end(); ++iter )
		{
			biggest = ( biggest < iter->second ? iter->second : biggest );
		}

		return biggest;
	}

	// ���� �߿� ���� ���� ���� ���� �༮
	const int FindMaxPointNumberOfHorizon( const vector<Point> &points )
	{
		map<int, int> ycoordPoints;
		auto iter = points.begin();
		++iter;
		for ( ; iter != points.end(); ++iter )
		{
			auto pilot = ycoordPoints.find( iter->y );
			// ã�� ���� X��ǥ�� ������ ù ���̴�
			if ( pilot == ycoordPoints.end() )
			{
				ycoordPoints.insert( map<int, int>::value_type( iter->y, 1 ) );
			}
			// ã�� ���� X��ǥ�� ������ ������ ���� 1 �߰����ش�
			else
			{
				pilot->second++;
			}
		}

		//���������� �� ���鼭 ���� ū value ���� ã�´�
		int biggest = 0;
		for ( auto iter = ycoordPoints.begin(); iter != ycoordPoints.end(); ++iter )
		{
			biggest = ( biggest < iter->second ? iter->second : biggest );
		}

		return biggest;
	}

	// ���������� ���� ���� ���� ���� Line�� �� ����
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
		// 1. ���� 3������ ������ ������ �� ����(0, 1, 2)�̴�.
		if ( points.size() < 3 )
		{
			return points.size();
		}

		// 2. �켱 ���� ���� �� ���� �ִ� ������ ��󳽴�.
		// �� ������ ���ڰ� �ӽ� MAX ���ڰ� �ȴ�. ���ĺ��ʹ� X�� Y��ǥ�� ���� ������ �Ű澲�� �ʾƵ� �ȴ�.
		int result = ( FindMaxPointNumberOfHorizon( points ) < FindMaxPointNumberOfVertical( points ) ?
			FindMaxPointNumberOfVertical( points ) : FindMaxPointNumberOfHorizon( points ) );

		// 3. ��� ������ ��ȸ�ϸ鼭 �� ���� ����.
		// �� ���� �̷�� ������ ������ �� ���� �ش� ������ �Ҵ��Ѵ�.
		// �̶� �� �������� �ߺ� ���� �������� �ʴ´�.
		for ( auto iter = points.begin(); iter != points.end(); ++iter )
		{
			auto pivot = iter;
			// �� ĭ �����ϰ� �����Ѵ�
			for ( ++pivot; pivot != points.end(); ++pivot )
			{
				// �� ���� ���� ����, ���� ���� ���� ���� ��
				if ( !IsOnSameXLine( *iter, *pivot ) && !IsOnSameYLine( *iter, *pivot ) )
				{
					InsertPointWithoutDuplication( *iter, *pivot, findLine( *iter, *pivot ) );
				}
			}
		}
		// ���� / ���򼱿� �ִ� ����� �ٸ� ���� ���� �ִ� ������ ��� ���� ���� ���� ���� �������� �� ������ ��ȯ
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