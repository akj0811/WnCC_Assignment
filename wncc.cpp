#include<bits/stdc++.h>												// Header files.
using namespace std;
int main()
{
	int power[10];
	power[0]=1;
	for(int i=1;i<10;i++)
		power[i]=(power[i-1]*10);									// Calculating powers of 10 to evaluate decimals.
	fstream fin;
	fin.open("timestat.txt");
	vector<string> aray[3];
	int count=0,lcount=0;
	string x;
	while(fin>>x)													// Taking input from the file.
	{
		if(lcount)
		{
			lcount=0;
			aray[count].push_back(x);
			count=(count+1)%3;
		}
		else
			lcount++;
	}
	vector<double> ans[3];												// Processing the string input to obtain the desired time values.
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<aray[i].size();j++)
		{
			double final=0;
			int k;
			for(k=0;k<aray[i][j].size();k++)
			{
				if(aray[i][j][k]=='m')
					break;
			}
			for(int l=0;l<k;l++)
			{
				final=final*10;
				final+=(aray[i][j][l]-'0');
			}
			final=final*60;
			int temp=k;
			for(k=0;k<aray[i][j].size();k++)
			{
				if(aray[i][j][k]=='.')
					break;
			}
			double sec=0;
			for(int l=temp+1;l<k;l++)
			{
				sec=(sec*10);
				sec+=(aray[i][j][l]-'0');
			}
			final+=sec;
			sec=0;
			for(int l=k+1;l<aray[i][j].size()-1;l++)
			{
				sec=(sec*10);
				sec+=(aray[i][j][l]-'0');
			}
			final+=(sec/power[aray[i][j].size()-2-k]);
			ans[i].push_back(final);
		}
	}
	int total=ans[0].size();
	double avg[3];																// Average calculations
	for(int i=0;i<3;i++)
	{
		double sum=0;
		for(int j=0;j<total;j++)
			sum+=(ans[i][j]);
		avg[i]=(sum/total);
	}
	double deviations[3][total];												// Deviation Calculations
	double std[3];
	for(int i=0;i<3;i++)
	{
		double sum=0;
		for(int j=0;j<total;j++)
		{
			deviations[i][j]=(ans[i][j]-avg[i])*(ans[i][j]-avg[i]);
			sum+=deviations[i][j];
		}
		std[i]=(sum/(total-1));
		std[i]=(sqrt(std[i]));
	}
	pair<double,double> range[3];												// Range Calculations
	for(int i=0;i<3;i++)
	{
		range[i].first=avg[i]-std[i];
		range[i].second=avg[i]+std[i];
	}
	int number_range[3]={0};
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<total;j++)
		{
			if(ans[i][j]>=range[i].first&&ans[i][j]<=range[i].second)
				number_range[i]++;
		}
	}
	cout<<"Total number of runs                       - "<<total<<"\n";			// Output
	cout<<"Average real time                          - "<<avg[0]<<"\n";
	cout<<"Average user time                          - "<<avg[1]<<"\n";
	cout<<"Average system time                        - "<<avg[2]<<"\n";
	cout<<"S.D. of real time                          - "<<std[0]<<"\n";
	cout<<"S.D. of user time                          - "<<std[1]<<"\n";
	cout<<"S.D. of system time                        - "<<std[2]<<"\n";
	cout<<"Number of runs within range of real time   - "<<number_range[0]<<"\n";
	cout<<"Number of runs within range of user time   - "<<number_range[1]<<"\n";
	cout<<"Number of runs within range of system time - "<<number_range[2]<<"\n";
	return 0;
}