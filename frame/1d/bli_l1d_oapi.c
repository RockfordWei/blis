/*

   BLIS    
   An object-based framework for developing high-performance BLAS-like
   libraries.

   Copyright (C) 2014, The University of Texas at Austin

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    - Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    - Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    - Neither the name of The University of Texas at Austin nor the names
      of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
   HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

// Guard the function definitions so that they are only compiled when
// #included from files that define the object API macros.
#ifdef BLIS_ENABLE_OAPI

//
// Define object-based interfaces.
//

#undef  GENFRONT
#define GENFRONT( opname ) \
\
void PASTEMAC(opname,EX_SUF) \
     ( \
       obj_t*  x, \
       obj_t*  y  \
       BLIS_OAPI_CNTX_PARAM  \
     ) \
{ \
	BLIS_OAPI_CNTX_DECL \
\
	num_t     dt        = bli_obj_datatype( *x ); \
\
    doff_t    diagoffx  = bli_obj_diag_offset( *x ); \
    diag_t    diagx     = bli_obj_diag( *x ); \
    trans_t   transx    = bli_obj_conjtrans_status( *x ); \
	dim_t     m         = bli_obj_length( *y ); \
	dim_t     n         = bli_obj_width( *y ); \
    void*     buf_x     = bli_obj_buffer_at_off( *x ); \
    inc_t     rs_x      = bli_obj_row_stride( *x ); \
    inc_t     cs_x      = bli_obj_col_stride( *x ); \
    void*     buf_y     = bli_obj_buffer_at_off( *y ); \
    inc_t     rs_y      = bli_obj_row_stride( *y ); \
    inc_t     cs_y      = bli_obj_col_stride( *y ); \
\
	if ( bli_error_checking_is_enabled() ) \
	    PASTEMAC(opname,_check)( x, y ); \
\
	/* Invoke the typed function. */ \
	bli_call_ft_12 \
	( \
	   dt, \
	   opname, \
	   diagoffx, \
	   diagx, \
	   transx, \
	   m, \
	   n, \
	   buf_x, rs_x, cs_x, \
	   buf_y, rs_y, cs_y, \
	   cntx  \
	); \
}

GENFRONT( addd )
GENFRONT( copyd )
GENFRONT( subd )


#undef  GENFRONT
#define GENFRONT( opname ) \
\
void PASTEMAC(opname,EX_SUF) \
     ( \
       obj_t*  alpha, \
       obj_t*  x, \
       obj_t*  y  \
       BLIS_OAPI_CNTX_PARAM  \
     ) \
{ \
	BLIS_OAPI_CNTX_DECL \
\
	num_t     dt        = bli_obj_datatype( *x ); \
\
    doff_t    diagoffx  = bli_obj_diag_offset( *x ); \
    diag_t    diagx     = bli_obj_diag( *x ); \
    trans_t   transx    = bli_obj_conjtrans_status( *x ); \
	dim_t     m         = bli_obj_length( *y ); \
	dim_t     n         = bli_obj_width( *y ); \
    void*     buf_x     = bli_obj_buffer_at_off( *x ); \
    inc_t     rs_x      = bli_obj_row_stride( *x ); \
    inc_t     cs_x      = bli_obj_col_stride( *x ); \
    void*     buf_y     = bli_obj_buffer_at_off( *y ); \
    inc_t     rs_y      = bli_obj_row_stride( *y ); \
    inc_t     cs_y      = bli_obj_col_stride( *y ); \
\
	void*     buf_alpha; \
\
	obj_t     alpha_local; \
\
	if ( bli_error_checking_is_enabled() ) \
	    PASTEMAC(opname,_check)( alpha, x, y ); \
\
	/* Create local copy-casts of scalars (and apply internal conjugation
	   as needed). */ \
	bli_obj_scalar_init_detached_copy_of( dt, BLIS_NO_CONJUGATE, \
	                                      alpha, &alpha_local ); \
	buf_alpha = bli_obj_buffer_for_1x1( dt, alpha_local ); \
\
	/* Invoke the typed function. */ \
	bli_call_ft_13 \
	( \
	   dt, \
	   opname, \
	   diagoffx, \
	   diagx, \
	   transx, \
	   m, \
	   n, \
	   buf_alpha, \
	   buf_x, rs_x, cs_x, \
	   buf_y, rs_y, cs_y, \
	   cntx  \
	); \
}

GENFRONT( axpyd )
GENFRONT( scal2d )


#undef  GENFRONT
#define GENFRONT( opname ) \
\
void PASTEMAC(opname,EX_SUF) \
     ( \
       obj_t*  x  \
       BLIS_OAPI_CNTX_PARAM  \
     ) \
{ \
	BLIS_OAPI_CNTX_DECL \
\
	num_t     dt        = bli_obj_datatype( *x ); \
\
    doff_t    diagoffx  = bli_obj_diag_offset( *x ); \
	dim_t     m         = bli_obj_length( *x ); \
	dim_t     n         = bli_obj_width( *x ); \
    void*     buf_x     = bli_obj_buffer_at_off( *x ); \
    inc_t     rs_x      = bli_obj_row_stride( *x ); \
    inc_t     cs_x      = bli_obj_col_stride( *x ); \
\
	if ( bli_error_checking_is_enabled() ) \
	    PASTEMAC(opname,_check)( x ); \
\
	/* Invoke the void pointer-based function. */ \
	bli_call_ft_7 \
	( \
	   dt, \
	   opname, \
	   diagoffx, \
	   m, \
	   n, \
	   buf_x, rs_x, cs_x, \
	   cntx  \
	); \
}

GENFRONT( invertd )


#undef  GENFRONT
#define GENFRONT( opname ) \
\
void PASTEMAC(opname,EX_SUF) \
     ( \
       obj_t*  alpha, \
       obj_t*  x  \
       BLIS_OAPI_CNTX_PARAM  \
     ) \
{ \
	BLIS_OAPI_CNTX_DECL \
\
	num_t     dt        = bli_obj_datatype( *x ); \
\
    /* conj_t    conjalpha = bli_obj_conj_status( *alpha ); */ \
    doff_t    diagoffx  = bli_obj_diag_offset( *x ); \
	dim_t     m         = bli_obj_length( *x ); \
	dim_t     n         = bli_obj_width( *x ); \
    void*     buf_x     = bli_obj_buffer_at_off( *x ); \
    inc_t     rs_x      = bli_obj_row_stride( *x ); \
    inc_t     cs_x      = bli_obj_col_stride( *x ); \
\
	void*     buf_alpha; \
\
	obj_t     alpha_local; \
\
	if ( bli_error_checking_is_enabled() ) \
	    PASTEMAC(opname,_check)( alpha, x ); \
\
	/* Create local copy-casts of scalars (and apply internal conjugation
	   as needed). */ \
	bli_obj_scalar_init_detached_copy_of( dt, BLIS_NO_CONJUGATE, \
	                     alpha, &alpha_local ); \
	buf_alpha = bli_obj_buffer_for_1x1( dt, alpha_local ); \
\
	/* Invoke the typed function. */ \
	bli_call_ft_9 \
	( \
	   dt, \
	   opname, \
	   BLIS_NO_CONJUGATE, /* internal conjugation applied during copy-cast. */ \
	   diagoffx, \
	   m, \
	   n, \
	   buf_alpha, \
	   buf_x, rs_x, cs_x, \
	   cntx  \
	); \
}

GENFRONT( scald )
GENFRONT( setd )


#undef  GENFRONT
#define GENFRONT( opname ) \
\
void PASTEMAC(opname,EX_SUF) \
     ( \
       obj_t*  alpha, \
       obj_t*  x  \
       BLIS_OAPI_CNTX_PARAM  \
     ) \
{ \
	BLIS_OAPI_CNTX_DECL \
\
	num_t     dt        = bli_obj_datatype( *x ); \
\
    doff_t    diagoffx  = bli_obj_diag_offset( *x ); \
	dim_t     m         = bli_obj_length( *x ); \
	dim_t     n         = bli_obj_width( *x ); \
    void*     buf_x     = bli_obj_buffer_at_off( *x ); \
    inc_t     rs_x      = bli_obj_row_stride( *x ); \
    inc_t     cs_x      = bli_obj_col_stride( *x ); \
\
	void*     buf_alpha = bli_obj_buffer_for_1x1( dt, *alpha ); \
\
	if ( bli_error_checking_is_enabled() ) \
	    PASTEMAC(opname,_check)( alpha, x ); \
\
	/* Invoke the typed function. */ \
	bli_call_ft_8 \
	( \
	   dt, \
	   opname, \
	   diagoffx, \
	   m, \
	   n, \
	   buf_alpha, \
	   buf_x, rs_x, cs_x, \
	   cntx  \
	); \
}

GENFRONT( setid )


#endif

