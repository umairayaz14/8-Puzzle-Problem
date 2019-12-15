#include <iostream>
#include <Bits.h>
using namespace::std;

class puzzle
{
	struct node
	{
		node* p;
		int m[3][3];
		int x;
		int y;
		//int status;

	};

	struct queue
	{
		node* n;
		queue* next;
	};

public:

	node* temp;
	queue* head;
	queue* tail;
	node* root;

	puzzle()
	{
		head = NULL;
		tail = NULL;
		root = NULL;
	}

	int blanklocx(int m[3][3])
	{

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				if (m[x][y] == 0)
				{
					return x;
					break;
				}
			}
		}

	}

	int blanklocy(int m[3][3])
	{
		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				if (m[x][y] == 0)
				{
					return y;
					break;
				}
			}
		}
	}

	node* newnode(int m[3][3], int x1, int y1, int nx, int ny, node* parent)
	{
		node* ptr = new node;
		ptr->p = parent;
		ptr->x = x1;
		ptr->y = y1;

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				//	ptr->m[x][y] = m[x][y];
			/*	if (x == nx && y == ny)
				{
					ptr->x = nx;
					ptr->y = ny;
					ptr->m[x1][y1] = m[x][y];
					ptr->m[ptr->x][ptr->y] = 0;

				}     */
			//	else
					ptr->m[x][y] = m[x][y];
			}
		}
			        ptr->x = nx;
					ptr->y = ny;
					ptr->m[x1][y1] = m[nx][ny];
					ptr->m[ptr->x][ptr->y] = 0;


		return ptr;
	}

	node* insertroot(int init[3][3], int x, int y, int x1, int y1, node* ptr)
	{
		 newnode(init, x, y, x1, y1, ptr);
	}

	void print(int m[3][3])
	{

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				cout << m[x][y] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

	void printp(node* par)
	{
		if (par == NULL)
		{
			return;
		}
		else
		{
		
		printp(par->p);
		print(par->m);
        }

	}

	void addqueue(node* ptr)
	{
		
		if (head == NULL)
		{
			queue* pt = new queue;
			pt->n = ptr;
			pt->next = NULL;
			head = pt;
			tail = pt;
			return;
		}
        else
        {
		queue* pt = new queue;
		pt->n = ptr;
		pt->next=NULL;
		tail->next = pt;
		tail = pt;
	    }
	}

	node* deletequeue()
	{
		queue* node1 = head;
		node* ptr2 = node1->n;
		head = head->next;
	//	delete node1;
		return ptr2;
	//	print(ptr2->m);
	}

	/*node* neighbours(node* ptr)
	{
		node* temp = ptr;

		if (temp->p == NULL)
		{
			return temp;

		}
		neighbours(temp->p);
	}*/

	bool goal(int init[3][3], int final[3][3])
	{
		int d = 0;
		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				if (init[x][y] != final[x][y])
				{
					d = 1;
				}
			}
		}
		if (d == 0)
			return 1;
		else
			return 0;
	}

	void copyarr(int arr1[3][3], int arr2[3][3])
	{
		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				arr1[x][y] = arr2[x][y];
			}
		}
	}

	void BFS(int init[3][3], int x, int y, int fin[3][3])
	{
		bool t;
		root = insertroot(init, x, y, x, y, NULL);
		addqueue(root);
		node* ptr = NULL;
		//node* u = new node;
		//node* v = new node;

		while (1)
		{
			ptr = deletequeue();
			int arrr[3][3], arrl[3][3], arru[3][3], arrd[3][3];
			copyarr(arrr, ptr->m);
			copyarr(arrl, ptr->m);
			copyarr(arru, ptr->m);
			copyarr(arrd, ptr->m);
			print(ptr->m);
		//	printp(ptr->p);
			t = goal(ptr->m, fin);
			if (t)
			{
				cout<<"Final: "<<endl;
				print(ptr->m);
				break;
			}
			
			//	x= blanklocx(ptr->m);
			//	y = blanklocy(ptr->m);
			else
			{
				x= blanklocx(ptr->m);
				y = blanklocy(ptr->m);		
			if ((y+1 == 2 || y+1 == 1) && x==x)
			{
			node* tempr;
			tempr = newnode(arrr,x,y,x,y+1,ptr);
			addqueue(tempr);
			cout<<"R: "<<endl;
			print(tempr->m);
		    }
	        if ((y-1 == 0 || y-1 == 1)&& x==x)
	        {
			node* templ;
			templ = newnode(arrl, x, y, x, y-1, ptr);
			addqueue(templ);
			cout<<"L: "<<endl;
			print(templ->m);
	     	}
            if((x-1 == 0 || x-1 ==1)&& y==y )
            {
			
			node* tempu;
			tempu = newnode(arru, x, y, x-1 , y , ptr);
			addqueue(tempu);
			cout<<"U: "<<endl;
			print(tempu->m);
            }
            if((x+1 == 1 || x+1 == 2)&& y==y)
			{
			node* tempd;
			tempd = newnode(arrd, x, y, x+1, y, ptr);
			addqueue(tempd);
			cout<<"D: "<<endl;
			print(tempd->m);
		    }
		}
		}

		/*while (head != NULL || t==false)
		{
			u = deletequeue();
			while (v = neighbours(u))
			{
				if (v->status == 1)
				{
					v->status = 2;
					v->p = u;
					addqueue(v);
				}

			}
		}
		u->status = 3;*/
	}
};

int main()
{
	class puzzle p;
	int init[3][3];
	
			for (int x = 0; x < 3; x++)
		{

			for (int y = 0; y < 3; y++)
			{
				cout << "Enter value of row " << x + 1 << ": ";
				int n;
				cin >> n;
				init[x][y] = n;
			}

		}
	cout << endl;
	cout<<"Root: "<<endl;
	p.print(init);
	//p.temp;
	int final[3][3] =
	{
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8}
	};

	int x = p.blanklocx(init);
	int y = p.blanklocy(init);

	cout << "Blank x: " << x << " " << "Blan y: " << y << endl << endl;

	//p.insertroot(init, x, y, x, y, NULL);
	//p.temp = p.newnode(init, x, y, 1, 2, p.root);
	//p.printp(p.temp);
	
	p.BFS(init, x, y, final);
	return 0;
}
