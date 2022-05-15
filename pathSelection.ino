void choosePath(int pathNum) {
  for(int i=0;i<2000;i++)
    for(int j=0;j<5;j++)
        path[i][j] = 0;
        
  switch (pathNum) {
    case 1:  // Lissajous
      fileLength = 880;
      offsetAngle = 20;
      for(int i=0;i<fileLength;i++)
        for(int j=0;j<5;j++)
          path[i][j] = lissajousA[i][j];
      break;
    case 2:  // straight
      fileLength = 3;
      offsetAngle = 20;
      for(int i=0;i<fileLength;i++)
        for(int j=0;j<5;j++)
          path[i][j] = straight[i][j];
      break;
    case 3:  // spirals 2
      fileLength = 4;
      offsetAngle = 10;
      for(int i=0;i<fileLength;i++)
        for(int j=0;j<5;j++)
          path[i][j] = spirals[i][j];
      break;
    case 4:  // lissajous slow
      fileLength = 1408;
      offsetAngle = 10;
      for(long i=0;i<fileLength;i++)
        for(int j=0;j<5;j++)
          path[i][j] = lissajousB[i][j];
      break;
    default:
      break;
  }
}
