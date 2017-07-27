

ans=INT_MAX;
	for(int k=1;k<=m;k++)
	{
		for(int i=1;i<k-1;i++)
			for(int j=i+1;j<k;j++)
				ans=min(ans,g[k][i]+dist[i][j]+g[j][k]);

		for(int i=1;i<=m;i++)
			if(i!=k)
				for(int j=1;j<=m;j++)
					if(j!=i && j!=k)
						dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
	}