

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Wed Mar 22 05:30:35 2017
 */
/* Compiler settings for HyperPlane.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __HyperPlane_h_h__
#define __HyperPlane_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IHyperPlane_FWD_DEFINED__
#define __IHyperPlane_FWD_DEFINED__
typedef interface IHyperPlane IHyperPlane;

#endif 	/* __IHyperPlane_FWD_DEFINED__ */


#ifndef __CHyperPlaneDoc_FWD_DEFINED__
#define __CHyperPlaneDoc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CHyperPlaneDoc CHyperPlaneDoc;
#else
typedef struct CHyperPlaneDoc CHyperPlaneDoc;
#endif /* __cplusplus */

#endif 	/* __CHyperPlaneDoc_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __HyperPlane_LIBRARY_DEFINED__
#define __HyperPlane_LIBRARY_DEFINED__

/* library HyperPlane */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_HyperPlane;

#ifndef __IHyperPlane_DISPINTERFACE_DEFINED__
#define __IHyperPlane_DISPINTERFACE_DEFINED__

/* dispinterface IHyperPlane */
/* [uuid] */ 


EXTERN_C const IID DIID_IHyperPlane;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("57AC423D-3BFB-4FBE-9DFD-6268C09C0159")
    IHyperPlane : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IHyperPlaneVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IHyperPlane * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IHyperPlane * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IHyperPlane * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IHyperPlane * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IHyperPlane * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IHyperPlane * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IHyperPlane * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IHyperPlaneVtbl;

    interface IHyperPlane
    {
        CONST_VTBL struct IHyperPlaneVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHyperPlane_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IHyperPlane_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IHyperPlane_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IHyperPlane_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IHyperPlane_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IHyperPlane_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IHyperPlane_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IHyperPlane_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CHyperPlaneDoc;

#ifdef __cplusplus

class DECLSPEC_UUID("74059D69-9F0D-426B-AB40-444845B0104A")
CHyperPlaneDoc;
#endif
#endif /* __HyperPlane_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


