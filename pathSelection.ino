void choosePath(int pathNum) {
  switch (pathNum) {
    case 1:  // Spirals
      fileLength = 599;
      for(int i=0;i<fileLength;i++)
        for(int j=0;j<11;j++)
          path[i][j] = 0;// myPath3[i][j];
      currLin = path[0][9];
      currRot = path[0][10];
      break;
    case 2:  // Spirals
      fileLength = 1067;
      for(int i=0;i<fileLength;i++)
        for(int j=0;j<11;j++)
          path[i][j] =0;// myPath4[i][j];
      currLin = path[0][9];
      currRot = path[0][10];
      break;
    default:
      break;
  }
}
