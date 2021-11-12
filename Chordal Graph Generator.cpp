#include<bits/stdc++.h>
using namespace std;

int main(){
	
	FILE *fp = NULL;
	fp = fopen("test.txt", "w+");
	int n;
	scanf("%d",&n);
	fprintf(fp,"%d %d\n",n,2 * n - 3);
	for(int i = 2 ; i <= n - 1; i ++){
		fprintf(fp,"%d %d\n",i,i+1);
	}

	for(int i = 2 ; i <= n ; i ++){
		fprintf(fp,"1 %d\n",i);
	}
	   fclose(fp);
}


