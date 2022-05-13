void choosePath(int pathNum) {
  for(int i=0;i<2000;i++)
    for(int j=0;j<5;j++)
        path[i][j] = 0;
        
  switch (pathNum) {
    case 1:  // Lissajous
      fileLength = 535;
      for(int i=0;i<fileLength;i++)
        for(int j=0;j<5;j++)
          path[i][j] = lissajousA[i][j];
      break;
    default:
      break;
  }
}
