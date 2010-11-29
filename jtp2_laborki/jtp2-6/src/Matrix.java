class Matrix
{
	Matrix() {
		System.out.println("hello matrix!");
		int[][] m1 = new int[2][2];
		m1[0][0] = 1; m1[0][1] = 2;
		m1[1][0] = 3; m1[1][1] = 4;
		printM(m1);
		
		int[][] m2 = new int[2][1];
		m2[0][0] = 5;
		m2[1][0] = 6;
		printM(m2);
		
		printM(multiply(m1,m2));
		
		int[][] m = upperMatrix();
		printM(m);
		firstZero(m);
	}
	
	public static void main(String args[]) {
		new Matrix();
	}
	
	int[][] multiply(int[][] m1, int[][] m2) {
		int w = m1[0].length;
		for(int[] e : m1) assert e.length==w;
		assert m2.length==w;
		for(int[] e : m2) assert e.length==m2[0].length;
		
		int[][] m = new int[m1.length][m2[0].length];
		for(int i=0; i<m1.length; ++i)
			for(int j=0; j<m2[0].length; ++j) {
				m[i][j]=0;
				for(int k=0; k<m1[0].length; ++k)
					m[i][j] += m1[i][k] * m2[k][j];
			}
		return m;
	}
	
	void firstZero(int[][] m) {
		int x,y=-1;
		up:
		for(x=0; x<m.length; ++x)
			for(y=0; y<m[x].length; ++y)
				if(m[x][y] == 0) break up;
		if(x != m.length)
			System.out.println(x + " " + y);
	}
	
	int[][] upperMatrix() {
		int n = (int)(Math.random() * 5) + 1;
		int[][] m = new int[n][];
		
		for(int i=0; i<m.length; ++i) {
			m[i] = new int[i+1];
			for(int j=0; j<m[i].length; ++j)
				m[i][j] = (int)(Math.random() * 10);
		}
		return m;
	}
	
	void printM(int[][] m) {
		for(int[] t : m) {
			for(int e : t)
				System.out.print(e + " ");
			System.out.println("");
		}
		System.out.println("");
	}
	
	
	
	
	
	
}
