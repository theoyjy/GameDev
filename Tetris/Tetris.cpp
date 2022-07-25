#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int M = 20;
const int N = 10;

int field[M][N] = { 0 };

// numbers map to locations:
// i = row(y) *2 + col(x)
/*	
	| 0 | 1 |
	| 2 | 3 |
	| 4 | 5 |
	| 6 | 7 |
*/

// shapes of tiles map to numbers
int figures[7][4] =
{
	1, 3, 5, 7,
	2, 4, 5, 7,
	3, 5, 4, 6,
	3, 5, 4, 7,
	2, 3, 5, 7,
	3, 5, 7, 6,
	2, 3, 4, 5,
};

struct point {
	int x;
	int y;
}a[4], b[4];

int main()
{
	RenderWindow window(VideoMode(320, 480), "The Game");

	Texture t;
	t.loadFromFile("./Resources/TetrisTiles.png");
	Sprite s(t);
	s.setTextureRect(IntRect(0, 0, 18, 18)); //ÇÐ¸î²ÄÖÊ

	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}
		}

		int n = 5;
		for (int i = 0; i < 4; ++i)
		{
			a[i].x = figures[n][i] % 2; // 0 or 1
			a[i].y = figures[n][i] / 2; // 0, 1, 2, 3
		}

		window.clear(Color::White);

		for (int i = 0; i < 4; ++i)
		{
			s.setPosition(a[i].x * 18, a[i].y * 18);
			window.draw(s);
		}

		window.display();
	}
	return 0;
}