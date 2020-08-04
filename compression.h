static int
compress(double* array, int nx, int ny, double tolerance)
{
  int status = 0;    /* return value: 0 = success */
  zfp_type type;     /* array scalar type */
  zfp_field* field;  /* array meta data */
  zfp_stream* zfp;   /* compressed stream */
  void* buffer;      /* storage for compressed stream */
  size_t bufsize;    /* byte size of compressed buffer */
  bitstream* stream; /* bit stream to write to or read from */
  size_t zfpsize;    /* byte size of compressed stream */

  /* allocate meta data for the 2D array a[nz][ny][nx] */
  type = zfp_type_double;
  field = zfp_field_2d(array, type, nx, ny);

  /* allocate meta data for a compressed stream */
  zfp = zfp_stream_open(NULL);

  /* set compression mode and parameters via one of four functions */
  //zfp_stream_set_reversible(zfp); 
  //zfp_stream_set_rate(zfp, rate, type, 2, 0); 
  //zfp_stream_set_precision(zfp, precision); 
  zfp_stream_set_accuracy(zfp, tolerance);

  /* allocate buffer for compressed data */
  bufsize = zfp_stream_maximum_size(zfp, field);

  buffer = malloc(bufsize);

  /* associate bit stream with allocated buffer */
  stream = stream_open(buffer, bufsize);
  zfp_stream_set_bit_stream(zfp, stream);
  zfp_stream_rewind(zfp);

  //for(size_t i = 0; i < 10000; i++){
  //  std::cout << array[i] << " ";
  //}
  //std::cout << std::endl;

  zfpsize = zfp_compress(zfp, field);
  if(!zfpsize){
    fprintf(stderr, "compression failed\n");
    status = 1;
  }


  //check?
  zfp_stream_flush(zfp);
  zfp_stream_rewind(zfp);

  //zfpsize = fread(buffer, 1, bufsize, stdin); 
  if(!zfp_decompress(zfp, field)){
    //fprintf(stderr, "decompression failed\n");
    std::cout << "decompression failed \n" << std::endl;
    status = 1;
  }else{
    fwrite(buffer, 1, zfpsize, stdout);
    std::cout << "done with decompression" << std::endl;
  }

 //for(size_t i = 0; i < 10000; i++){
 //   std::cout << array[i] << " ";
 // }
 // std::cout << std::endl;
  /* compress or decompress entire array */
  //if (decompress) {

    /* read compressed stream and decompress array */
  //  zfpsize = fread(buffer, 1, bufsize, stdin); 
  //  if (!zfp_decompress(zfp, field)) {
  //    fprintf(stderr, "decompression failed\n");
  //    status = 1;
  //  }
  //}
  //else {
    
    /* compress array and output compressed stream */
  //  zfpsize = zfp_compress(zfp, field);
  //  if (!zfpsize) {
  //    fprintf(stderr, "compression failed\n");
  //    status = 1;
  //  }
  //  else
  //    fwrite(buffer, 1, zfpsize, stdout);
  //}

  /* clean up */
  zfp_field_free(field);
  zfp_stream_close(zfp);
  stream_close(stream);
  free(buffer);
  free(array);

  return status;
}