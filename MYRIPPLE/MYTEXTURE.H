// MyTexture.h: interface for the CMyTexture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYTEXTURE_H__6EFF87BC_E0EE_4915_9D69_ABC674379FA4__INCLUDED_)
#define AFX_MYTEXTURE_H__6EFF87BC_E0EE_4915_9D69_ABC674379FA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct _ImageRec 
{
    unsigned short imagic;
    unsigned short type;
    unsigned short dim;
    unsigned short xsize, ysize, zsize;
    unsigned int min, max;
    unsigned int wasteBytes;
    char name[80];
    unsigned long colorMap;
    FILE *file;
    unsigned char *tmp, *tmpR, *tmpG, *tmpB;
    unsigned long rleEnd;
    unsigned int *rowStart;
    int *rowSize;
} ImageRec;

class CMyTexture  
{
public:
	CMyTexture();
	virtual ~CMyTexture();
	void bwtorgba(unsigned char *b,unsigned char *l,int n);
	void latorgba(unsigned char *b, unsigned char *a,unsigned char *l,int n);
	void rgbtorgba(unsigned char *r,unsigned char *g,unsigned char *b,unsigned char *l,int n); 
	void rgbatorgba(unsigned char *r,unsigned char *g,unsigned char *b,unsigned char *a,unsigned char *l,int n); 
	void ConvertShort(unsigned short *array, long length); 
	void ConvertLong(unsigned *array, long length); 
	ImageRec * ImageOpen(const char *fileName);
	void ImageClose(ImageRec *image); 
	void ImageGetRow(ImageRec *image, unsigned char *buf, int y, int z); 
	unsigned * read_texture(char *name, int *width, int *height, int *components); 

};

#endif // !defined(AFX_MYTEXTURE_H__6EFF87BC_E0EE_4915_9D69_ABC674379FA4__INCLUDED_)
