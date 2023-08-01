//ImageFilter

#include <iostream>
#include <cstdio>
#include <fstream>

#define x1 750
#define y1 500




int main(){

	FILE* inp;
	FILE* outp;
	unsigned char img1[y1][x1], img2[y1][x1], img3[y1][x1] , output[y1][x1] , TX[3][3] , TY[3][3] , FX[5][5] , FY[5][5];
	
	int value = 0;
	int sum = 0;
	
	//3x3 horizontal
	TX[0][0] = -1; TX[0][1] = 0; TX[0][2] = 1; 
	TX[1][0] = -2; TX[1][1] = 0; TX[1][2] = 2;  
	TX[2][0] = -1; TX[2][1] = 0; TX[2][2] = 1;

	//3x3 vertical
	TY[0][0] = -1; TY[0][1] = -2; TY[0][2] = -1;    
	TY[1][0] =  0; TY[1][1] =  0; TY[1][2] =  0;    
	TY[2][0] =  1; TY[2][1] =  2; TY[2][2] =  1;
	
	//5x5 horizontal -- std::cout << value << "====";
	FX[0][0] = -1; FX[0][1] = -2; FX[0][2] = 0; FX[0][3] = 2; FX[0][4] = 1; 
	FX[1][0] = -2; FX[1][1] = -4; FX[1][2] = 0; FX[1][3] = 4; FX[1][4] = 2; 
	FX[2][0] = -4; FX[2][1] = -8; FX[2][2] = 0; FX[2][3] = 8; FX[2][4] = 4; 
	FX[3][0] = -2; FX[3][1] = -4; FX[3][2] = 0; FX[3][3] = 4; FX[3][4] = 2;
	FX[4][0] = -1; FX[4][1] = -2; FX[4][2] = 0; FX[4][3] = 2; FX[4][4] = 1;

	//5x5 vertical
	FY[0][0] = -1; FY[0][1] = -2; FY[0][2] = -4; FY[0][3] = -2; FY[0][4] = -1; 
	FY[1][0] = -2; FY[1][1] = -4; FY[1][2] = -8; FY[1][3] = -4; FY[1][4] = -2; 
	FY[2][0] =  0; FY[2][1] =  0; FY[2][2] =  0; FY[2][3] =  0; FY[2][4] =  0; 
	FY[3][0] =  2; FY[3][1] =  4; FY[3][2] =  8; FY[3][3] =  4; FY[3][4] =  2;
	FY[4][0] =  1; FY[4][1] =  2; FY[4][2] =  4; FY[4][3] =  2; FY[4][4] =  1;
	
	
	//unesco---------------------------------------------------------------------------------------------------------------
	inp = fopen("unesco-1.raw" , "rb");
	fread(img1 , 1 , y1*x1 , inp);
	
	
	//3x3 h
	value = 0;
	for (int j=1 ; j<y1 ; j++){
		for (int i=1 ; i<x1 ; i++){
			
			
			value =   (img1[j - 1][i - 1] * TX[0][0]) + (img1[j - 1][i] * TX[0][1]) + (img1[j - 1][i + 1] * TX[0][2])
					+ (img1[j][i - 1] * TX[1][0])     + (img1[j][i] * TX[1][1])     + (img1[j][i + 1] * TX[1][2])
					+ (img1[j + 1][i - 1] * TX[2][0]) + (img1[j + 1][i] * TX[2][1]) + (img1[j + 1][i + 1] * TX[2][2]);
			
			
			sum = (img1[j - 1][i + 1] * TX[0][2]) + 
				  (img1[j][i + 1] * TX[1][2]) + 
				  (img1[j + 1][i + 1] * TX[2][2]);
				  
			if (sum == 0) sum = 1;
			
			value = 128 + (value/sum)/2;

			
			
			output[j][i] = value;
			
		}
	}
	
	outp = fopen("unescoThreeHorizontal.raw" , "wb");
	fwrite(output , 1 , y1*x1 , outp);
	fclose(outp);
	
	//3x3 v
	value = 0;
	for (int j=1 ; j<y1 ; j++){
		for (int i=1 ; i<x1 ; i++){
			
			
			value =   (img1[j - 1][i - 1] * TY[0][0]) + (img1[j - 1][i] * TY[0][1]) + (img1[j - 1][i + 1] * TY[0][2])
					+ (img1[j][i - 1] * TY[1][0])     + (img1[j][i] * TY[1][1])     + (img1[j][i + 1] * TY[1][2])
					+ (img1[j + 1][i - 1] * TY[2][0]) + (img1[j + 1][i] * TY[2][1]) + (img1[j + 1][i + 1] * TY[2][2]);
			
			sum = (img1[j + 1][i - 1] * TY[2][0]) + 
				  (img1[j + 1][i] * TY[2][1]) + 
				  (img1[j + 1][i + 1] * TY[2][2]);
				  
			if (sum == 0) sum = 1;
			
			value = 128 + (value/sum)/2;
			
			
			output[j][i] = value;
			
		}
	}
	
	outp = fopen("unescoThreeVertical.raw" , "wb");
	fwrite(output , 1 , y1*x1 , outp);
	fclose(outp);
	
	//5x5 h
	value = 0;
	for (int j=1 ; j<y1 ; j++){
		for (int i=1 ; i<x1 ; i++){
			
			
			value =   (img1[j - 2][i - 2] * FX[0][0]) + (img1[j - 2][i -1] * FX[0][1]) + (img1[j - 2][i] * FX[0][2]) + (img1[j - 2][i + 1] * FX[0][3]) + (img1[j - 2][i + 2] * FX[0][4])
					+ (img1[j - 1][i - 2] * FX[1][0]) + (img1[j - 1][i -1] * FX[1][1]) + (img1[j - 1][i] * FX[1][2]) + (img1[j - 1][i + 1] * FX[1][3]) + (img1[j - 1][i + 2] * FX[1][4])
					+ (img1[j][i - 2] * FX[2][0]) + (img1[j][i -1] * FX[2][1]) + (img1[j][i] * FX[2][2]) + (img1[j][i + 1] * FX[2][3]) + (img1[j][i + 2] * FX[2][4])
					+ (img1[j + 1][i - 2] * FX[3][0]) + (img1[j + 1][i -1] * FX[3][1]) + (img1[j + 1][i] * FX[3][2]) + (img1[j + 1][i + 1] * FX[3][3]) + (img1[j + 1][i + 2] * FX[3][4])
					+ (img1[j + 2][i - 2] * FX[4][0]) + (img1[j + 2][i -1] * FX[4][1]) + (img1[j + 2][i] * FX[4][2]) + (img1[j + 2][i + 1] * FX[4][3]) + (img1[j + 2][i + 2] * FX[4][4]);
			
			sum = (img1[j - 2][i + 1] * FX[0][3]) + (img1[j - 2][i + 2] * FX[0][4]) + 
				  (img1[j - 1][i + 1] * FX[1][3]) + (img1[j - 1][i + 2] * FX[1][4]) +
				  (img1[j][i + 1] * FX[2][3]) + (img1[j][i + 2] * FX[2][4]) +
				  (img1[j + 1][i + 1] * FX[3][3]) + (img1[j + 1][i + 2] * FX[3][4]) +
				  (img1[j + 2][i + 1] * FX[4][3]) + (img1[j + 2][i + 2] * FX[4][4]);
			
			if (sum == 0) sum = 1;
			
			value = 128 + (value/sum)/2;
			
	
			output[j][i] = value;
			
		}
	}
	
	outp = fopen("unescoFiveHorizontal.raw" , "wb");
	fwrite(output , 1 , y1*x1 , outp);
	fclose(outp);
	
	//5x5 v
	value = 0;
	for (int j=1 ; j<y1 ; j++){
		for (int i=1 ; i<x1 ; i++){
			
			
			value =   (img1[j - 2][i - 2] * FY[0][0]) + (img1[j - 2][i -1] * FY[0][1]) + (img1[j - 2][i] * FY[0][2]) + (img1[j - 2][i + 1] * FY[0][3]) + (img1[j - 2][i + 2] * FY[0][4])
					+ (img1[j - 1][i - 2] * FY[1][0]) + (img1[j - 1][i -1] * FY[1][1]) + (img1[j - 1][i] * FY[1][2]) + (img1[j - 1][i + 1] * FY[1][3]) + (img1[j - 1][i + 2] * FY[1][4])
					+ (img1[j][i - 2] * FY[2][0]) + (img1[j][i -1] * FY[2][1]) + (img1[j][i] * FY[2][2]) + (img1[j][i + 1] * FY[2][3]) + (img1[j][i + 2] * FY[2][4])
					+ (img1[j + 1][i - 2] * FY[3][0]) + (img1[j + 1][i -1] * FY[3][1]) + (img1[j + 1][i] * FY[3][2]) + (img1[j + 1][i + 1] * FY[3][3]) + (img1[j + 1][i + 2] * FY[3][4])
					+ (img1[j + 2][i - 2] * FY[4][0]) + (img1[j + 2][i -1] * FY[4][1]) + (img1[j + 2][i] * FY[4][2]) + (img1[j + 2][i + 1] * FY[4][3]) + (img1[j + 2][i + 2] * FY[4][4]);
			
			sum = (img1[j + 1][i - 2] * FY[3][0]) + (img1[j + 1][i -1] * FY[3][1]) + 
				  (img1[j + 1][i] * FY[3][2]) + (img1[j + 1][i + 1] * FY[3][3]) + 
				  (img1[j + 1][i + 2] * FY[3][4]) + (img1[j + 2][i - 2] * FY[4][0]) + 
				  (img1[j + 2][i -1] * FY[4][1]) + (img1[j + 2][i] * FY[4][2]) + 
				  (img1[j + 2][i + 1] * FY[4][3]) + (img1[j + 2][i + 2] * FY[4][4]);
			
			if (sum == 0) sum = 1;
			
			value = 128 + (value/sum)/2;
			
	
			output[j][i] = value;
			
		}
	}
	
	outp = fopen("unescoFiveVertical.raw" , "wb");
	fwrite(output , 1 , y1*x1 , outp);
	fclose(outp);
	
	
	fclose(inp);
	
	//Trees -------------------------------------------------------------------------------------------------------------
	inp = fopen("trees.raw" , "rb");
	fread(img2 , 1 , y1*x1 , inp);
	
	
	//3x3 h
	value = 0;
	for (int j=1 ; j<y1 ; j++){
		for (int i=1 ; i<x1 ; i++){
			
			
			value =   (img2[j - 1][i - 1] * TX[0][0]) + (img2[j - 1][i] * TX[0][1]) + (img2[j - 1][i + 1] * TX[0][2])
					+ (img2[j][i - 1] * TX[1][0])     + (img2[j][i] * TX[1][1])     + (img2[j][i + 1] * TX[1][2])
					+ (img2[j + 1][i - 1] * TX[2][0]) + (img2[j + 1][i] * TX[2][1]) + (img2[j + 1][i + 1] * TX[2][2]);
			
			sum = (img2[j - 1][i + 1] * TX[0][2]) + 
				  (img2[j][i + 1] * TX[1][2]) + 
				  (img2[j + 1][i + 1] * TX[2][2]);
			
			if (sum == 0) sum = 1;
			
			value = 128 + (value/sum)/2;
			
			
			output[j][i] = value;
			
		}
	}
	
	outp = fopen("treesThreeHorizontal.raw" , "wb");
	fwrite(output , 1 , y1*x1 , outp);
	fclose(outp);
	
	//3x3 v
	value = 0;
	for (int j=1 ; j<y1 ; j++){
		for (int i=1 ; i<x1 ; i++){
			
			
			value =   (img2[j - 1][i - 1] * TY[0][0]) + (img2[j - 1][i] * TY[0][1]) + (img2[j - 1][i + 1] * TY[0][2])
					+ (img2[j][i - 1] * TY[1][0])     + (img2[j][i] * TY[1][1])     + (img2[j][i + 1] * TY[1][2])
					+ (img2[j + 1][i - 1] * TY[2][0]) + (img2[j + 1][i] * TY[2][1]) + (img2[j + 1][i + 1] * TY[2][2]);
			
			sum = (img2[j + 1][i - 1] * TY[2][0]) + 
				  (img2[j + 1][i] * TY[2][1]) + 
				  (img2[j + 1][i + 1] * TY[2][2]);
			
			if (sum == 0) sum = 1;
			
			value = 128 + (value/sum)/2;
			
			
			output[j][i] = value;
			
		}
	}
	
	outp = fopen("treesThreeVertical.raw" , "wb");
	fwrite(output , 1 , y1*x1 , outp);
	fclose(outp);
	
	//5x5 h
	value = 0;
	for (int j=1 ; j<y1 ; j++){
		for (int i=1 ; i<x1 ; i++){
			
			
			value =   (img2[j - 2][i - 2] * FX[0][0]) + (img2[j - 2][i -1] * FX[0][1]) + (img2[j - 2][i] * FX[0][2]) + (img2[j - 2][i + 1] * FX[0][3]) + (img2[j - 2][i + 2] * FX[0][4])
					+ (img2[j - 1][i - 2] * FX[1][0]) + (img2[j - 1][i -1] * FX[1][1]) + (img2[j - 1][i] * FX[1][2]) + (img2[j - 1][i + 1] * FX[1][3]) + (img2[j - 1][i + 2] * FX[1][4])
					+ (img2[j][i - 2] * FX[2][0]) + (img2[j][i -1] * FX[2][1]) + (img2[j][i] * FX[2][2]) + (img2[j][i + 1] * FX[2][3]) + (img2[j][i + 2] * FX[2][4])
					+ (img2[j + 1][i - 2] * FX[3][0]) + (img2[j + 1][i -1] * FX[3][1]) + (img2[j + 1][i] * FX[3][2]) + (img2[j + 1][i + 1] * FX[3][3]) + (img2[j + 1][i + 2] * FX[3][4])
					+ (img2[j + 2][i - 2] * FX[4][0]) + (img2[j + 2][i -1] * FX[4][1]) + (img2[j + 2][i] * FX[4][2]) + (img2[j + 2][i + 1] * FX[4][3]) + (img2[j + 2][i + 2] * FX[4][4]);
			
			sum = (img2[j - 2][i + 1] * FX[0][3]) + (img2[j - 2][i + 2] * FX[0][4]) + 
				  (img2[j - 1][i + 1] * FX[1][3]) + (img2[j - 1][i + 2] * FX[1][4]) +
				  (img2[j][i + 1] * FX[2][3]) + (img2[j][i + 2] * FX[2][4]) +
				  (img2[j + 1][i + 1] * FX[3][3]) + (img2[j + 1][i + 2] * FX[3][4]) +
				  (img2[j + 2][i + 1] * FX[4][3]) + (img2[j + 2][i + 2] * FX[4][4]);
			
			if (sum == 0) sum = 1;
			
			value = 128 + (value/sum)/2;
			
	
			output[j][i] = value;
			
		}
	}
	
	outp = fopen("treesFiveHorizontal.raw" , "wb");
	fwrite(output , 1 , y1*x1 , outp);
	fclose(outp);
	
	//5x5 v
	value = 0;
	for (int j=1 ; j<y1 ; j++){
		for (int i=1 ; i<x1 ; i++){
			
			
			value =   (img2[j - 2][i - 2] * FY[0][0]) + (img2[j - 2][i -1] * FY[0][1]) + (img2[j - 2][i] * FY[0][2]) + (img2[j - 2][i + 1] * FY[0][3]) + (img2[j - 2][i + 2] * FY[0][4])
					+ (img2[j - 1][i - 2] * FY[1][0]) + (img2[j - 1][i -1] * FY[1][1]) + (img2[j - 1][i] * FY[1][2]) + (img2[j - 1][i + 1] * FY[1][3]) + (img2[j - 1][i + 2] * FY[1][4])
					+ (img2[j][i - 2] * FY[2][0]) + (img2[j][i -1] * FY[2][1]) + (img2[j][i] * FY[2][2]) + (img2[j][i + 1] * FY[2][3]) + (img2[j][i + 2] * FY[2][4])
					+ (img2[j + 1][i - 2] * FY[3][0]) + (img2[j + 1][i -1] * FY[3][1]) + (img2[j + 1][i] * FY[3][2]) + (img2[j + 1][i + 1] * FY[3][3]) + (img2[j + 1][i + 2] * FY[3][4])
					+ (img2[j + 2][i - 2] * FY[4][0]) + (img2[j + 2][i -1] * FY[4][1]) + (img2[j + 2][i] * FY[4][2]) + (img2[j + 2][i + 1] * FY[4][3]) + (img2[j + 2][i + 2] * FY[4][4]);
			
			sum = (img2[j + 1][i - 2] * FY[3][0]) + (img2[j + 1][i -1] * FY[3][1]) + 
				  (img2[j + 1][i] * FY[3][2]) + (img2[j + 1][i + 1] * FY[3][3]) + 
				  (img2[j + 1][i + 2] * FY[3][4]) + (img2[j + 2][i - 2] * FY[4][0]) + 
				  (img2[j + 2][i -1] * FY[4][1]) + (img2[j + 2][i] * FY[4][2]) + 
				  (img2[j + 2][i + 1] * FY[4][3]) + (img2[j + 2][i + 2] * FY[4][4]);
			
			if (sum == 0) sum = 1;
			
			value = 128 + (value/sum)/2;
			
	
			output[j][i] = value;
			
		}
	}
	
	outp = fopen("treesFiveVertical.raw" , "wb");
	fwrite(output , 1 , y1*x1 , outp);
	fclose(outp);
	
	
	fclose(inp);
	
	//Circle---------------------------------------------------------------------------------------------------------------
	inp = fopen("circle.raw" , "rb");
	fread(img3 , 1 , y1*x1 , inp);
	
	
	//3x3 h
	value = 0;
	for (int j=1 ; j<y1 ; j++){
		for (int i=1 ; i<x1 ; i++){
			
			
			value =   (img3[j - 1][i - 1] * TX[0][0]) + (img3[j - 1][i] * TX[0][1]) + (img3[j - 1][i + 1] * TX[0][2])
					+ (img3[j][i - 1] * TX[1][0])     + (img3[j][i] * TX[1][1])     + (img3[j][i + 1] * TX[1][2])
					+ (img3[j + 1][i - 1] * TX[2][0]) + (img3[j + 1][i] * TX[2][1]) + (img3[j + 1][i + 1] * TX[2][2]);
			
			sum = (img3[j - 1][i + 1] * TX[0][2]) + 
				  (img3[j][i + 1] * TX[1][2]) + 
				  (img3[j + 1][i + 1] * TX[2][2]);
			
			if (sum == 0) sum = 1;
			
			value = 128 + (value/sum)/2;
			
			
			output[j][i] = value;
			
		}
	}
	
	outp = fopen("circleThreeHorizontal.raw" , "wb");
	fwrite(output , 1 , y1*x1 , outp);
	fclose(outp);
	
	//3x3 v
	value = 0;
	for (int j=1 ; j<y1 ; j++){
		for (int i=1 ; i<x1 ; i++){
			
			
			value =   (img3[j - 1][i - 1] * TY[0][0]) + (img3[j - 1][i] * TY[0][1]) + (img3[j - 1][i + 1] * TY[0][2])
					+ (img3[j][i - 1] * TY[1][0])     + (img3[j][i] * TY[1][1])     + (img3[j][i + 1] * TY[1][2])
					+ (img3[j + 1][i - 1] * TY[2][0]) + (img3[j + 1][i] * TY[2][1]) + (img3[j + 1][i + 1] * TY[2][2]);
			
			sum = (img3[j + 1][i - 1] * TY[2][0]) + 
				  (img3[j + 1][i] * TY[2][1]) + 
				  (img3[j + 1][i + 1] * TY[2][2]);
			
			if (sum == 0) sum = 1;
			
			value = 128 + (value/sum)/2;
			
			
			output[j][i] = value;
			
		}
	}
	
	outp = fopen("circleThreeVertical.raw" , "wb");
	fwrite(output , 1 , y1*x1 , outp);
	fclose(outp);
	
	//5x5 h
	value = 0;
	for (int j=1 ; j<y1 ; j++){
		for (int i=1 ; i<x1 ; i++){
			
			
			value =   (img3[j - 2][i - 2] * FX[0][0]) + (img3[j - 2][i -1] * FX[0][1]) + (img3[j - 2][i] * FX[0][2]) + (img3[j - 2][i + 1] * FX[0][3]) + (img3[j - 2][i + 2] * FX[0][4])
					+ (img3[j - 1][i - 2] * FX[1][0]) + (img3[j - 1][i -1] * FX[1][1]) + (img3[j - 1][i] * FX[1][2]) + (img3[j - 1][i + 1] * FX[1][3]) + (img3[j - 1][i + 2] * FX[1][4])
					+ (img3[j][i - 2] * FX[2][0]) + (img3[j][i -1] * FX[2][1]) + (img3[j][i] * FX[2][2]) + (img3[j][i + 1] * FX[2][3]) + (img3[j][i + 2] * FX[2][4])
					+ (img3[j + 1][i - 2] * FX[3][0]) + (img3[j + 1][i -1] * FX[3][1]) + (img3[j + 1][i] * FX[3][2]) + (img3[j + 1][i + 1] * FX[3][3]) + (img3[j + 1][i + 2] * FX[3][4])
					+ (img3[j + 2][i - 2] * FX[4][0]) + (img3[j + 2][i -1] * FX[4][1]) + (img3[j + 2][i] * FX[4][2]) + (img3[j + 2][i + 1] * FX[4][3]) + (img3[j + 2][i + 2] * FX[4][4]);
			
			sum = (img3[j - 2][i + 1] * FX[0][3]) + (img3[j - 2][i + 2] * FX[0][4]) + 
				  (img3[j - 1][i + 1] * FX[1][3]) + (img3[j - 1][i + 2] * FX[1][4]) +
				  (img3[j][i + 1] * FX[2][3]) + (img3[j][i + 2] * FX[2][4]) +
				  (img3[j + 1][i + 1] * FX[3][3]) + (img3[j + 1][i + 2] * FX[3][4]) +
				  (img3[j + 2][i + 1] * FX[4][3]) + (img3[j + 2][i + 2] * FX[4][4]);
			
			if (sum == 0) sum = 1;
			
			value = 128 + (value/sum)/2;
			
	
			output[j][i] = value;
			
		}
	}
	
	outp = fopen("circleFiveHorizontal.raw" , "wb");
	fwrite(output , 1 , y1*x1 , outp);
	fclose(outp);
	
	//5x5 v
	value = 0;
	for (int j=1 ; j<y1 ; j++){
		for (int i=1 ; i<x1 ; i++){
			
			
			value =   (img3[j - 2][i - 2] * FY[0][0]) + (img3[j - 2][i -1] * FY[0][1]) + (img3[j - 2][i] * FY[0][2]) + (img3[j - 2][i + 1] * FY[0][3]) + (img3[j - 2][i + 2] * FY[0][4])
					+ (img3[j - 1][i - 2] * FY[1][0]) + (img3[j - 1][i -1] * FY[1][1]) + (img3[j - 1][i] * FY[1][2]) + (img3[j - 1][i + 1] * FY[1][3]) + (img3[j - 1][i + 2] * FY[1][4])
					+ (img3[j][i - 2] * FY[2][0]) + (img3[j][i -1] * FY[2][1]) + (img3[j][i] * FY[2][2]) + (img3[j][i + 1] * FY[2][3]) + (img3[j][i + 2] * FY[2][4])
					+ (img3[j + 1][i - 2] * FY[3][0]) + (img3[j + 1][i -1] * FY[3][1]) + (img3[j + 1][i] * FY[3][2]) + (img3[j + 1][i + 1] * FY[3][3]) + (img3[j + 1][i + 2] * FY[3][4])
					+ (img3[j + 2][i - 2] * FY[4][0]) + (img3[j + 2][i -1] * FY[4][1]) + (img3[j + 2][i] * FY[4][2]) + (img3[j + 2][i + 1] * FY[4][3]) + (img3[j + 2][i + 2] * FY[4][4]);
			
			sum = (img3[j + 1][i - 2] * FY[3][0]) + (img3[j + 1][i -1] * FY[3][1]) + 
				  (img3[j + 1][i] * FY[3][2]) + (img3[j + 1][i + 1] * FY[3][3]) + 
				  (img3[j + 1][i + 2] * FY[3][4]) + (img3[j + 2][i - 2] * FY[4][0]) + 
				  (img3[j + 2][i -1] * FY[4][1]) + (img3[j + 2][i] * FY[4][2]) + 
				  (img3[j + 2][i + 1] * FY[4][3]) + (img3[j + 2][i + 2] * FY[4][4]);
			
			if (sum == 0) sum = 1;
			
			value = 128 + (value/sum)/2;
			
	
			output[j][i] = value;
			
		}
	}
	
	outp = fopen("circleFiveVertical.raw" , "wb");
	fwrite(output , 1 , y1*x1 , outp);
	fclose(outp);

	
	fclose(inp);

}//end main