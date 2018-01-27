#ifndef USE_XTRANSFORM
void make_closed_loop()
{
  cnttype i,j;
#ifdef USE_INTERVALS
  make_nondet_coeffs(plant.coeffs,plant.uncertainty,plant_cbmc);
  make_nondet_transform(transform.coeffs,transform.uncertainty,transform_cbmc);
#else
  copy_coeffs(plant.coeffs,plant_cbmc);
  copy_transform(transform.coeffs,transform_cbmc);  
#endif    
  fxp_check_coeffs(controller,implK);
  for (i = 0;i<_DIMENSION;i++)
  {
    controller_cbmc[i]=0;
    for (j = 0;j<_DIMENSION;j++)
    {
      controller_cbmc[i]-=transform_cbmc[j][i]*controller[j];
    }
#ifdef USE_SCALING
    controller_cbmc[i]*=transform.scale;
#endif
  }
#ifndef __CPROVER
    print_matrix("T ",transform_cbmc);
    print_vector("controller",controller);
    print_vector("plant polynomial",plant_cbmc);
    print_vector("controller polynomial",controller_cbmc);
#endif
#ifdef _USE_OBSERVER
  #ifdef USE_INTERVALS
    make_nondet_transform(observer_pretransform.coeffs,observer_pretransform.uncertainty,observer_transform_cbmc);
  #else
    copy_transform(observer_pretransform.coeffs,observer_transform_cbmc);
  #endif
  fxp_check_coeffs(observer,implL);
  for (i = 0;i<_DIMENSION;i++)
  {
    observer_cbmc[i]=0;
    for (j = 0;j<_DIMENSION;j++)
    {
      observer_cbmc[i]-=observer_transform_cbmc[i][j]*observer[j];
    }
    observer_cbmc[i]*=implL.scale;
  #ifdef USE_SCALING
    observer_cbmc[i]*=observer_pretransform.scale;
  #endif
  }
  //Has to be done before plant_cbmc is updated
  for (i = 0;i<_DIMENSION;i++) observer_plant_cbmc[i]=plant_cbmc[i]-observer_cbmc[i];
#endif
  for (i = 0;i<_DIMENSION;i++) plant_cbmc[i]-=controller_cbmc[i];
#ifndef __CPROVER
    print_vector("loop polynomial",plant_cbmc);
#endif
}
#endif

signed int check_stability_closedloop(vectort a)
{
  cnttype n=_DIMENSION+1;
  cnttype columns=n;
  control_floatt m[n][n];
  cnttype i,j;
  control_floatt sum=_one;
  m[0][0]=1;
#ifndef __CPROVER
  printf("polynomial[%d] %f",n,m[0][0]);
#endif
  for(i = 0 ; i < _DIMENSION; i++) 
  { 
    m[0][i+1]=a[i];
    sum += a[i];
#ifndef __CPROVER
    printf(",%f",a[i]);
#endif
  }
#ifdef __CPROVER
  verify_assume(m[0][0] > _transform_error);
  verify_assume(sum > _sum_error);
  verify_assume(m[0][n-1]!=0);
  verify_assume(m[0][n-1]+_transform_error < m[0][0]);
  verify_assume(-m[0][n-1]+_transform_error < m[0][0]);
#else
  printf("\n");
  printf("m[0][0]=%f>%f\n",m[0][0],_transform_error);
  if (!(m[0][0] > _transform_error)) 
  {
    return 0;
  }
  printf("sum=%f>%f\n",sum,_sum_error);
  if (!(sum > _sum_error))
  {
    return 0;
  }
  printf("m[0][%d]=%f<m[0][0]=%f\n",n-1,m[0][n - 1],m[0][0]);
  if (m[0][n - 1]==0)
  {
    return 0;    
  }  
  if (!(m[0][n - 1]+_transform_error < m[0][0])) 
  {
    return 0;
  }
  printf("-m[0][%d]=%f<m[0][0]=%f\n",n-1,m[0][n - 1],m[0][0]);
  if (!(-m[0][n - 1]+_transform_error < m[0][0])) 
  {
    return 0;
  }
#endif
  sum = _zero;
  for(i = 0 ; i < n; i++)
  {
    if (((n -i)&1)!=0) sum+=m[0][i];
    else               sum-=m[0][i];
  }
  if ((n&1)==0) sum=-sum;
#ifdef __CPROVER
  verify_assume(sum > _sum_error);
#else
  printf("sum_o-sum_e=%f>0\n",sum);
  if (!(sum > _sum_error)) return 0;
#endif
  columns--;
  control_floatt error=_transform_error;
  control_floatt mag=1;
  for(i=1;i<n;i++)
  {
    //denominator is always >0
    control_floatt factor=m[i-1][columns] / m[i-1][0];
#ifndef __CPROVER
    printf("factor=%f,p=",factor);
#endif
#ifdef __CHECK_FP
    if (m[i-1][0]<0) verify_assume(m[i-1][0]<-(mag*mag/_imp_max+_transform_error));
    else             verify_assume(m[i-1][0]> (mag*mag/_imp_max+_transform_error));//check for overflow.
    control_floatt efactor=m[i-1][columns];
    if (efactor<0) efactor=-efactor;
    efactor+=_transform_error;
    efactor/=m[i-1][0]-_transform_error;
    efactor-=factor;
    verify_assume(efactor<_transform_error*mag);
    if (factor>0) 
    {
      _transform_error*=2+factor;//Unsound! does not consider the error in factor (a+e/b-e = a/(b-e) +e/(b-e))
      mag+=mag*factor;
    }
    else
    {
      _transform_error*=2-factor;
      mag-=mag*factor;
    }
#endif
    for(j=0;j<columns;j++)
    {
      m[i][j] = m[i - 1][j] - factor * m[i - 1][columns-j];      
#ifndef __CPROVER
      printf("%f,",m[i][j]);
#endif
    }
#ifdef __CPROVER
      verify_assume(m[i][0] >= _transform_error);
#else
    printf("m[%d]=%f>%f\n", i, m[i][0],_transform_error);
    if (!(m[i][0] >= _transform_error)) return 0;
#endif
    columns--;
  }
  return 1;
}

signed int check_restricted_stability(vectort a,control_floatt speed_factor)
{
  cnttype i,j;
  vectort polynomial;
  for (i=0;i<_DIMENSION;i++)
  {
    polynomial[i]=a[i];
    for (j=0;j<=i;j++) polynomial[i]*=speed_factor;
  }
  #ifndef __CPROVER
    printf("speed factor=%f\n",speed_factor);
    print_vector("a ",polynomial);  
    print_vector("P ",polynomial);
  #endif
  return check_stability_closedloop(polynomial);
}