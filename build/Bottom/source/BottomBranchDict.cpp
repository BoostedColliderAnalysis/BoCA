//
// File generated by /usr/bin/rootcint at Sat Jun 20 20:44:32 2015

// Do NOT change. Changes will be lost next time file is generated
//

#define R__DICTIONARY_FILENAME BottomBranchDict
#include "RConfig.h" //rootcint 4834
#if !defined(R__ACCESS_IN_SYMBOL)
//Break the privacy of classes -- Disabled for the moment
#define private public
#define protected public
#endif

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;
#include "BottomBranchDict.h"

#include "TClass.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"

// Direct notice to TROOT of the dictionary's loading.
namespace {
   static struct DictInit {
      DictInit() {
         ROOT::RegisterModule();
      }
   } __TheDictionaryInitializer;
}

// START OF SHADOWS

namespace ROOT {
   namespace Shadow {
   } // of namespace Shadow
} // of namespace ROOT
// END OF SHADOWS

namespace analysis {
   namespace ROOT {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static void analysis_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("analysis", 0 /*version*/, "/home/toodles/madness/analysis/Bottom/include/HBranchBTagger.hh", 6,
                     ::ROOT::DefineBehavior((void*)0,(void*)0),
                     &analysis_Dictionary, 4);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_(Init));

      // Dictionary for non-ClassDef classes
      static void analysis_Dictionary() {
         GenerateInitInstance()->GetClass();
      }

   }
}

namespace analysis {
namespace bottom {
   namespace ROOT {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static void analysiscLcLbottom_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("analysis::bottom", 0 /*version*/, "/home/toodles/madness/analysis/Bottom/include/HBranchBTagger.hh", 8,
                     ::ROOT::DefineBehavior((void*)0,(void*)0),
                     &analysiscLcLbottom_Dictionary, 4);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_(Init));

      // Dictionary for non-ClassDef classes
      static void analysiscLcLbottom_Dictionary() {
         GenerateInitInstance()->GetClass();
      }

   }
}
}

namespace ROOT {
   void analysiscLcLbottomcLcLHBTaggerBranch_ShowMembers(void *obj, TMemberInspector &R__insp);
   static void *new_analysiscLcLbottomcLcLHBTaggerBranch(void *p = 0);
   static void *newArray_analysiscLcLbottomcLcLHBTaggerBranch(Long_t size, void *p);
   static void delete_analysiscLcLbottomcLcLHBTaggerBranch(void *p);
   static void deleteArray_analysiscLcLbottomcLcLHBTaggerBranch(void *p);
   static void destruct_analysiscLcLbottomcLcLHBTaggerBranch(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::analysis::bottom::HBTaggerBranch*)
   {
      ::analysis::bottom::HBTaggerBranch *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::analysis::bottom::HBTaggerBranch >(0);
      static ::ROOT::TGenericClassInfo 
         instance("analysis::bottom::HBTaggerBranch", ::analysis::bottom::HBTaggerBranch::Class_Version(), "/home/toodles/madness/analysis/Bottom/include/HBranchBTagger.hh", 16,
                  typeid(::analysis::bottom::HBTaggerBranch), DefineBehavior(ptr, ptr),
                  &::analysis::bottom::HBTaggerBranch::Dictionary, isa_proxy, 4,
                  sizeof(::analysis::bottom::HBTaggerBranch) );
      instance.SetNew(&new_analysiscLcLbottomcLcLHBTaggerBranch);
      instance.SetNewArray(&newArray_analysiscLcLbottomcLcLHBTaggerBranch);
      instance.SetDelete(&delete_analysiscLcLbottomcLcLHBTaggerBranch);
      instance.SetDeleteArray(&deleteArray_analysiscLcLbottomcLcLHBTaggerBranch);
      instance.SetDestructor(&destruct_analysiscLcLbottomcLcLHBTaggerBranch);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::analysis::bottom::HBTaggerBranch*)
   {
      return GenerateInitInstanceLocal((::analysis::bottom::HBTaggerBranch*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::analysis::bottom::HBTaggerBranch*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

      namespace analysis {
         namespace bottom {
//______________________________________________________________________________
TClass *HBTaggerBranch::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *HBTaggerBranch::Class_Name()
{
   return "analysis::bottom::HBTaggerBranch";
}

//______________________________________________________________________________
const char *HBTaggerBranch::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::analysis::bottom::HBTaggerBranch*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int HBTaggerBranch::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::analysis::bottom::HBTaggerBranch*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void HBTaggerBranch::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::analysis::bottom::HBTaggerBranch*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *HBTaggerBranch::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::analysis::bottom::HBTaggerBranch*)0x0)->GetClass();
   return fgIsA;
}

} // namespace analysis::bottom
} // namespace analysis::bottom
      namespace analysis {
         namespace bottom {
//______________________________________________________________________________
void HBTaggerBranch::Streamer(TBuffer &R__b)
{
   // Stream an object of class analysis::bottom::HBTaggerBranch.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(analysis::bottom::HBTaggerBranch::Class(),this);
   } else {
      R__b.WriteClassBuffer(analysis::bottom::HBTaggerBranch::Class(),this);
   }
}

} // namespace analysis::bottom
} // namespace analysis::bottom
//______________________________________________________________________________
      namespace analysis {
         namespace bottom {
void HBTaggerBranch::ShowMembers(TMemberInspector &R__insp)
{
      // Inspect the data members of an object of class analysis::bottom::HBTaggerBranch.
      TClass *R__cl = ::analysis::bottom::HBTaggerBranch::IsA();
      if (R__cl || R__insp.IsA()) { }
      R__insp.Inspect(R__cl, R__insp.GetParent(), "VertexMass", &VertexMass);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "JetMass", &JetMass);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "VertexNumber", &VertexNumber);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "Pull", &Pull);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "Vertex", &Vertex);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "DeltaR", &DeltaR);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "BTag", &BTag);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "BdtBTag", &BdtBTag);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "BCutSigEff", &BCutSigEff);
      //This works around a msvc bug and should be harmless on other platforms
      typedef analysis::Branch baseClass1;
      baseClass1::ShowMembers(R__insp);
}

} // namespace analysis::bottom
} // namespace analysis::bottom
namespace ROOT {
   // Wrappers around operator new
   static void *new_analysiscLcLbottomcLcLHBTaggerBranch(void *p) {
      return  p ? new(p) ::analysis::bottom::HBTaggerBranch : new ::analysis::bottom::HBTaggerBranch;
   }
   static void *newArray_analysiscLcLbottomcLcLHBTaggerBranch(Long_t nElements, void *p) {
      return p ? new(p) ::analysis::bottom::HBTaggerBranch[nElements] : new ::analysis::bottom::HBTaggerBranch[nElements];
   }
   // Wrapper around operator delete
   static void delete_analysiscLcLbottomcLcLHBTaggerBranch(void *p) {
      delete ((::analysis::bottom::HBTaggerBranch*)p);
   }
   static void deleteArray_analysiscLcLbottomcLcLHBTaggerBranch(void *p) {
      delete [] ((::analysis::bottom::HBTaggerBranch*)p);
   }
   static void destruct_analysiscLcLbottomcLcLHBTaggerBranch(void *p) {
      typedef ::analysis::bottom::HBTaggerBranch current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::analysis::bottom::HBTaggerBranch

/********************************************************
* BottomBranchDict.cpp
* CAUTION: DON'T CHANGE THIS FILE. THIS FILE IS AUTOMATICALLY GENERATED
*          FROM HEADER FILES LISTED IN G__setup_cpp_environmentXXX().
*          CHANGE THOSE HEADER FILES AND REGENERATE THIS FILE.
********************************************************/

#ifdef G__MEMTEST
#undef malloc
#undef free
#endif

#if defined(__GNUC__) && __GNUC__ >= 4 && ((__GNUC_MINOR__ == 2 && __GNUC_PATCHLEVEL__ >= 1) || (__GNUC_MINOR__ >= 3))
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

extern "C" void G__cpp_reset_tagtableBottomBranchDict();

extern "C" void G__set_cpp_environmentBottomBranchDict() {
  G__add_compiledheader("TObject.h");
  G__add_compiledheader("TMemberInspector.h");
  G__add_compiledheader("HBranchBTagger.cpp");
  G__cpp_reset_tagtableBottomBranchDict();
}
#include <new>
extern "C" int G__cpp_dllrevBottomBranchDict() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* analysis */

/* analysis::bottom */

/* analysis::bottom::HBTaggerBranch */
static int G__BottomBranchDict_195_0_1(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   analysis::bottom::HBTaggerBranch* p = NULL;
   char* gvp = (char*) G__getgvp();
   int n = G__getaryconstruct();
   if (n) {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new analysis::bottom::HBTaggerBranch[n];
     } else {
       p = new((void*) gvp) analysis::bottom::HBTaggerBranch[n];
     }
   } else {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new analysis::bottom::HBTaggerBranch;
     } else {
       p = new((void*) gvp) analysis::bottom::HBTaggerBranch;
     }
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__BottomBranchDictLN_analysiscLcLbottomcLcLHBTaggerBranch));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BottomBranchDict_195_0_2(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) analysis::bottom::HBTaggerBranch::Class());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BottomBranchDict_195_0_3(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) analysis::bottom::HBTaggerBranch::Class_Name());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BottomBranchDict_195_0_4(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 115, (long) analysis::bottom::HBTaggerBranch::Class_Version());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BottomBranchDict_195_0_5(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      analysis::bottom::HBTaggerBranch::Dictionary();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BottomBranchDict_195_0_9(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((analysis::bottom::HBTaggerBranch*) G__getstructoffset())->StreamerNVirtual(*(TBuffer*) libp->para[0].ref);
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BottomBranchDict_195_0_10(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) analysis::bottom::HBTaggerBranch::DeclFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BottomBranchDict_195_0_11(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) analysis::bottom::HBTaggerBranch::ImplFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BottomBranchDict_195_0_12(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) analysis::bottom::HBTaggerBranch::ImplFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BottomBranchDict_195_0_13(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) analysis::bottom::HBTaggerBranch::DeclFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic copy constructor
static int G__BottomBranchDict_195_0_14(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)

{
   analysis::bottom::HBTaggerBranch* p;
   void* tmp = (void*) G__int(libp->para[0]);
   p = new analysis::bottom::HBTaggerBranch(*(analysis::bottom::HBTaggerBranch*) tmp);
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__BottomBranchDictLN_analysiscLcLbottomcLcLHBTaggerBranch));
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic destructor
typedef analysis::bottom::HBTaggerBranch G__TanalysiscLcLbottomcLcLHBTaggerBranch;
static int G__BottomBranchDict_195_0_15(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   char* gvp = (char*) G__getgvp();
   long soff = G__getstructoffset();
   int n = G__getaryconstruct();
   //
   //has_a_delete: 1
   //has_own_delete1arg: 0
   //has_own_delete2arg: 0
   //
   if (!soff) {
     return(1);
   }
   if (n) {
     if (gvp == (char*)G__PVOID) {
       delete[] (analysis::bottom::HBTaggerBranch*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       for (int i = n - 1; i >= 0; --i) {
         ((analysis::bottom::HBTaggerBranch*) (soff+(sizeof(analysis::bottom::HBTaggerBranch)*i)))->~G__TanalysiscLcLbottomcLcLHBTaggerBranch();
       }
       G__setgvp((long)gvp);
     }
   } else {
     if (gvp == (char*)G__PVOID) {
       delete (analysis::bottom::HBTaggerBranch*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       ((analysis::bottom::HBTaggerBranch*) (soff))->~G__TanalysiscLcLbottomcLcLHBTaggerBranch();
       G__setgvp((long)gvp);
     }
   }
   G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic assignment operator
static int G__BottomBranchDict_195_0_16(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   analysis::bottom::HBTaggerBranch* dest = (analysis::bottom::HBTaggerBranch*) G__getstructoffset();
   *dest = *(analysis::bottom::HBTaggerBranch*) libp->para[0].ref;
   const analysis::bottom::HBTaggerBranch& obj = *dest;
   result7->ref = (long) (&obj);
   result7->obj.i = (long) (&obj);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* analysis */

/* analysis::bottom */

/* analysis::bottom::HBTaggerBranch */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncBottomBranchDict {
 public:
  G__Sizep2memfuncBottomBranchDict(): p(&G__Sizep2memfuncBottomBranchDict::sizep2memfunc) {}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncBottomBranchDict::*p)();
};

size_t G__get_sizep2memfuncBottomBranchDict()
{
  G__Sizep2memfuncBottomBranchDict a;
  G__setsizep2memfunc((int)a.sizep2memfunc());
  return((size_t)a.sizep2memfunc());
}


/*********************************************************
* virtual base class offset calculation interface
*********************************************************/

   /* Setting up class inheritance */

/*********************************************************
* Inheritance information setup/
*********************************************************/
extern "C" void G__cpp_setup_inheritanceBottomBranchDict() {

   /* Setting up class inheritance */
   if(0==G__getnumbaseclass(G__get_linked_tagnum(&G__BottomBranchDictLN_analysiscLcLbottomcLcLHBTaggerBranch))) {
     analysis::bottom::HBTaggerBranch *G__Lderived;
     G__Lderived=(analysis::bottom::HBTaggerBranch*)0x1000;
     {
       analysis::Branch *G__Lpbase=(analysis::Branch*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__BottomBranchDictLN_analysiscLcLbottomcLcLHBTaggerBranch),G__get_linked_tagnum(&G__BottomBranchDictLN_analysiscLcLBranch),(long)G__Lpbase-(long)G__Lderived,1,1);
     }
     {
       TObject *G__Lpbase=(TObject*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__BottomBranchDictLN_analysiscLcLbottomcLcLHBTaggerBranch),G__get_linked_tagnum(&G__BottomBranchDictLN_TObject),(long)G__Lpbase-(long)G__Lderived,1,0);
     }
   }
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetableBottomBranchDict() {

   /* Setting up typedef entry */
   G__search_typename2("Version_t",115,-1,0,-1);
   G__setnewtype(-1,"Class version identifier (short)",0);
   G__search_typename2("vector<ROOT::TSchemaHelper>",117,G__get_linked_tagnum(&G__BottomBranchDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__BottomBranchDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__BottomBranchDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__BottomBranchDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__BottomBranchDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<TVirtualArray*>",117,G__get_linked_tagnum(&G__BottomBranchDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__BottomBranchDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__BottomBranchDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__BottomBranchDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__BottomBranchDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("pair<float&,std::string>",117,G__get_linked_tagnum(&G__BottomBranchDictLN_pairlEfloataNcOstringgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<ObsPair>",117,G__get_linked_tagnum(&G__BottomBranchDictLN_vectorlEpairlEfloataNcOstringgRcOallocatorlEpairlEfloataNcOstringgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__BottomBranchDictLN_reverse_iteratorlEvectorlEpairlEfloataNcOstringgRcOallocatorlEpairlEfloataNcOstringgRsPgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__BottomBranchDictLN_vectorlEpairlEfloataNcOstringgRcOallocatorlEpairlEfloataNcOstringgRsPgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__BottomBranchDictLN_reverse_iteratorlEvectorlEpairlEfloataNcOstringgRcOallocatorlEpairlEfloataNcOstringgRsPgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__BottomBranchDictLN_vectorlEpairlEfloataNcOstringgRcOallocatorlEpairlEfloataNcOstringgRsPgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<pair<float&,string> >",117,G__get_linked_tagnum(&G__BottomBranchDictLN_vectorlEpairlEfloataNcOstringgRcOallocatorlEpairlEfloataNcOstringgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* analysis */
static void G__setup_memvaranalysis(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__BottomBranchDictLN_analysis));
   {
   }
   G__tag_memvar_reset();
}


   /* analysis::bottom */
static void G__setup_memvaranalysiscLcLbottom(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__BottomBranchDictLN_analysiscLcLbottom));
   {
   }
   G__tag_memvar_reset();
}


   /* analysis::bottom::HBTaggerBranch */
static void G__setup_memvaranalysiscLcLbottomcLcLHBTaggerBranch(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__BottomBranchDictLN_analysiscLcLbottomcLcLHBTaggerBranch));
   { analysis::bottom::HBTaggerBranch *p; p=(analysis::bottom::HBTaggerBranch*)0x1000; if (p) { }
   G__memvar_setup((void*)((long)(&p->VertexMass)-(long)(p)),102,0,0,-1,-1,-1,1,"VertexMass=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->JetMass)-(long)(p)),102,0,0,-1,-1,-1,1,"JetMass=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->VertexNumber)-(long)(p)),102,0,0,-1,-1,-1,1,"VertexNumber=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->Pull)-(long)(p)),102,0,0,-1,-1,-1,1,"Pull=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->Vertex)-(long)(p)),102,0,0,-1,-1,-1,1,"Vertex=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->DeltaR)-(long)(p)),102,0,0,-1,-1,-1,1,"DeltaR=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->BTag)-(long)(p)),102,0,0,-1,-1,-1,1,"BTag=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->BdtBTag)-(long)(p)),102,0,0,-1,-1,-1,1,"BdtBTag=",0,(char*)NULL);
   G__memvar_setup((void*)((long)(&p->BCutSigEff)-(long)(p)),102,0,0,-1,-1,-1,1,"BCutSigEff=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__BottomBranchDictLN_TClass),-1,-2,4,"fgIsA=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarBottomBranchDict() {
}
/***********************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
***********************************************************/

/*********************************************************
* Member function information setup for each class
*********************************************************/
static void G__setup_memfuncanalysis(void) {
   /* analysis */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__BottomBranchDictLN_analysis));
   G__tag_memfunc_reset();
}

static void G__setup_memfuncanalysiscLcLbottom(void) {
   /* analysis::bottom */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__BottomBranchDictLN_analysiscLcLbottom));
   G__tag_memfunc_reset();
}

static void G__setup_memfuncanalysiscLcLbottomcLcLHBTaggerBranch(void) {
   /* analysis::bottom::HBTaggerBranch */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__BottomBranchDictLN_analysiscLcLbottomcLcLHBTaggerBranch));
   G__memfunc_setup("HBTaggerBranch",1330,G__BottomBranchDict_195_0_1, 105, G__get_linked_tagnum(&G__BottomBranchDictLN_analysiscLcLbottomcLcLHBTaggerBranch), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Class",502,G__BottomBranchDict_195_0_2, 85, G__get_linked_tagnum(&G__BottomBranchDictLN_TClass), -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (TClass* (*)())(&analysis::bottom::HBTaggerBranch::Class) ), 0);
   G__memfunc_setup("Class_Name",982,G__BottomBranchDict_195_0_3, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&analysis::bottom::HBTaggerBranch::Class_Name) ), 0);
   G__memfunc_setup("Class_Version",1339,G__BottomBranchDict_195_0_4, 115, -1, G__defined_typename("Version_t"), 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (Version_t (*)())(&analysis::bottom::HBTaggerBranch::Class_Version) ), 0);
   G__memfunc_setup("Dictionary",1046,G__BottomBranchDict_195_0_5, 121, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (void (*)())(&analysis::bottom::HBTaggerBranch::Dictionary) ), 0);
   G__memfunc_setup("IsA",253,(G__InterfaceMethod) NULL,85, G__get_linked_tagnum(&G__BottomBranchDictLN_TClass), -1, 0, 0, 1, 1, 8, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("ShowMembers",1132,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TMemberInspector' - 1 - -", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Streamer",835,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - -", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("StreamerNVirtual",1656,G__BottomBranchDict_195_0_9, 121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - ClassDef_StreamerNVirtual_b", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("DeclFileName",1145,G__BottomBranchDict_195_0_10, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&analysis::bottom::HBTaggerBranch::DeclFileName) ), 0);
   G__memfunc_setup("ImplFileLine",1178,G__BottomBranchDict_195_0_11, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&analysis::bottom::HBTaggerBranch::ImplFileLine) ), 0);
   G__memfunc_setup("ImplFileName",1171,G__BottomBranchDict_195_0_12, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&analysis::bottom::HBTaggerBranch::ImplFileName) ), 0);
   G__memfunc_setup("DeclFileLine",1152,G__BottomBranchDict_195_0_13, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&analysis::bottom::HBTaggerBranch::DeclFileLine) ), 0);
   // automatic copy constructor
   G__memfunc_setup("HBTaggerBranch", 1330, G__BottomBranchDict_195_0_14, (int) ('i'), G__get_linked_tagnum(&G__BottomBranchDictLN_analysiscLcLbottomcLcLHBTaggerBranch), -1, 0, 1, 1, 1, 0, "u 'analysis::bottom::HBTaggerBranch' - 11 - -", (char*) NULL, (void*) NULL, 0);
   // automatic destructor
   G__memfunc_setup("~HBTaggerBranch", 1456, G__BottomBranchDict_195_0_15, (int) ('y'), -1, -1, 0, 0, 1, 1, 0, "", (char*) NULL, (void*) NULL, 0);
   // automatic assignment operator
   G__memfunc_setup("operator=", 937, G__BottomBranchDict_195_0_16, (int) ('u'), G__get_linked_tagnum(&G__BottomBranchDictLN_analysiscLcLbottomcLcLHBTaggerBranch), -1, 1, 1, 1, 1, 0, "u 'analysis::bottom::HBTaggerBranch' - 11 - -", (char*) NULL, (void*) NULL, 0);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncBottomBranchDict() {
}

/*********************************************************
* Global variable information setup for each class
*********************************************************/
static void G__cpp_setup_global0() {

   /* Setting up global variables */
   G__resetplocal();

}

static void G__cpp_setup_global1() {

   G__resetglobalenv();
}
extern "C" void G__cpp_setup_globalBottomBranchDict() {
  G__cpp_setup_global0();
  G__cpp_setup_global1();
}

/*********************************************************
* Global function information setup for each class
*********************************************************/
static void G__cpp_setup_func0() {
   G__lastifuncposition();

}

static void G__cpp_setup_func1() {
}

static void G__cpp_setup_func2() {
}

static void G__cpp_setup_func3() {
}

static void G__cpp_setup_func4() {
}

static void G__cpp_setup_func5() {
}

static void G__cpp_setup_func6() {
}

static void G__cpp_setup_func7() {
}

static void G__cpp_setup_func8() {
}

static void G__cpp_setup_func9() {
}

static void G__cpp_setup_func10() {
}

static void G__cpp_setup_func11() {
}

static void G__cpp_setup_func12() {
}

static void G__cpp_setup_func13() {

   G__resetifuncposition();
}

extern "C" void G__cpp_setup_funcBottomBranchDict() {
  G__cpp_setup_func0();
  G__cpp_setup_func1();
  G__cpp_setup_func2();
  G__cpp_setup_func3();
  G__cpp_setup_func4();
  G__cpp_setup_func5();
  G__cpp_setup_func6();
  G__cpp_setup_func7();
  G__cpp_setup_func8();
  G__cpp_setup_func9();
  G__cpp_setup_func10();
  G__cpp_setup_func11();
  G__cpp_setup_func12();
  G__cpp_setup_func13();
}

/*********************************************************
* Class,struct,union,enum tag information setup
*********************************************************/
/* Setup class/struct taginfo */
G__linked_taginfo G__BottomBranchDictLN_TClass = { "TClass" , 99 , -1 };
G__linked_taginfo G__BottomBranchDictLN_TBuffer = { "TBuffer" , 99 , -1 };
G__linked_taginfo G__BottomBranchDictLN_TMemberInspector = { "TMemberInspector" , 99 , -1 };
G__linked_taginfo G__BottomBranchDictLN_TObject = { "TObject" , 99 , -1 };
G__linked_taginfo G__BottomBranchDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR = { "vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >" , 99 , -1 };
G__linked_taginfo G__BottomBranchDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR = { "reverse_iterator<vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >::iterator>" , 99 , -1 };
G__linked_taginfo G__BottomBranchDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR = { "vector<TVirtualArray*,allocator<TVirtualArray*> >" , 99 , -1 };
G__linked_taginfo G__BottomBranchDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<TVirtualArray*,allocator<TVirtualArray*> >::iterator>" , 99 , -1 };
G__linked_taginfo G__BottomBranchDictLN_analysis = { "analysis" , 110 , -1 };
G__linked_taginfo G__BottomBranchDictLN_pairlEfloataNcOstringgR = { "pair<float&,string>" , 115 , -1 };
G__linked_taginfo G__BottomBranchDictLN_vectorlEpairlEfloataNcOstringgRcOallocatorlEpairlEfloataNcOstringgRsPgRsPgR = { "vector<pair<float&,string>,allocator<pair<float&,string> > >" , 99 , -1 };
G__linked_taginfo G__BottomBranchDictLN_reverse_iteratorlEvectorlEpairlEfloataNcOstringgRcOallocatorlEpairlEfloataNcOstringgRsPgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<pair<float&,string>,allocator<pair<float&,string> > >::iterator>" , 99 , -1 };
G__linked_taginfo G__BottomBranchDictLN_analysiscLcLBranch = { "analysis::Branch" , 99 , -1 };
G__linked_taginfo G__BottomBranchDictLN_analysiscLcLbottom = { "analysis::bottom" , 110 , -1 };
G__linked_taginfo G__BottomBranchDictLN_analysiscLcLbottomcLcLHBTaggerBranch = { "analysis::bottom::HBTaggerBranch" , 99 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtableBottomBranchDict() {
  G__BottomBranchDictLN_TClass.tagnum = -1 ;
  G__BottomBranchDictLN_TBuffer.tagnum = -1 ;
  G__BottomBranchDictLN_TMemberInspector.tagnum = -1 ;
  G__BottomBranchDictLN_TObject.tagnum = -1 ;
  G__BottomBranchDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR.tagnum = -1 ;
  G__BottomBranchDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__BottomBranchDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR.tagnum = -1 ;
  G__BottomBranchDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__BottomBranchDictLN_analysis.tagnum = -1 ;
  G__BottomBranchDictLN_pairlEfloataNcOstringgR.tagnum = -1 ;
  G__BottomBranchDictLN_vectorlEpairlEfloataNcOstringgRcOallocatorlEpairlEfloataNcOstringgRsPgRsPgR.tagnum = -1 ;
  G__BottomBranchDictLN_reverse_iteratorlEvectorlEpairlEfloataNcOstringgRcOallocatorlEpairlEfloataNcOstringgRsPgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__BottomBranchDictLN_analysiscLcLBranch.tagnum = -1 ;
  G__BottomBranchDictLN_analysiscLcLbottom.tagnum = -1 ;
  G__BottomBranchDictLN_analysiscLcLbottomcLcLHBTaggerBranch.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtableBottomBranchDict() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum_fwd(&G__BottomBranchDictLN_TClass);
   G__get_linked_tagnum_fwd(&G__BottomBranchDictLN_TBuffer);
   G__get_linked_tagnum_fwd(&G__BottomBranchDictLN_TMemberInspector);
   G__get_linked_tagnum_fwd(&G__BottomBranchDictLN_TObject);
   G__get_linked_tagnum_fwd(&G__BottomBranchDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR);
   G__get_linked_tagnum_fwd(&G__BottomBranchDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__BottomBranchDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR);
   G__get_linked_tagnum_fwd(&G__BottomBranchDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR);
   G__tagtable_setup(G__get_linked_tagnum_fwd(&G__BottomBranchDictLN_analysis),0,-1,262144,(char*)NULL,G__setup_memvaranalysis,G__setup_memfuncanalysis);
   G__get_linked_tagnum_fwd(&G__BottomBranchDictLN_pairlEfloataNcOstringgR);
   G__get_linked_tagnum_fwd(&G__BottomBranchDictLN_vectorlEpairlEfloataNcOstringgRcOallocatorlEpairlEfloataNcOstringgRsPgRsPgR);
   G__get_linked_tagnum_fwd(&G__BottomBranchDictLN_reverse_iteratorlEvectorlEpairlEfloataNcOstringgRcOallocatorlEpairlEfloataNcOstringgRsPgRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__BottomBranchDictLN_analysiscLcLBranch);
   G__tagtable_setup(G__get_linked_tagnum_fwd(&G__BottomBranchDictLN_analysiscLcLbottom),0,-1,262144,(char*)NULL,G__setup_memvaranalysiscLcLbottom,G__setup_memfuncanalysiscLcLbottom);
   G__tagtable_setup(G__get_linked_tagnum_fwd(&G__BottomBranchDictLN_analysiscLcLbottomcLcLHBTaggerBranch),sizeof(analysis::bottom::HBTaggerBranch),-1,291072,(char*)NULL,G__setup_memvaranalysiscLcLbottomcLcLHBTaggerBranch,G__setup_memfuncanalysiscLcLbottomcLcLHBTaggerBranch);
}
extern "C" void G__cpp_setupBottomBranchDict(void) {
  G__check_setup_version(30051515,"G__cpp_setupBottomBranchDict()");
  G__set_cpp_environmentBottomBranchDict();
  G__cpp_setup_tagtableBottomBranchDict();

  G__cpp_setup_inheritanceBottomBranchDict();

  G__cpp_setup_typetableBottomBranchDict();

  G__cpp_setup_memvarBottomBranchDict();

  G__cpp_setup_memfuncBottomBranchDict();
  G__cpp_setup_globalBottomBranchDict();
  G__cpp_setup_funcBottomBranchDict();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncBottomBranchDict();
  return;
}
class G__cpp_setup_initBottomBranchDict {
  public:
    G__cpp_setup_initBottomBranchDict() { G__add_setup_func("BottomBranchDict",(G__incsetup)(&G__cpp_setupBottomBranchDict)); G__call_setup_funcs(); }
   ~G__cpp_setup_initBottomBranchDict() { G__remove_setup_func("BottomBranchDict"); }
};
G__cpp_setup_initBottomBranchDict G__cpp_setup_initializerBottomBranchDict;
