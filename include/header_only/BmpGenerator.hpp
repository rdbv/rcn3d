#ifndef RCN3D_BMPGENERATOR_HPP
#define RCN3D_BMPGENERATOR_HPP

#include <cstdlib>
#include <cstdio>

namespace rcn3d {

struct Canvas
{
	double ** red;
	double ** green;
	double ** blue;
	unsigned int w;
	unsigned int h;

	void make(unsigned int initw, unsigned int inith)
	{
		w = initw;
		h = inith;
		red = new double*[w];
		green = new double*[w];
		blue = new double*[w];
		for (unsigned int i = 0; i < w; i++)
		{
			red[i] = new double[h];
			green[i] = new double[h];
			blue[i] = new double[h];
		}
	}
	void destroy()
	{
		for (unsigned int i = 0; i < w; i++)
		{
			delete[] red[i];
			delete[] green[i];
			delete[] blue[i];
		}
		delete[] red;
		delete[] green;
		delete[] blue;
	}

	void setColor(int x, int y, int r, int g, int b){
		if(x<0 || y<0 || x>=w || y >=h)return;
		red[x][y] = (double)r/255.0;
		green[x][y] = (double)g/255.0;
		blue[x][y] = (double)b/255.0;
	}

	void save(const char* file)
	{
		FILE *f;
		unsigned char *img = NULL;
		int filesize = 54 + 3*w*h;
		img = new unsigned char [3*w*h];
		int r, g, b, x, y;

		for(unsigned int i=0; i<w; i++)
		{
			for(unsigned int j=0; j<h; j++)
			{
				x=i; y=(h-1)-j;
				r = (int)(red  [i][j]*255);
				g = (int)(green[i][j]*255);
				b = (int)(blue [i][j]*255);
				if (r > 255) r=255;
				if (r <   0) r=  0;
				if (g > 255) g=255;
				if (g <   0) g=  0;
				if (b > 255) b=255;
				if (b <   0) b=  0;
				img[(x+y*w)*3+2] = (unsigned char)(r);
				img[(x+y*w)*3+1] = (unsigned char)(g);
				img[(x+y*w)*3+0] = (unsigned char)(b);
			}
		}

		unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
		unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
		unsigned char bmppad[3] = {0,0,0};

		bmpfileheader[ 2] = (unsigned char)(filesize    );
		bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
		bmpfileheader[ 4] = (unsigned char)(filesize>>16);
		bmpfileheader[ 5] = (unsigned char)(filesize>>24);

		bmpinfoheader[ 4] = (unsigned char)(       w    );
		bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
		bmpinfoheader[ 6] = (unsigned char)(       w>>16);
		bmpinfoheader[ 7] = (unsigned char)(       w>>24);
		bmpinfoheader[ 8] = (unsigned char)(       h    );
		bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
		bmpinfoheader[10] = (unsigned char)(       h>>16);
		bmpinfoheader[11] = (unsigned char)(       h>>24);

		f = fopen(file,"wb");
		fwrite(bmpfileheader,1,14,f);
		fwrite(bmpinfoheader,1,40,f);
		for(unsigned int i=0; i<h; i++)
		{
			fwrite(img+(w*(h-i-1)*3),3,w,f);
			fwrite(bmppad,1,(4-(w*3)%4)%4,f);
		}
		delete[] img;
		fclose(f);
	}
};

}


#endif //RCN3D_BMPGENERATOR_HPP
