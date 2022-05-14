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
    case 2:  // SpiralsA
      fileLength = 900;
      offsetAngle = 20;
      for(int i=0;i<fileLength;i++)
        for(int j=0;j<5;j++)
          path[i][j] = spiralsA[i][j];
      break;
    case 3:  // straight
      fileLength = 3;
      offsetAngle = 20;
      for(int i=0;i<fileLength;i++)
        for(int j=0;j<5;j++)
          path[i][j] = straight[i][j];
      break;
    case 4:  // spirals 2
      fileLength = 4;
      offsetAngle = 10;
      for(int i=0;i<fileLength;i++)
        for(int j=0;j<5;j++)
          path[i][j] = spiralsB[i][j];
      break;
    case 5:  // spirals 2
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
