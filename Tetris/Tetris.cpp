#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int M = 20;
const int N = 10;

int field[M][N] = { 0 }; // the playground

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

struct Point {
	int x;
	int y;
}a[4], b[4];

bool check()
{
	for (int i(0); i < 4; ++i)
	{
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M)
			return false;
		else if (field[a[i].y][a[i].x]) // �Ѿ��и���ռ�ݳ���
			return false;
	}
	return true;
}

int main()
{
	srand(time(0));

	RenderWindow window(VideoMode(320, 480), "The Game");

	Texture t;
	t.loadFromFile("./Resources/Tiles.png");
	Sprite s(t);
	s.setTextureRect(IntRect(0, 0, 18, 18)); //�и����

	int moveDirection = 0;
	bool rotate = false;
	int colorNum = 1;

	float timer = 0;
	float delay = 0.3;
	Clock clock;
	
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}

			if (e.type == Event::KeyPressed)
			{
				if (e.key.code == Keyboard::Up)
					rotate = true;
				else if (e.key.code == Keyboard::Left)
					moveDirection = -1;
				else if (e.key.code == Keyboard::Right)
					moveDirection = 1;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Down))delay = 0.05;
		/// <- Move -> /// 
		for (int i(0); i < 4; ++i)
			a[i].x += moveDirection;

		if (!check())
		{
			for (int i(0); i < 4; ++i)
				a[i] = b[i];
		}
		/// <- Clockwise Rotate -> /// 
		if (rotate)
		{
			Point p = a[1]; // center of rotation
			for (int i(0); i < 4; ++i)
			{
				// ���ԭtile����ת���ĵ���Ծ���
				int x = a[i].y - p.y; // x < 0 : �õ�����ת���ĵ��·���˳ʱ����ת������ת���ĵ��󷽣����֮��Ҫ����
				int y = a[i].x - p.x; // y < 0 : �õ�����ת���ĵ��ҷ���˳ʱ����ת������ת���ĵ��·������֮��Ҫ�ӣ�
				// ��Ծ����Ӧ�õ���һ������
				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}
			if (!check())
			{
				for (int i(0); i < 4; ++i)
					a[i] = b[i];
			}
		}

		/// <Tick> /// 
		if (timer > delay)
		{
			for (int i(0); i < 4; ++i)
			{
				b[i] = a[i];
				a[i].y += 1;
			}
			if (!check())
			{
				for (int i(0); i < 4; ++i) // a ���磬������һ��tick��λ��b�����Ƶ�������
					field[b[i].y][b[i].x] = colorNum;

				// ������һ�������ɫ �����״��tile
				colorNum = 1 + rand() % 7;	
				int n = rand() % 7;
				for (int i = 0; i < 4; ++i)
				{
					a[i].x = figures[n][i] % 2; // 0 or 1
					a[i].y = figures[n][i] / 2; // 0, 1, 2, 3
				}
			}

			timer = 0;
		}

		moveDirection = 0;
		rotate = false;
		delay = 0.3;

		/// draw ///
		window.clear(Color::White);
		for (int i(0); i < M; ++i)	// ���Ƴ������Ѿ����õ�
		{		
			for (int j(0); j < N; ++j)
			{
				if (field[i][j] == 0) continue;
				s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
				s.setPosition(j * 18, i * 18);
				window.draw(s);
			}
		}

		for (int i = 0; i < 4; i++) // ���������ƶ���
		{
			s.setTextureRect(IntRect(colorNum* 18, 0, 18, 18));
			s.setPosition(a[i].x * 18, a[i].y * 18);
			//s.move(28, 31);
			window.draw(s);

		}
		window.display();
	}
	return 0;
}