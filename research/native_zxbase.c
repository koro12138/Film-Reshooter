/* Image base: 00100000 */

/* 0010a4e0 __on_dlclose */

void __on_dlclose(void)

{
  __cxa_finalize(&__dso_handle);
  return;
}



/* 0010a4f0 __emutls_unregister_key */

void __emutls_unregister_key(void)

{
  return;
}



/* 0010a4f8 __on_dlclose_late */

void __on_dlclose_late(void)

{
  __emutls_unregister_key();
  return;
}



/* 0010a500 __atexit_handler_wrapper */

void __atexit_handler_wrapper(code *UNRECOVERED_JUMPTABLE)

{
  if (UNRECOVERED_JUMPTABLE != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0010a50c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE)();
    return;
  }
  return;
}



/* 0010a514 atexit */

int atexit(__func *__func)

{
  int iVar1;
  
  iVar1 = __cxa_atexit(__atexit_handler_wrapper,__func,&__dso_handle);
  return iVar1;
}



/* 0010a530 pthread_atfork */

int pthread_atfork(__prepare *__prepare,__parent *__parent,__child *__child)

{
  int iVar1;
  
  iVar1 = __register_atfork((int)__prepare,__parent,__child,&__dso_handle);
  return iVar1;
}



/* 0010a540 Java_com_codex_lmoments_LegendaryPostProcessor_applyLut */

uint Java_com_codex_lmoments_LegendaryPostProcessor_applyLut
               (long *param_1,undefined8 param_2,_JNIEnv *param_3,long param_4,uint param_5)

{
  uint uVar1;
  _jobject *p_Var2;
  
  uVar1 = 0;
  if ((param_3 != (_JNIEnv *)0x0) && (param_4 != 0)) {
    uVar1 = param_5;
    p_Var2 = (_jobject *)(**(code **)(*param_1 + 0x548))(param_1,param_4,0);
    uVar1 = (anonymous_namespace)::applyLut
                      ((_anonymous_namespace_ *)param_1,param_3,p_Var2,(char *)(ulong)param_5,uVar1,
                       -1.0,5000.0);
    if (p_Var2 != (_jobject *)0x0) {
      (**(code **)(*param_1 + 0x550))(param_1,param_4,p_Var2);
    }
    uVar1 = uVar1 & 1;
  }
  return uVar1;
}



/* 0010a5e8 applyLut */

/* (anonymous namespace)::applyLut(_JNIEnv*, _jobject*, char const*, int, float, float) */

bool __thiscall
(anonymous_namespace)::applyLut
          (_anonymous_namespace_ *this,_JNIEnv *param_1,_jobject *param_2,char *param_3,int param_4,
          float param_5,float param_6)

{
  void *pvVar1;
  byte bVar2;
  int iVar3;
  ulong extraout_x1;
  ulong uVar4;
  int iVar5;
  ulong uVar6;
  int iVar7;
  bool bVar8;
  ulong uVar9;
  byte *pbVar10;
  float fVar11;
  float in_s2;
  void *local_1f0;
  void *local_1e8;
  undefined8 uStack_1e0;
  void *local_1d8;
  void *local_1d0;
  undefined8 local_1c8;
  undefined8 local_1c0;
  undefined8 local_1b8;
  undefined4 local_1b0 [4];
  int aiStack_1a0 [2];
  undefined8 auStack_198 [18];
  basic_ios<char,std::__ndk1::char_traits<char>> abStack_108 [152];
  
  local_1d8 = (void *)0x0;
  local_1d0 = (void *)0x0;
  local_1c8 = 0;
  if (0.0 <= param_5) {
                    /* try { // try from 0010a66c to 0010a687 has its CatchHandler @ 0010a978 */
    std::__ndk1::basic_ifstream<char,std::__ndk1::char_traits<char>>::basic_ifstream
              ((char *)&local_1c0,(uint)param_2);
    local_1e8 = (void *)0x0;
    uStack_1e0 = 0;
    local_1f0 = (void *)0x0;
                    /* try { // try from 0010a6a0 to 0010a6ab has its CatchHandler @ 0010a968 */
    std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>::
    __init_with_sentinel_abi_ne180000_<std::__ndk1::istreambuf_iterator<char,std::__ndk1::char_traits<char>>,std::__ndk1::istreambuf_iterator<char,std::__ndk1::char_traits<char>>>
              ((vector<unsigned_char,std::__ndk1::allocator<unsigned_char>> *)&local_1f0,
               (istreambuf_iterator)*(undefined8 *)((long)auStack_198 + *(long *)(local_1c0 - 0x18))
               ,0);
                    /* try { // try from 0010a6ac to 0010a6bf has its CatchHandler @ 0010a94c */
    bVar2 = adaptiveLut((vector *)&local_1f0,param_5,param_6,(vector *)&local_1d8);
    if (local_1f0 != (void *)0x0) {
      local_1e8 = local_1f0;
      operator_delete(local_1f0);
    }
  }
  else {
    bVar8 = false;
    if ((param_2 == (_jobject *)0x0) || ((int)param_3 < 0)) goto LAB_0010a80c;
                    /* try { // try from 0010a634 to 0010a647 has its CatchHandler @ 0010a944 */
    std::__ndk1::basic_ifstream<char,std::__ndk1::char_traits<char>>::basic_ifstream
              ((char *)&local_1c0,(uint)param_2);
    if ((*(byte *)((long)aiStack_1a0 + *(long *)(local_1c0 - 0x18)) & 5) == 0) {
                    /* try { // try from 0010a844 to 0010a84b has its CatchHandler @ 0010a934 */
      std::__ndk1::basic_istream<char,std::__ndk1::char_traits<char>>::tellg();
      bVar2 = 0;
      if ((-1 < (long)extraout_x1) &&
         (bVar2 = 0, ((ulong)param_3 & 0xffffffff) * 0x3993 + 0x4993 <= extraout_x1)) {
                    /* try { // try from 0010a86c to 0010a89f has its CatchHandler @ 0010a938 */
        std::__ndk1::basic_istream<char,std::__ndk1::char_traits<char>>::seekg
                  ((longlong)&local_1c0,(int)param_3 * 0x3993 + 0x1000);
        uVar6 = (long)local_1d0 - (long)local_1d8;
        if (uVar6 < 0x3993) {
          std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>::__append
                    ((vector<unsigned_char,std::__ndk1::allocator<unsigned_char>> *)&local_1d8,
                     0x3993 - uVar6);
        }
        else if (uVar6 != 0x3993) {
          local_1d0 = (void *)((long)local_1d8 + 0x3993);
        }
                    /* try { // try from 0010a8f4 to 0010a8ff has its CatchHandler @ 0010a938 */
        std::__ndk1::basic_istream<char,std::__ndk1::char_traits<char>>::read
                  ((char *)&local_1c0,(long)local_1d8);
        if (*(int *)((long)aiStack_1a0 + *(long *)(local_1c0 - 0x18)) == 0) {
          bVar2 = 1;
        }
        else {
          bVar2 = local_1b8 == (long)local_1d0 - (long)local_1d8;
        }
      }
    }
    else {
      bVar2 = 0;
    }
  }
  local_1c0 = *(ulong *)PTR_VTT_00120dc0;
  *(undefined8 *)((long)&local_1c0 + *(long *)(local_1c0 - 0x18)) =
       *(undefined8 *)(PTR_VTT_00120dc0 + 0x18);
  std::__ndk1::basic_filebuf<char,std::__ndk1::char_traits<char>>::~basic_filebuf
            ((basic_filebuf<char,std::__ndk1::char_traits<char>> *)local_1b0);
  std::__ndk1::basic_istream<char,std::__ndk1::char_traits<char>>::~basic_istream
            ((basic_istream<char,std::__ndk1::char_traits<char>> *)&local_1c0);
  std::__ndk1::basic_ios<char,std::__ndk1::char_traits<char>>::~basic_ios(abStack_108);
  if ((bVar2 & 1) == 0) {
    bVar8 = false;
  }
  else {
    local_1c0 = 0;
    local_1b8 = 0;
    local_1b0[0] = 0;
                    /* try { // try from 0010a71c to 0010a72b has its CatchHandler @ 0010a948 */
    iVar3 = AndroidBitmap_getInfo(this,param_1,&local_1c0);
    bVar8 = false;
    if ((iVar3 == 0) && (local_1b8._4_4_ == 1)) {
      local_1f0 = (void *)0x0;
                    /* try { // try from 0010a744 to 0010a753 has its CatchHandler @ 0010a940 */
      iVar3 = AndroidBitmap_lockPixels(this,param_1,&local_1f0);
      pvVar1 = local_1f0;
      bVar8 = iVar3 == 0 && local_1f0 != (void *)0x0;
      if (iVar3 == 0 && local_1f0 != (void *)0x0) {
        uVar6 = (ulong)local_1c0._4_4_;
        if (local_1c0._4_4_ != 0) {
          uVar4 = local_1c0 & 0xffffffff;
          uVar9 = 0;
          do {
            if ((int)uVar4 != 0) {
              uVar6 = 0;
              pbVar10 = (byte *)((long)pvVar1 + uVar9 * (local_1b8 & 0xffffffff) + 2);
              do {
                fVar11 = (float)sampleLut((vector *)&local_1d8,(uint)pbVar10[-2],(uint)pbVar10[-1],
                                          (uint)*pbVar10);
                uVar6 = uVar6 + 1;
                iVar3 = (int)(long)fVar11;
                if (0xfe < (int)(long)fVar11) {
                  iVar3 = 0xff;
                }
                iVar5 = (int)(long)param_6;
                if (0xfe < iVar5) {
                  iVar5 = 0xff;
                }
                iVar7 = (int)(long)in_s2;
                if (0xfe < iVar7) {
                  iVar7 = 0xff;
                }
                pbVar10[-2] = (byte)iVar3 & ((byte)(iVar3 >> 0x1f) ^ 0xff);
                pbVar10[-1] = (byte)iVar5 & ((byte)(iVar5 >> 0x1f) ^ 0xff);
                *pbVar10 = (byte)iVar7 & ((byte)(iVar7 >> 0x1f) ^ 0xff);
                uVar4 = local_1c0 & 0xffffffff;
                pbVar10 = pbVar10 + 4;
              } while (uVar6 < uVar4);
              uVar6 = local_1c0 >> 0x20;
            }
            uVar9 = uVar9 + 1;
          } while (uVar9 < uVar6);
        }
                    /* try { // try from 0010a8a8 to 0010a8d3 has its CatchHandler @ 0010a93c */
        AndroidBitmap_unlockPixels(this,param_1);
        __android_log_print(4,"LeicaNative","LUT applied block=%d size=%ux%u",
                            (ulong)param_3 & 0xffffffff,local_1c0 & 0xffffffff,local_1c0._4_4_);
      }
    }
  }
LAB_0010a80c:
  if (local_1d8 != (void *)0x0) {
    local_1d0 = local_1d8;
    operator_delete(local_1d8);
  }
  return bVar8;
}



/* 0010a994 Java_com_codex_lmoments_LegendaryPostProcessor_applyMonochrome */

uint Java_com_codex_lmoments_LegendaryPostProcessor_applyMonochrome
               (long *param_1,undefined8 param_2,_jobject *param_3,long param_4,long param_5)

{
  uint uVar1;
  char *pcVar2;
  char *pcVar3;
  
  uVar1 = 0;
  if (((param_3 != (_jobject *)0x0) && (param_4 != 0)) && (param_5 != 0)) {
    pcVar2 = (char *)(**(code **)(*param_1 + 0x548))(param_1,param_4,0);
    pcVar3 = (char *)(**(code **)(*param_1 + 0x548))(param_1,param_5,0);
    uVar1 = (anonymous_namespace)::applyAlgorithm
                      ((_JNIEnv *)param_1,param_3,pcVar2,pcVar3,(char *)0x0,0,200,5000);
    if (pcVar2 != (char *)0x0) {
      (**(code **)(*param_1 + 0x550))(param_1,param_4,pcVar2);
    }
    if (pcVar3 != (char *)0x0) {
      (**(code **)(*param_1 + 0x550))(param_1,param_5,pcVar3);
    }
    uVar1 = uVar1 & 1;
  }
  return uVar1;
}



/* 0010aa78 applyAlgorithm */

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* (anonymous namespace)::applyAlgorithm(_JNIEnv*, _jobject*, char const*, char const*, char const*,
   int, int, int) */

bool (anonymous_namespace)::applyAlgorithm
               (_JNIEnv *param_1,_jobject *param_2,char *param_3,char *param_4,char *param_5,
               int param_6,int param_7,int param_8)

{
  long *plVar1;
  undefined *puVar2;
  long lVar3;
  long lVar4;
  undefined (*pauVar5) [16];
  undefined (*pauVar6) [16];
  byte *pbVar7;
  byte *pbVar8;
  char *pcVar9;
  ulong uVar10;
  char **__argv;
  byte bVar11;
  undefined (*pauVar12) [16];
  undefined (*pauVar13) [16];
  uint7 uVar14;
  uint7 uVar15;
  uint6 uVar16;
  uint6 uVar17;
  undefined auVar18 [16];
  undefined auVar19 [16];
  undefined auVar20 [16];
  undefined auVar21 [16];
  undefined auVar22 [16];
  undefined auVar23 [16];
  undefined auVar24 [16];
  undefined auVar25 [16];
  undefined auVar26 [16];
  undefined auVar27 [16];
  undefined auVar28 [16];
  bool bVar29;
  undefined *puVar30;
  byte *pbVar31;
  char cVar32;
  int iVar33;
  int iVar34;
  uint uVar35;
  __pid_t _Var36;
  void *__s;
  void *__s_00;
  size_t sVar37;
  undefined (*pauVar38) [16];
  long lVar39;
  int *piVar40;
  undefined8 uVar41;
  ulong uVar42;
  ulong extraout_x1;
  long lVar43;
  ulong uVar44;
  byte *pbVar45;
  ulong uVar46;
  char *__name;
  ulong uVar47;
  ulong uVar48;
  long lVar49;
  ulong uVar50;
  ulong uVar51;
  ulong uVar52;
  ulong uVar53;
  void *pvVar54;
  ulong uVar55;
  char *__name_00;
  uint uVar56;
  uint uVar58;
  uint uVar59;
  undefined auVar57 [16];
  uint uVar60;
  uint uVar61;
  uint uVar64;
  uint uVar65;
  undefined auVar62 [16];
  undefined auVar63 [16];
  uint uVar66;
  uint uVar67;
  uint uVar69;
  uint uVar70;
  undefined auVar68 [16];
  uint uVar71;
  uint uVar72;
  uint uVar76;
  undefined8 uVar73;
  uint uVar77;
  undefined auVar74 [16];
  undefined auVar75 [16];
  uint uVar78;
  uint uVar79;
  uint uVar81;
  uint uVar82;
  undefined auVar80 [16];
  uint uVar83;
  uint uVar84;
  uint uVar86;
  uint uVar87;
  undefined auVar85 [16];
  uint uVar88;
  undefined auVar89 [16];
  uint uVar90;
  uint uVar93;
  uint uVar94;
  undefined auVar91 [16];
  undefined auVar92 [16];
  uint uVar95;
  undefined4 uVar96;
  undefined auVar97 [16];
  undefined4 uVar98;
  uint uVar99;
  uint uVar100;
  uint uVar101;
  uint uVar102;
  uint uVar103;
  uint uVar106;
  uint uVar107;
  uint uVar108;
  undefined auVar104 [16];
  undefined auVar105 [16];
  uint uVar109;
  uint uVar112;
  uint uVar113;
  uint uVar114;
  undefined auVar110 [16];
  undefined auVar111 [16];
  uint uVar115;
  uint uVar117;
  uint uVar118;
  uint uVar119;
  undefined auVar116 [16];
  uint uVar120;
  uint uVar123;
  uint uVar124;
  uint uVar125;
  undefined auVar121 [16];
  undefined auVar122 [16];
  undefined auVar126 [16];
  undefined auVar127 [16];
  undefined auVar128 [16];
  undefined auVar129 [16];
  undefined auVar130 [16];
  undefined auVar131 [16];
  undefined auVar132 [16];
  undefined auVar133 [16];
  undefined auVar134 [16];
  undefined auVar135 [16];
  undefined auVar136 [16];
  undefined auVar137 [16];
  undefined auVar138 [16];
  undefined auVar139 [16];
  undefined auVar140 [16];
  undefined auVar141 [16];
  undefined auVar142 [16];
  undefined auVar143 [16];
  undefined auVar144 [16];
  undefined auVar145 [16];
  int iVar149;
  int iVar150;
  undefined auVar146 [16];
  undefined auVar147 [16];
  undefined auVar148 [16];
  undefined auVar151 [16];
  int iVar152;
  undefined auVar153 [16];
  void *local_5d0;
  int iStack_548;
  int iStack_544;
  undefined local_540 [168];
  undefined8 uStack_498;
  short local_490;
  short sStack_48e;
  short sStack_48c;
  short sStack_48a;
  undefined8 uStack_458;
  undefined8 local_3d0;
  size_t local_3c8;
  void *local_3c0;
  uint auStack_3b0 [36];
  basic_ios<char,std::__ndk1::char_traits<char>> abStack_320 [164];
  __pid_t local_27c;
  char *local_278;
  undefined8 local_270;
  char *local_268;
  void *local_260;
  char *local_258;
  char *local_250;
  char *local_248;
  void *local_240;
  void *local_238;
  void *local_230;
  void *local_228;
  void *local_220;
  undefined8 local_218;
  byte local_210 [16];
  void *local_200;
  byte local_1f8 [16];
  void *local_1e8;
  byte local_1e0 [16];
  void *local_1d0;
  char *local_1c8;
  void *local_1c0;
  char *local_1b8;
  char *local_1b0;
  void *local_1a8;
  void *local_1a0;
  undefined8 local_198;
  byte local_190 [16];
  char *local_180;
  byte local_178 [16];
  void *local_168;
  byte local_160 [16];
  void *local_150;
  __ndk1 local_148 [16];
  void *local_138;
  byte local_130 [16];
  void *local_120;
  long local_118;
  ulong *local_110;
  ulong *puStack_108;
  ulong local_100;
  undefined8 uStack_f8;
  char *local_f0;
  ulong local_e0;
  undefined8 uStack_d8;
  char *local_d0;
  undefined8 local_c0;
  undefined8 local_b8;
  undefined4 local_b0;
  
  if (param_3 == (char *)0x0) {
    return false;
  }
  if (param_4 == (char *)0x0) {
    return false;
  }
  local_c0 = 0;
  local_b8 = 0;
  local_b0 = 0;
  iVar33 = AndroidBitmap_getInfo(param_1,param_2,&local_c0);
  if (iVar33 != 0) {
    return false;
  }
  if (local_b8._4_4_ != 1) {
    return false;
  }
  if ((uint)local_c0 == 0) {
    return false;
  }
  if (local_c0._4_4_ == 0) {
    return false;
  }
  if ((local_c0 & 1) != 0) {
    return false;
  }
  if ((local_c0 & 0x100000000) != 0) {
    return false;
  }
  uVar53 = (ulong)local_c0._4_4_ * (local_c0 & 0xffffffff);
  if (64000000 < uVar53) {
    return false;
  }
  uVar55 = uVar53 * 3 >> 1;
  __s = operator_new(uVar55);
  memset(__s,0x80,uVar55);
  uVar46 = uVar53;
  if (param_5 != (char *)0x0) {
    uVar46 = uVar55;
  }
                    /* try { // try from 0010ab64 to 0010ab6b has its CatchHandler @ 0010c0b8 */
  __s_00 = operator_new(uVar46);
  memset(__s_00,0,uVar46);
  sVar37 = strlen(param_4);
  if (0xffffffffffffffef < sVar37) {
                    /* try { // try from 0010bedc to 0010bee3 has its CatchHandler @ 0010c0cc */
    std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>::
    __throw_length_error_abi_ne180000_();
    goto LAB_0010bee4;
  }
  if (sVar37 < 0x17) {
    pvVar54 = (void *)((ulong)&local_3d0 | 1);
    local_3d0 = CONCAT71(local_3d0._1_7_,(char)((int)sVar37 << 1));
    if (sVar37 != 0) goto LAB_0010abd8;
  }
  else {
    uVar55 = (sVar37 | 0xf) + 1;
                    /* try { // try from 0010abbc to 0010abc3 has its CatchHandler @ 0010c0cc */
    pvVar54 = operator_new(uVar55);
    local_3d0 = uVar55 | 1;
    local_3c8 = sVar37;
    local_3c0 = pvVar54;
LAB_0010abd8:
    memcpy(pvVar54,param_4,sVar37);
  }
  *(undefined *)((long)pvVar54 + sVar37) = 0;
                    /* try { // try from 0010abec to 0010abfb has its CatchHandler @ 0010c0a0 */
  pauVar38 = (undefined (*) [16])
             std::__ndk1::
             basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>::append
                       ((char *)&local_3d0);
  local_d0 = *(char **)pauVar38[1];
  uStack_d8 = SUB168(*pauVar38,8);
  local_e0 = SUB168(*pauVar38,0);
  *(undefined8 *)(*pauVar38 + 8) = 0;
  *(undefined8 *)pauVar38[1] = 0;
  *(undefined8 *)*pauVar38 = 0;
  if ((local_3d0 & 1) != 0) {
    operator_delete(local_3c0);
  }
  sVar37 = strlen(param_4);
  if (0xffffffffffffffef < sVar37) {
LAB_0010bee4:
                    /* try { // try from 0010bee4 to 0010beeb has its CatchHandler @ 0010c0c0 */
    uVar41 = std::__ndk1::
             basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>::
             __throw_length_error_abi_ne180000_();
                    /* catch() { ... } // from try @ 0010bcf8 with catch @ 0010beec */
                    /* catch() { ... } // from try @ 0010bce0 with catch @ 0010bef0 */
    std::__ndk1::basic_ifstream<char,std::__ndk1::char_traits<char>>::~basic_ifstream
              ((basic_ifstream<char,std::__ndk1::char_traits<char>> *)&local_3d0);
    if ((local_210[0] & 1) != 0) {
      operator_delete(local_200);
    }
    if ((local_1f8[0] & 1) != 0) {
      operator_delete(local_1e8);
    }
    if ((local_1e0[0] & 1) != 0) {
      operator_delete(local_1d0);
    }
    if ((local_190[0] & 1) != 0) {
      operator_delete(local_180);
    }
    if ((local_178[0] & 1) != 0) {
      operator_delete(local_168);
    }
    if ((local_160[0] & 1) != 0) {
      operator_delete(local_150);
    }
    if (((byte)local_148[0] & 1) != 0) {
      operator_delete(local_138);
    }
    if ((local_130[0] & 1) != 0) {
      operator_delete(local_120);
    }
    if (((byte)local_100 & 1) != 0) {
      operator_delete(local_f0);
    }
    if ((local_e0 & 1) != 0) {
      operator_delete(local_d0);
    }
    operator_delete(local_5d0);
    operator_delete(__s);
                    /* WARNING: Subroutine does not return */
    _Unwind_Resume(uVar41);
  }
  if (sVar37 < 0x17) {
    pvVar54 = (void *)((ulong)&local_3d0 | 1);
    local_3d0 = CONCAT71(local_3d0._1_7_,(char)((int)sVar37 << 1));
    if (sVar37 != 0) goto LAB_0010ac7c;
  }
  else {
    uVar55 = (sVar37 | 0xf) + 1;
                    /* try { // try from 0010ac60 to 0010ac67 has its CatchHandler @ 0010c0c0 */
    pvVar54 = operator_new(uVar55);
    local_3d0 = uVar55 | 1;
    local_3c8 = sVar37;
    local_3c0 = pvVar54;
LAB_0010ac7c:
    memcpy(pvVar54,param_4,sVar37);
  }
  *(undefined *)((long)pvVar54 + sVar37) = 0;
                    /* try { // try from 0010ac90 to 0010ac9f has its CatchHandler @ 0010c088 */
  pauVar38 = (undefined (*) [16])
             std::__ndk1::
             basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>::append
                       ((char *)&local_3d0);
  local_f0 = *(char **)pauVar38[1];
  uStack_f8 = SUB168(*pauVar38,8);
  local_100 = SUB168(*pauVar38,0);
  *(undefined8 *)(*pauVar38 + 8) = 0;
  *(undefined8 *)pauVar38[1] = 0;
  *(undefined8 *)*pauVar38 = 0;
  if ((local_3d0 & 1) != 0) {
    operator_delete(local_3c0);
  }
  __name = (char *)((ulong)&local_e0 | 1);
  pcVar9 = __name;
  if ((local_e0 & 1) != 0) {
    pcVar9 = local_d0;
  }
                    /* try { // try from 0010ace4 to 0010ace7 has its CatchHandler @ 0010c084 */
  iVar33 = mkstemp(pcVar9);
  __name_00 = (char *)((ulong)&local_100 | 1);
  pcVar9 = __name_00;
  if ((local_100 & 1) != 0) {
    pcVar9 = local_f0;
  }
                    /* try { // try from 0010ad04 to 0010ad23 has its CatchHandler @ 0010c0d8 */
  iVar34 = mkstemp(pcVar9);
  if (-1 < iVar33) {
    close(iVar33);
  }
  if (iVar34 < 0) {
LAB_0010ae18:
    if ((local_e0 & 1) != 0) {
      __name = local_d0;
    }
    unlink(__name);
    if ((local_100 & 1) != 0) {
      __name_00 = local_f0;
    }
    unlink(__name_00);
  }
  else {
    close(iVar34);
    local_110 = &local_e0;
    puStack_108 = &local_100;
    if (iVar33 < 0) goto LAB_0010ae18;
    local_118 = 0;
                    /* try { // try from 0010ad38 to 0010ad47 has its CatchHandler @ 0010bf94 */
    iVar33 = AndroidBitmap_lockPixels(param_1,param_2,&local_118);
    if ((iVar33 != 0) || (local_118 == 0)) goto LAB_0010ae18;
    if (local_c0._4_4_ != 0) {
      uVar35 = 0;
      uVar55 = 0;
      pbVar31 = (byte *)(local_118 + 2);
      do {
        uVar51 = local_c0 & 0xffffffff;
        pbVar45 = pbVar31;
        uVar56 = uVar35;
        if ((uint)local_c0 != 0) {
          do {
            if (param_5 == (char *)0x0) {
              cVar32 = (char)((uint)pbVar45[-1] * 0x81 + (uint)pbVar45[-2] * 0x42 +
                              (uint)*pbVar45 * 0x19 + 0x80 >> 8) + '\x10';
            }
            else {
              cVar32 = (char)((uint)pbVar45[-1] * 0x9646 + (uint)pbVar45[-2] * 0x4c8b +
                              (uint)*pbVar45 * 0x1d2f + 0x8000 >> 0x10);
            }
            uVar51 = uVar51 - 1;
            *(char *)((long)__s + (ulong)uVar56) = cVar32;
            uVar56 = uVar56 + 1;
            pbVar45 = pbVar45 + 4;
          } while (uVar51 != 0);
        }
        auVar28 = _DAT_00102f00;
        auVar27 = _DAT_00102ee0;
        auVar26 = _DAT_00102ed0;
        auVar25 = _DAT_00102ec0;
        auVar24 = _DAT_00102e80;
        auVar23 = _DAT_00102e70;
        auVar22 = _DAT_00102e50;
        auVar21 = _DAT_00102e40;
        auVar20 = _DAT_00102e30;
        auVar19 = _DAT_00102e20;
        auVar18 = _DAT_00102e10;
        uVar55 = uVar55 + 1;
        uVar35 = uVar35 + (uint)local_c0;
        pbVar31 = pbVar31 + (local_b8 & 0xffffffff);
      } while (uVar55 != local_c0._4_4_);
      if (param_5 != (char *)0x0) {
        uVar48 = local_c0 & 0xffffffff;
        uVar42 = uVar48 - 1;
        uVar55 = (uVar42 >> 1) + 1;
        uVar51 = 0x10;
        if ((uVar55 & 0xf) != 0) {
          uVar51 = uVar55 & 0xf;
        }
        lVar49 = uVar55 - uVar51;
        lVar39 = local_118 + (uVar42 * 4 | 7);
        uVar10 = 8;
        if ((uVar55 & 7) != 0) {
          uVar10 = uVar55 & 7;
        }
        iVar152 = -0x2b33;
        iVar34 = -0x2b33;
        uVar35 = 0;
        iVar33 = 0;
        uVar47 = 0;
        uVar41 = SUB168(_DAT_00102ea0,8);
        local_490 = SUB162(_DAT_00102ea0,0);
        sStack_48e = SUB162(_DAT_00102ea0,2);
        sStack_48c = SUB162(_DAT_00102ea0,4);
        sStack_48a = SUB162(_DAT_00102ea0,6);
        local_540._8_8_ = SUB168(_DAT_00102e90,8);
        local_540._0_8_ = 0xffffd4cdffffd4cd;
        auVar140 = _DAT_00102e90;
        do {
          if ((uint)local_c0 != 0) {
            puVar2 = (undefined *)((long)__s + uVar35 + uVar53);
            lVar3 = local_118 + (ulong)((int)local_b8 * ((uint)uVar47 | 1));
            lVar4 = local_118 + (ulong)((int)local_b8 * (uint)uVar47);
            if (uVar48 < 0x11 || uVar48 - 0x40000001 < 0xffffffffc0000000) {
              uVar50 = 0;
            }
            else {
              uVar56 = (int)local_b8 * 2 * iVar33;
              uVar52 = (long)__s + (uint)local_c0 * iVar33 + uVar53;
              uVar44 = (long)__s +
                       (ulong)((uint)local_c0 * iVar33) + (uVar42 & 0xfffffffffffffffe) + uVar53 + 2
              ;
              uVar50 = 0;
              if ((uVar44 <= local_118 + (ulong)((int)local_b8 + uVar56) ||
                   lVar39 + (ulong)((int)local_b8 + uVar56) <= uVar52) &&
                 (lVar39 + (ulong)uVar56 <= uVar52 || uVar44 <= local_118 + (ulong)uVar56)) {
                iVar149 = (int)uStack_458;
                iVar150 = (int)((ulong)uStack_458 >> 0x20);
                if ((uint)local_c0 < 0x21) {
                  lVar43 = 0;
                }
                else {
                  uVar50 = 0;
                  lVar43 = lVar49;
                  puVar30 = puVar2;
                  do {
                    pauVar38 = (undefined (*) [16])(lVar4 + (uVar50 & 0xffffff80));
                    auVar57 = pauVar38[6];
                    auVar62 = pauVar38[7];
                    pauVar5 = (undefined (*) [16])(lVar3 + (uVar50 & 0xffffff80));
                    auVar63 = pauVar38[4];
                    auVar68 = pauVar38[5];
                    lVar43 = lVar43 + -0x10;
                    uVar50 = uVar50 + 0x80;
                    auVar80 = pauVar38[2];
                    auVar91 = pauVar38[3];
                    auVar92 = *pauVar38;
                    auVar74 = pauVar38[1];
                    auVar75 = a64_TBL(ZEXT816(0),auVar57,auVar62,auVar18);
                    a64_TBL(ZEXT816(0),auVar63,auVar68,auVar27);
                    a64_TBL(ZEXT816(0),auVar63,auVar68,auVar23);
                    auVar127 = a64_TBL(ZEXT816(0),auVar80,auVar91,auVar18);
                    auVar153 = a64_TBL(ZEXT816(0),auVar80,auVar91,auVar25);
                    auVar85 = a64_TBL(ZEXT816(0),auVar57,auVar62,auVar28);
                    auVar111 = a64_TBL(ZEXT816(0),auVar63,auVar68,auVar20);
                    auVar151 = a64_TBL(ZEXT816(0),auVar92,auVar74,auVar23);
                    auVar132 = a64_TBL(ZEXT816(0),auVar80,auVar91,auVar28);
                    auVar136 = a64_TBL(ZEXT816(0),auVar92,auVar74,auVar27);
                    auVar121 = a64_TBL(ZEXT816(0),auVar57,auVar62,auVar24);
                    pauVar12 = pauVar5 + 1;
                    uVar96 = (undefined4)((ulong)*(undefined8 *)(pauVar5[1] + 8) >> 0x20);
                    pauVar38 = pauVar5 + 6;
                    uVar98 = (undefined4)((ulong)*(undefined8 *)(pauVar5[6] + 8) >> 0x20);
                    pauVar13 = pauVar5 + 7;
                    auVar138 = a64_TBL(ZEXT816(0),auVar92,auVar74,auVar26);
                    auVar104 = pauVar5[2];
                    auVar105 = pauVar5[3];
                    auVar122 = a64_TBL(ZEXT816(0),auVar57,auVar62,auVar25);
                    auVar116 = a64_TBL(ZEXT816(0),auVar63,auVar68,auVar26);
                    auVar140._12_4_ = uVar96;
                    auVar140._0_12_ = *(undefined (*) [12])*pauVar12;
                    auVar128 = a64_TBL(ZEXT816(0),*pauVar5,auVar140,auVar23);
                    pauVar6 = pauVar5 + 4;
                    auVar140 = pauVar5[5];
                    auVar133 = a64_TBL(ZEXT816(0),auVar104,auVar105,auVar18);
                    local_490 = (ushort)auVar75[4] + (ushort)auVar85[4];
                    sStack_48e = (ushort)auVar75[5] + (ushort)auVar85[5];
                    sStack_48c = (ushort)auVar75[6] + (ushort)auVar85[6];
                    sStack_48a = (ushort)auVar75[7] + (ushort)auVar85[7];
                    auVar85._12_4_ = uVar98;
                    auVar85._0_12_ = *(undefined (*) [12])*pauVar38;
                    auVar145 = a64_TBL(ZEXT816(0),auVar85,*pauVar13,auVar18);
                    auVar126 = a64_TBL(ZEXT816(0),auVar80,auVar91,auVar24);
                    auVar85 = a64_TBL(ZEXT816(0),auVar92,auVar74,auVar20);
                    auVar134 = a64_TBL(ZEXT816(0),*pauVar6,auVar140,auVar26);
                    auVar139 = a64_TBL(ZEXT816(0),auVar92,auVar74,auVar21);
                    auVar110._2_2_ = sStack_48e;
                    auVar110._0_2_ = local_490;
                    auVar110._4_2_ = sStack_48c;
                    auVar110._6_2_ = sStack_48a;
                    auVar110._8_8_ = uVar41;
                    auVar142 = a64_TBL(ZEXT816(0),auVar80,auVar91,auVar19);
                    auVar137 = a64_TBL(ZEXT816(0),auVar80,auVar91,auVar110);
                    a64_TBL(ZEXT816(0),auVar57,auVar62,auVar19);
                    a64_TBL(ZEXT816(0),auVar57,auVar62,auVar110);
                    auVar131 = a64_TBL(ZEXT816(0),auVar92,auVar74,local_540._0_16_);
                    auVar89 = a64_TBL(ZEXT816(0),auVar63,auVar68,auVar21);
                    auVar141 = a64_TBL(ZEXT816(0),auVar63,auVar68,local_540._0_16_);
                    auVar130 = a64_TBL(ZEXT816(0),*pauVar6,auVar140,auVar23);
                    auVar91._12_4_ = uVar98;
                    auVar91._0_12_ = *(undefined (*) [12])*pauVar38;
                    auVar91 = a64_TBL(ZEXT816(0),auVar91,*pauVar13,auVar25);
                    auVar92._12_4_ = uVar98;
                    auVar92._0_12_ = *(undefined (*) [12])*pauVar38;
                    auVar143 = a64_TBL(ZEXT816(0),auVar92,*pauVar13,auVar110);
                    auVar146 = a64_TBL(ZEXT816(0),auVar104,auVar105,auVar25);
                    auVar148 = a64_TBL(ZEXT816(0),auVar104,auVar105,auVar110);
                    auVar57._12_4_ = uVar96;
                    auVar57._0_12_ = *(undefined (*) [12])*pauVar12;
                    auVar110 = a64_TBL(ZEXT816(0),*pauVar5,auVar57,local_540._0_16_);
                    auVar92 = a64_TBL(ZEXT816(0),*pauVar6,auVar140,local_540._0_16_);
                    auVar62._12_4_ = uVar96;
                    auVar62._0_12_ = *(undefined (*) [12])*pauVar12;
                    auVar129 = a64_TBL(ZEXT816(0),*pauVar5,auVar62,auVar26);
                    auVar63._12_4_ = uVar96;
                    auVar63._0_12_ = *(undefined (*) [12])*pauVar12;
                    auVar63 = a64_TBL(ZEXT816(0),*pauVar5,auVar63,auVar27);
                    auVar74._12_4_ = uVar98;
                    auVar74._0_12_ = *(undefined (*) [12])*pauVar38;
                    auVar135 = a64_TBL(ZEXT816(0),auVar74,*pauVar13,auVar24);
                    auVar144 = a64_TBL(ZEXT816(0),auVar104,auVar105,auVar24);
                    auVar57 = a64_TBL(ZEXT816(0),auVar104,auVar105,auVar28);
                    auVar75._12_4_ = uVar98;
                    auVar75._0_12_ = *(undefined (*) [12])*pauVar38;
                    auVar62 = a64_TBL(ZEXT816(0),auVar75,*pauVar13,auVar28);
                    auVar74 = a64_TBL(ZEXT816(0),*pauVar6,auVar140,auVar27);
                    auVar75 = a64_TBL(ZEXT816(0),*pauVar6,auVar140,auVar20);
                    auVar147 = a64_TBL(ZEXT816(0),*pauVar6,auVar140,auVar21);
                    auVar97._12_4_ = uVar98;
                    auVar97._0_12_ = *(undefined (*) [12])*pauVar38;
                    auVar140 = a64_TBL(ZEXT816(0),auVar97,*pauVar13,auVar19);
                    auVar97 = a64_TBL(ZEXT816(0),auVar104,auVar105,auVar19);
                    auVar68._12_4_ = uVar96;
                    auVar68._0_12_ = *(undefined (*) [12])*pauVar12;
                    auVar68 = a64_TBL(ZEXT816(0),*pauVar5,auVar68,auVar20);
                    auVar80._12_4_ = uVar96;
                    auVar80._0_12_ = *(undefined (*) [12])*pauVar12;
                    auVar80 = a64_TBL(ZEXT816(0),*pauVar5,auVar80,auVar21);
                    uVar72 = (uint)(ushort)((ushort)auVar127[4] + (ushort)auVar132[4]) +
                             (uint)auVar133[4] + (uint)auVar57[4] + 2 >> 2;
                    uVar76 = (uint)(ushort)((ushort)auVar127[5] + (ushort)auVar132[5]) +
                             (uint)auVar133[5] + (uint)auVar57[5] + 2 >> 2;
                    uVar77 = (uint)(ushort)((ushort)auVar127[6] + (ushort)auVar132[6]) +
                             (uint)auVar133[6] + (uint)auVar57[6] + 2 >> 2;
                    uVar78 = (uint)(ushort)((ushort)auVar127[7] + (ushort)auVar132[7]) +
                             (uint)auVar133[7] + (uint)auVar57[7] + 2 >> 2;
                    uVar84 = (uint)(ushort)uStack_498 + (uint)auVar145[4] + (uint)auVar62[4] + 2 >>
                             2;
                    uVar86 = (uint)(ushort)((ulong)uStack_498 >> 0x10) + (uint)auVar145[5] +
                             (uint)auVar62[5] + 2 >> 2;
                    uVar87 = (uint)(ushort)((ulong)uStack_498 >> 0x20) + (uint)auVar145[6] +
                             (uint)auVar62[6] + 2 >> 2;
                    uVar88 = (uint)(ushort)((ulong)uStack_498 >> 0x30) + (uint)auVar145[7] +
                             (uint)auVar62[7] + 2 >> 2;
                    uVar103 = (uint)(ushort)((ushort)auVar122[4] + (ushort)auVar121[4]) +
                              (uint)auVar91[4] + (uint)auVar135[4] + 2 >> 2;
                    uVar106 = (uint)(ushort)((ushort)auVar122[5] + (ushort)auVar121[5]) +
                              (uint)auVar91[5] + (uint)auVar135[5] + 2 >> 2;
                    uVar107 = (uint)(ushort)((ushort)auVar122[6] + (ushort)auVar121[6]) +
                              (uint)auVar91[6] + (uint)auVar135[6] + 2 >> 2;
                    uVar108 = (uint)(ushort)((ushort)auVar122[7] + (ushort)auVar121[7]) +
                              (uint)auVar91[7] + (uint)auVar135[7] + 2 >> 2;
                    uVar67 = (uint)(ushort)((ushort)auVar151[2] + (ushort)auVar136[2]) +
                             (uint)auVar128[2] +
                             (CONCAT12(auVar130[1],(ushort)auVar130[0]) & 0xffff) +
                             (CONCAT12(auVar74[1],(ushort)auVar74[0]) & 0xffff) + 2 >> 2;
                    uVar69 = (uint)auVar130[1] + (uint)auVar74[1] + 2 >> 2;
                    uVar70 = (uint)(ushort)((ushort)auVar151[3] + (ushort)auVar136[3]) +
                             (uint)auVar128[3] + (uint)auVar130[2] + (uint)auVar74[2] + 2 >> 2;
                    uVar71 = (uint)auVar130[3] + (uint)auVar74[3] + 2 >> 2;
                    uVar115 = (uint)(ushort)((ushort)auVar153[4] + (ushort)auVar126[4]) +
                              (uint)auVar146[4] + (uint)auVar144[4] + 2 >> 2;
                    uVar117 = (uint)(ushort)((ushort)auVar153[5] + (ushort)auVar126[5]) +
                              (uint)auVar146[5] + (uint)auVar144[5] + 2 >> 2;
                    uVar118 = (uint)(ushort)((ushort)auVar153[6] + (ushort)auVar126[6]) +
                              (uint)auVar146[6] + (uint)auVar144[6] + 2 >> 2;
                    uVar119 = (uint)(ushort)((ushort)auVar153[7] + (ushort)auVar126[7]) +
                              (uint)auVar146[7] + (uint)auVar144[7] + 2 >> 2;
                    uVar99 = (uint)(ushort)((ushort)auVar116[0] + (ushort)auVar111[0]) +
                             (CONCAT12(auVar134[1],(ushort)auVar134[0]) & 0xffff) +
                             (CONCAT12(auVar75[1],(ushort)auVar75[0]) & 0xffff) + 2 >> 2;
                    uVar100 = (uint)(ushort)((ushort)auVar116[1] + (ushort)auVar111[1]) +
                              (uint)auVar134[1] + (uint)auVar75[1] + 2 >> 2;
                    uVar101 = (uint)(ushort)((ushort)auVar116[2] + (ushort)auVar111[2]) +
                              (uint)auVar134[2] + (uint)auVar75[2] + 2 >> 2;
                    uVar102 = (uint)(ushort)((ushort)auVar116[3] + (ushort)auVar111[3]) +
                              (uint)auVar134[3] + (uint)auVar75[3] + 2 >> 2;
                    uVar90 = (uint)(ushort)((ushort)auVar138[0] + (ushort)auVar85[0]) +
                             (CONCAT12(auVar129[1],(ushort)auVar129[0]) & 0xffff) +
                             (CONCAT12(auVar68[1],(ushort)auVar68[0]) & 0xffff) + 2 >> 2;
                    uVar93 = (uint)(ushort)((ushort)auVar138[1] + (ushort)auVar85[1]) +
                             (uint)auVar129[1] + (uint)auVar68[1] + 2 >> 2;
                    uVar94 = (uint)(ushort)((ushort)auVar138[2] + (ushort)auVar85[2]) +
                             (uint)auVar129[2] + (uint)auVar68[2] + 2 >> 2;
                    uVar95 = (uint)(ushort)((ushort)auVar138[3] + (ushort)auVar85[3]) +
                             (uint)auVar129[3] + (uint)auVar68[3] + 2 >> 2;
                    uVar56 = (uint)(ushort)((ushort)auVar151[0] + (ushort)auVar136[0]) +
                             (CONCAT12(auVar128[1],(ushort)auVar128[0]) & 0xffff) +
                             (CONCAT12(auVar63[1],(ushort)auVar63[0]) & 0xffff) + 2 >> 2;
                    uVar58 = (uint)(ushort)((ushort)auVar151[1] + (ushort)auVar136[1] +
                                           (ushort)auVar128[1]) + (uint)auVar63[1] + 2 >> 2;
                    uVar59 = auVar121._8_4_ + (uint)auVar63[2] + 2 >> 2;
                    uVar60 = auVar121._12_4_ + (uint)auVar63[3] + 2 >> 2;
                    uVar61 = (uint)(ushort)((ushort)auVar131[0] + (ushort)auVar139[0]) +
                             (CONCAT12(auVar110[1],(ushort)auVar110[0]) & 0xffff) +
                             (CONCAT12(auVar80[1],(ushort)auVar80[0]) & 0xffff) + 2 >> 2;
                    uVar64 = (uint)(ushort)((ushort)auVar131[1] + (ushort)auVar139[1]) +
                             (uint)auVar110[1] + (uint)auVar80[1] + 2 >> 2;
                    uVar65 = (uint)(ushort)((ushort)auVar131[2] + (ushort)auVar139[2]) +
                             (uint)auVar110[2] + (uint)auVar80[2] + 2 >> 2;
                    uVar66 = (uint)(ushort)((ushort)auVar131[3] + (ushort)auVar139[3]) +
                             (uint)auVar110[3] + (uint)auVar80[3] + 2 >> 2;
                    uVar79 = (uint)auVar111._8_2_ + (uint)auVar143[4] + (uint)auVar140[4] + 2 >> 2;
                    uVar81 = (uint)auVar111._10_2_ + (uint)auVar143[5] + (uint)auVar140[5] + 2 >> 2;
                    uVar82 = (uint)auVar111._12_2_ + (uint)auVar143[6] + (uint)auVar140[6] + 2 >> 2;
                    uVar83 = (uint)auVar111._14_2_ + (uint)auVar143[7] + (uint)auVar140[7] + 2 >> 2;
                    uVar109 = (uint)(ushort)((ushort)auVar137[4] + (ushort)auVar142[4]) +
                              (uint)auVar148[4] + (uint)auVar97[4] + 2 >> 2;
                    uVar112 = (uint)(ushort)((ushort)auVar137[5] + (ushort)auVar142[5]) +
                              (uint)auVar148[5] + (uint)auVar97[5] + 2 >> 2;
                    uVar113 = (uint)(ushort)((ushort)auVar137[6] + (ushort)auVar142[6]) +
                              (uint)auVar148[6] + (uint)auVar97[6] + 2 >> 2;
                    uVar114 = (uint)(ushort)((ushort)auVar137[7] + (ushort)auVar142[7]) +
                              (uint)auVar148[7] + (uint)auVar97[7] + 2 >> 2;
                    uVar120 = (uint)(ushort)((ushort)auVar141[0] + (ushort)auVar89[0]) +
                              (CONCAT12(auVar92[1],(ushort)auVar92[0]) & 0xffff) +
                              (CONCAT12(auVar147[1],(ushort)auVar147[0]) & 0xffff) + 2 >> 2;
                    uVar123 = (uint)(ushort)((ushort)auVar141[1] + (ushort)auVar89[1]) +
                              (uint)auVar92[1] + (uint)auVar147[1] + 2 >> 2;
                    uVar124 = (uint)(ushort)((ushort)auVar141[2] + (ushort)auVar89[2]) +
                              (uint)auVar92[2] + (uint)auVar147[2] + 2 >> 2;
                    uVar125 = (uint)(ushort)((ushort)auVar141[3] + (ushort)auVar89[3]) +
                              (uint)auVar92[3] + (uint)auVar147[3] + 2 >> 2;
                    auVar131._8_4_ = 0x7f;
                    auVar131._0_8_ = 0x7f0000007f;
                    auVar131._12_4_ = 0x7f;
                    auVar130._0_4_ =
                         (int)(uVar72 * 0x8000 + uVar115 * -0x6b2f + uVar109 * -0x14d1 + 0x8000) >>
                         0x10;
                    auVar130._4_4_ =
                         (int)(uVar76 * 0x8000 + uVar117 * -0x6b2f + uVar112 * -0x14d1 + 0x8000) >>
                         0x10;
                    auVar130._8_4_ =
                         (int)(uVar77 * 0x8000 + uVar118 * -0x6b2f + uVar113 * iVar149 + 0x8000) >>
                         0x10;
                    auVar130._12_4_ =
                         (int)(uVar78 * 0x8000 + uVar119 * -0x6b2f + uVar114 * iVar150 + 0x8000) >>
                         0x10;
                    auVar122._0_4_ =
                         (int)(uVar103 * -0x54cd + uVar84 * -0x2b33 + uVar79 * 0x8000 + 0x8000) >>
                         0x10;
                    auVar122._4_4_ =
                         (int)(uVar106 * -0x54cd + uVar86 * -0x2b33 + uVar81 * 0x8000 + 0x8000) >>
                         0x10;
                    auVar122._8_4_ =
                         (int)(uVar107 * -0x54cd + uVar87 * iStack_548 + uVar82 * 0x8000 + 0x8000)
                         >> 0x10;
                    auVar122._12_4_ =
                         (int)(uVar108 * -0x54cd + uVar88 * iStack_544 + uVar83 * 0x8000 + 0x8000)
                         >> 0x10;
                    auVar105._0_4_ =
                         (int)(uVar115 * -0x54cd + uVar72 * -0x2b33 + uVar109 * 0x8000 + 0x8000) >>
                         0x10;
                    auVar105._4_4_ =
                         (int)(uVar117 * -0x54cd + uVar76 * -0x2b33 + uVar112 * 0x8000 + 0x8000) >>
                         0x10;
                    auVar105._8_4_ =
                         (int)(uVar118 * -0x54cd + uVar77 * iStack_548 + uVar113 * 0x8000 + 0x8000)
                         >> 0x10;
                    auVar105._12_4_ =
                         (int)(uVar119 * -0x54cd + uVar78 * iStack_544 + uVar114 * 0x8000 + 0x8000)
                         >> 0x10;
                    auVar121._0_4_ =
                         (int)(uVar84 * 0x8000 + uVar103 * -0x6b2f + uVar79 * -0x14d1 + 0x8000) >>
                         0x10;
                    auVar121._4_4_ =
                         (int)(uVar86 * 0x8000 + uVar106 * -0x6b2f + uVar81 * -0x14d1 + 0x8000) >>
                         0x10;
                    auVar121._8_4_ =
                         (int)(uVar87 * 0x8000 + uVar107 * -0x6b2f + uVar82 * iVar149 + 0x8000) >>
                         0x10;
                    auVar121._12_4_ =
                         (int)(uVar88 * 0x8000 + uVar108 * -0x6b2f + uVar83 * iVar150 + 0x8000) >>
                         0x10;
                    auVar116._0_4_ =
                         (int)(uVar99 * -0x54cd + uVar67 * -0x2b33 + uVar120 * 0x8000 + 0x8000) >>
                         0x10;
                    auVar116._4_4_ =
                         (int)(uVar100 * -0x54cd + uVar69 * -0x2b33 + uVar123 * 0x8000 + 0x8000) >>
                         0x10;
                    auVar116._8_4_ =
                         (int)(uVar101 * -0x54cd + uVar70 * iStack_548 + uVar124 * 0x8000 + 0x8000)
                         >> 0x10;
                    auVar116._12_4_ =
                         (int)(uVar102 * -0x54cd + uVar71 * iStack_544 + uVar125 * 0x8000 + 0x8000)
                         >> 0x10;
                    auVar104._0_4_ =
                         (int)(uVar90 * -0x54cd + uVar56 * -0x2b33 + uVar61 * 0x8000 + 0x8000) >>
                         0x10;
                    auVar104._4_4_ =
                         (int)(uVar93 * -0x54cd + uVar58 * -0x2b33 + uVar64 * 0x8000 + 0x8000) >>
                         0x10;
                    auVar104._8_4_ =
                         (int)(uVar94 * -0x54cd + uVar59 * iStack_548 + uVar65 * 0x8000 + 0x8000) >>
                         0x10;
                    auVar104._12_4_ =
                         (int)(uVar95 * -0x54cd + uVar60 * iStack_544 + uVar66 * 0x8000 + 0x8000) >>
                         0x10;
                    auVar63 = NEON_smin(auVar122,auVar131,4);
                    auVar126._0_4_ =
                         (int)(uVar67 * 0x8000 + uVar99 * -0x6b2f + uVar120 * -0x14d1 + 0x8000) >>
                         0x10;
                    auVar126._4_4_ =
                         (int)(uVar69 * 0x8000 + uVar100 * -0x6b2f + uVar123 * -0x14d1 + 0x8000) >>
                         0x10;
                    auVar126._8_4_ =
                         (int)(uVar70 * 0x8000 + uVar101 * -0x6b2f + uVar124 * iVar149 + 0x8000) >>
                         0x10;
                    auVar126._12_4_ =
                         (int)(uVar71 * 0x8000 + uVar102 * -0x6b2f + uVar125 * iVar150 + 0x8000) >>
                         0x10;
                    auVar57 = NEON_smin(auVar105,auVar131,4);
                    auVar111._0_4_ =
                         (int)(uVar56 * 0x8000 + uVar90 * -0x6b2f + uVar61 * -0x14d1 + 0x8000) >>
                         0x10;
                    auVar111._4_4_ =
                         (int)(uVar58 * 0x8000 + uVar93 * -0x6b2f + uVar64 * -0x14d1 + 0x8000) >>
                         0x10;
                    auVar111._8_4_ =
                         (int)(uVar59 * 0x8000 + uVar94 * -0x6b2f + uVar65 * iVar149 + 0x8000) >>
                         0x10;
                    auVar111._12_4_ =
                         (int)(uVar60 * 0x8000 + uVar95 * -0x6b2f + uVar66 * iVar150 + 0x8000) >>
                         0x10;
                    auVar91 = NEON_smin(auVar121,auVar131,4);
                    auVar62 = NEON_smin(auVar116,auVar131,4);
                    auVar80 = NEON_smin(auVar130,auVar131,4);
                    auVar140 = NEON_smin(auVar104,auVar131,4);
                    auVar85 = NEON_smin(auVar126,auVar131,4);
                    auVar68 = NEON_smin(auVar111,auVar131,4);
                    auVar57 = a64_TBL(ZEXT816(0),auVar140,auVar57,auVar62,auVar63,_DAT_00102ef0);
                    auVar140 = a64_TBL(ZEXT816(0),auVar68,auVar80,auVar85,auVar91,_DAT_00102ef0);
                    uVar17 = auVar57._0_6_ ^ 0x808080;
                    uVar16 = auVar57._0_6_ ^ 0x8080808080;
                    uVar15 = auVar140._0_7_ ^ 0x80808080;
                    uVar14 = auVar140._0_7_ ^ 0x808080808080;
                    *puVar30 = (char)uVar17;
                    puVar30[1] = (char)uVar15;
                    puVar30[2] = (char)(uVar17 >> 8);
                    puVar30[3] = (char)(uVar15 >> 8);
                    puVar30[4] = (char)(uVar17 >> 0x10);
                    puVar30[5] = (char)(uVar15 >> 0x10);
                    puVar30[6] = (char)(uVar16 >> 0x18);
                    puVar30[7] = (char)(uVar15 >> 0x18);
                    puVar30[8] = (char)(uVar16 >> 0x20);
                    puVar30[9] = (char)(uVar14 >> 0x20);
                    puVar30[10] = auVar57[5] ^ 0x80;
                    puVar30[0xb] = (char)(uVar14 >> 0x28);
                    puVar30[0xc] = auVar57[6] ^ 0x80;
                    puVar30[0xd] = auVar140[6] ^ 0x80;
                    puVar30[0xe] = auVar57[7] ^ 0x80;
                    puVar30[0xf] = auVar140[7] ^ 0x80;
                    puVar30[0x10] = auVar57[8] ^ 0x80;
                    puVar30[0x11] = auVar140[8] ^ 0x80;
                    puVar30[0x12] = auVar57[9] ^ 0x80;
                    puVar30[0x13] = auVar140[9] ^ 0x80;
                    puVar30[0x14] = auVar57[10] ^ 0x80;
                    puVar30[0x15] = auVar140[10] ^ 0x80;
                    puVar30[0x16] = auVar57[11] ^ 0x80;
                    puVar30[0x17] = auVar140[11] ^ 0x80;
                    puVar30[0x18] = auVar57[12] ^ 0x80;
                    puVar30[0x19] = auVar140[12] ^ 0x80;
                    puVar30[0x1a] = auVar57[13] ^ 0x80;
                    puVar30[0x1b] = auVar140[13] ^ 0x80;
                    puVar30[0x1c] = auVar57[14] ^ 0x80;
                    puVar30[0x1d] = auVar140[14] ^ 0x80;
                    puVar30[0x1e] = auVar57[15] ^ 0x80;
                    puVar30[0x1f] = auVar140[15] ^ 0x80;
                    puVar30 = puVar30 + 0x20;
                  } while (lVar43 != 0);
                  lVar43 = lVar49;
                  uVar50 = lVar49 * 2;
                  auVar140 = local_540._0_16_;
                  iVar34 = iStack_548;
                  iVar152 = iStack_544;
                  if (uVar51 < 9) goto LAB_0010b6fc;
                }
                uVar52 = lVar43 << 3;
                pbVar31 = (byte *)((long)__s + (ulong)uVar35 + lVar43 * 2 + uVar53);
                lVar43 = ~(uVar42 >> 1) + uVar10 + lVar43;
                do {
                  pauVar38 = (undefined (*) [16])(lVar4 + (uVar52 & 0xfffffff8));
                  auVar57 = pauVar38[2];
                  auVar62 = pauVar38[3];
                  pauVar6 = (undefined (*) [16])(lVar3 + (uVar52 & 0xfffffff8));
                  auVar63 = *pauVar38;
                  auVar68 = pauVar38[1];
                  lVar43 = lVar43 + 8;
                  auVar80 = pauVar6[2];
                  auVar85 = pauVar6[3];
                  auVar91 = *pauVar6;
                  auVar92 = pauVar6[1];
                  auVar121 = a64_TBL(ZEXT816(0),auVar57,auVar62,auVar18);
                  auVar104 = a64_TBL(ZEXT816(0),auVar63,auVar68,auVar23);
                  auVar110 = a64_TBL(ZEXT816(0),auVar57,auVar62,auVar28);
                  auVar116 = a64_TBL(ZEXT816(0),auVar63,auVar68,auVar27);
                  auVar89._2_2_ = sStack_48e;
                  auVar89._0_2_ = local_490;
                  auVar89._4_2_ = sStack_48c;
                  auVar89._6_2_ = sStack_48a;
                  auVar89._8_8_ = uVar41;
                  auVar145 = a64_TBL(ZEXT816(0),auVar57,auVar62,auVar25);
                  auVar136 = a64_TBL(ZEXT816(0),auVar63,auVar68,auVar140);
                  auVar148 = a64_TBL(ZEXT816(0),auVar57,auVar62,auVar24);
                  auVar130 = a64_TBL(ZEXT816(0),auVar57,auVar62,auVar89);
                  auVar57 = a64_TBL(ZEXT816(0),auVar57,auVar62,auVar19);
                  auVar62 = a64_TBL(ZEXT816(0),auVar80,auVar85,auVar18);
                  auVar141 = a64_TBL(ZEXT816(0),auVar91,auVar92,auVar23);
                  auVar126 = a64_TBL(ZEXT816(0),auVar63,auVar68,auVar26);
                  auVar139 = a64_TBL(ZEXT816(0),auVar63,auVar68,auVar20);
                  auVar68 = a64_TBL(ZEXT816(0),auVar63,auVar68,auVar21);
                  auVar74 = a64_TBL(ZEXT816(0),auVar80,auVar85,auVar25);
                  auVar97 = a64_TBL(ZEXT816(0),auVar91,auVar92,auVar26);
                  auVar111 = a64_TBL(ZEXT816(0),auVar80,auVar85,auVar89);
                  auVar122 = a64_TBL(ZEXT816(0),auVar91,auVar92,auVar140);
                  auVar131 = a64_TBL(ZEXT816(0),auVar80,auVar85,auVar28);
                  auVar63 = a64_TBL(ZEXT816(0),auVar91,auVar92,auVar27);
                  auVar75 = a64_TBL(ZEXT816(0),auVar80,auVar85,auVar24);
                  auVar105 = a64_TBL(ZEXT816(0),auVar91,auVar92,auVar20);
                  auVar80 = a64_TBL(ZEXT816(0),auVar80,auVar85,auVar19);
                  auVar85 = a64_TBL(ZEXT816(0),auVar91,auVar92,auVar21);
                  uVar52 = uVar52 + 0x40;
                  uVar79 = (uint)(ushort)((ushort)auVar121[4] + (ushort)auVar110[4]) +
                           (uint)auVar62[4] + (uint)auVar131[4] + 2 >> 2;
                  uVar81 = (uint)(ushort)((ushort)auVar121[5] + (ushort)auVar110[5]) +
                           (uint)auVar62[5] + (uint)auVar131[5] + 2 >> 2;
                  uVar82 = (uint)(ushort)((ushort)auVar121[6] + (ushort)auVar110[6]) +
                           (uint)auVar62[6] + (uint)auVar131[6] + 2 >> 2;
                  uVar83 = (uint)(ushort)((ushort)auVar121[7] + (ushort)auVar110[7]) +
                           (uint)auVar62[7] + (uint)auVar131[7] + 2 >> 2;
                  uVar56 = (uint)(ushort)((ushort)auVar104[0] + (ushort)auVar116[0]) +
                           (CONCAT12(auVar141[1],(ushort)auVar141[0]) & 0xffff) +
                           (CONCAT12(auVar63[1],(ushort)auVar63[0]) & 0xffff) + 2 >> 2;
                  uVar58 = (uint)(ushort)((ushort)auVar104[1] + (ushort)auVar116[1]) +
                           (uint)auVar141[1] + (uint)auVar63[1] + 2 >> 2;
                  uVar59 = (uint)(ushort)((ushort)auVar104[2] + (ushort)auVar116[2]) +
                           (uint)auVar141[2] + (uint)auVar63[2] + 2 >> 2;
                  uVar60 = (uint)(ushort)((ushort)auVar104[3] + (ushort)auVar116[3]) +
                           (uint)auVar141[3] + (uint)auVar63[3] + 2 >> 2;
                  uVar61 = (uint)(ushort)((ushort)auVar145[4] + (ushort)auVar148[4]) +
                           (uint)auVar74[4] + (uint)auVar75[4] + 2 >> 2;
                  uVar64 = (uint)(ushort)((ushort)auVar145[5] + (ushort)auVar148[5]) +
                           (uint)auVar74[5] + (uint)auVar75[5] + 2 >> 2;
                  uVar65 = (uint)(ushort)((ushort)auVar145[6] + (ushort)auVar148[6]) +
                           (uint)auVar74[6] + (uint)auVar75[6] + 2 >> 2;
                  uVar66 = (uint)(ushort)((ushort)auVar145[7] + (ushort)auVar148[7]) +
                           (uint)auVar74[7] + (uint)auVar75[7] + 2 >> 2;
                  uVar72 = (uint)(ushort)((ushort)auVar126[0] + (ushort)auVar139[0]) +
                           (CONCAT12(auVar97[1],(ushort)auVar97[0]) & 0xffff) +
                           (CONCAT12(auVar105[1],(ushort)auVar105[0]) & 0xffff) + 2 >> 2;
                  uVar76 = (uint)(ushort)((ushort)auVar126[1] + (ushort)auVar139[1]) +
                           (uint)auVar97[1] + (uint)auVar105[1] + 2 >> 2;
                  uVar77 = (uint)(ushort)((ushort)auVar126[2] + (ushort)auVar139[2]) +
                           (uint)auVar97[2] + (uint)auVar105[2] + 2 >> 2;
                  uVar78 = (uint)(ushort)((ushort)auVar126[3] + (ushort)auVar139[3]) +
                           (uint)auVar97[3] + (uint)auVar105[3] + 2 >> 2;
                  uVar84 = (uint)(ushort)((ushort)auVar130[4] + (ushort)auVar57[4]) +
                           (uint)auVar111[4] + (uint)auVar80[4] + 2 >> 2;
                  uVar86 = (uint)(ushort)((ushort)auVar130[5] + (ushort)auVar57[5]) +
                           (uint)auVar111[5] + (uint)auVar80[5] + 2 >> 2;
                  uVar87 = (uint)(ushort)((ushort)auVar130[6] + (ushort)auVar57[6]) +
                           (uint)auVar111[6] + (uint)auVar80[6] + 2 >> 2;
                  uVar88 = (uint)(ushort)((ushort)auVar130[7] + (ushort)auVar57[7]) +
                           (uint)auVar111[7] + (uint)auVar80[7] + 2 >> 2;
                  uVar67 = (uint)(ushort)((ushort)auVar136[0] + (ushort)auVar68[0]) +
                           (CONCAT12(auVar122[1],(ushort)auVar122[0]) & 0xffff) +
                           (CONCAT12(auVar85[1],(ushort)auVar85[0]) & 0xffff) + 2 >> 2;
                  uVar69 = (uint)(ushort)((ushort)auVar136[1] + (ushort)auVar68[1]) +
                           (uint)auVar122[1] + (uint)auVar85[1] + 2 >> 2;
                  uVar70 = (uint)(ushort)((ushort)auVar136[2] + (ushort)auVar68[2]) +
                           (uint)auVar122[2] + (uint)auVar85[2] + 2 >> 2;
                  uVar71 = (uint)(ushort)((ushort)auVar136[3] + (ushort)auVar68[3]) +
                           (uint)auVar122[3] + (uint)auVar85[3] + 2 >> 2;
                  auVar148._8_4_ = 0x7f;
                  auVar148._0_8_ = 0x7f0000007f;
                  auVar148._12_4_ = 0x7f;
                  auVar139._0_4_ =
                       (int)(uVar61 * -0x54cd + uVar79 * -0x2b33 + uVar84 * 0x8000 + 0x8000) >> 0x10
                  ;
                  auVar139._4_4_ =
                       (int)(uVar64 * -0x54cd + uVar81 * -0x2b33 + uVar86 * 0x8000 + 0x8000) >> 0x10
                  ;
                  auVar139._8_4_ =
                       (int)(uVar65 * -0x54cd + uVar82 * iVar34 + uVar87 * 0x8000 + 0x8000) >> 0x10;
                  auVar139._12_4_ =
                       (int)(uVar66 * -0x54cd + uVar83 * iVar152 + uVar88 * 0x8000 + 0x8000) >> 0x10
                  ;
                  auVar136._0_4_ =
                       (int)(uVar72 * -0x54cd + uVar56 * -0x2b33 + uVar67 * 0x8000 + 0x8000) >> 0x10
                  ;
                  auVar136._4_4_ =
                       (int)(uVar76 * -0x54cd + uVar58 * -0x2b33 + uVar69 * 0x8000 + 0x8000) >> 0x10
                  ;
                  auVar136._8_4_ =
                       (int)(uVar77 * -0x54cd + uVar59 * iVar34 + uVar70 * 0x8000 + 0x8000) >> 0x10;
                  auVar136._12_4_ =
                       (int)(uVar78 * -0x54cd + uVar60 * iVar152 + uVar71 * 0x8000 + 0x8000) >> 0x10
                  ;
                  auVar141._0_4_ =
                       (int)(uVar79 * 0x8000 + uVar61 * -0x6b2f + uVar84 * -0x14d1 + 0x8000) >> 0x10
                  ;
                  auVar141._4_4_ =
                       (int)(uVar81 * 0x8000 + uVar64 * -0x6b2f + uVar86 * -0x14d1 + 0x8000) >> 0x10
                  ;
                  auVar141._8_4_ =
                       (int)(uVar82 * 0x8000 + uVar65 * -0x6b2f + uVar87 * iVar149 + 0x8000) >> 0x10
                  ;
                  auVar141._12_4_ =
                       (int)(uVar83 * 0x8000 + uVar66 * -0x6b2f + uVar88 * iVar150 + 0x8000) >> 0x10
                  ;
                  auVar145._0_4_ =
                       (int)(uVar56 * 0x8000 + uVar72 * -0x6b2f + uVar67 * -0x14d1 + 0x8000) >> 0x10
                  ;
                  auVar145._4_4_ =
                       (int)(uVar58 * 0x8000 + uVar76 * -0x6b2f + uVar69 * -0x14d1 + 0x8000) >> 0x10
                  ;
                  auVar145._8_4_ =
                       (int)(uVar59 * 0x8000 + uVar77 * -0x6b2f + uVar70 * iVar149 + 0x8000) >> 0x10
                  ;
                  auVar145._12_4_ =
                       (int)(uVar60 * 0x8000 + uVar78 * -0x6b2f + uVar71 * iVar150 + 0x8000) >> 0x10
                  ;
                  auVar80 = NEON_smin(auVar139,auVar148,4);
                  auVar63 = NEON_smin(auVar136,auVar148,4);
                  auVar62 = NEON_smin(auVar141,auVar148,4);
                  auVar57 = NEON_smin(auVar145,auVar148,4);
                  auVar68 = ZEXT816(0x8080808080808080);
                  auVar63 = a64_TBL(ZEXT816(0),auVar63,auVar80,auVar22);
                  auVar57 = a64_TBL(ZEXT816(0),auVar57,auVar62,auVar22);
                  *pbVar31 = auVar63[0] ^ auVar68[0];
                  pbVar31[1] = auVar57[0] ^ auVar68[0];
                  pbVar31[2] = auVar63[1] ^ auVar68[1];
                  pbVar31[3] = auVar57[1] ^ auVar68[1];
                  pbVar31[4] = auVar63[2] ^ auVar68[2];
                  pbVar31[5] = auVar57[2] ^ auVar68[2];
                  pbVar31[6] = auVar63[3] ^ auVar68[3];
                  pbVar31[7] = auVar57[3] ^ auVar68[3];
                  pbVar31[8] = auVar63[4] ^ auVar68[4];
                  pbVar31[9] = auVar57[4] ^ auVar68[4];
                  pbVar31[10] = auVar63[5] ^ auVar68[5];
                  pbVar31[0xb] = auVar57[5] ^ auVar68[5];
                  pbVar31[0xc] = auVar63[6] ^ auVar68[6];
                  pbVar31[0xd] = auVar57[6] ^ auVar68[6];
                  pbVar31[0xe] = auVar63[7] ^ auVar68[7];
                  pbVar31[0xf] = auVar57[7] ^ auVar68[7];
                  pbVar31 = pbVar31 + 0x10;
                  uVar50 = (uVar55 - uVar10) * 2;
                } while (lVar43 != 0);
              }
            }
LAB_0010b6fc:
            uVar52 = uVar50 << 2;
            do {
              uVar44 = uVar52 & 0xfffffff8;
              uVar52 = uVar52 + 8;
              pbVar31 = (byte *)(lVar4 + uVar44);
              pbVar45 = (byte *)(lVar3 + uVar44);
              pbVar7 = (byte *)(lVar4 + (uVar44 | 4));
              pbVar8 = (byte *)(lVar3 + (uVar44 | 4));
              uVar56 = (uint)pbVar31[1] + (uint)pbVar45[1] + (uint)pbVar7[1] + (uint)pbVar8[1] + 2
                       >> 2;
              uVar58 = (uint)*pbVar31 + (uint)*pbVar45 + (uint)*pbVar7 + (uint)*pbVar8 + 2 >> 2;
              uVar59 = (uint)pbVar31[2] + (uint)pbVar45[2] + (uint)pbVar7[2] + (uint)pbVar8[2] + 2
                       >> 2;
              pbVar31 = puVar2 + uVar50;
              uVar50 = uVar50 + 2;
              iVar149 = (int)(uVar56 * -0x54cd + uVar58 * -0x2b33 + uVar59 * 0x8000 + 0x8000) >>
                        0x10;
              iVar150 = (int)(uVar56 * -0x6b2f + uVar58 * 0x8000 + uVar59 * -0x14d1 + 0x8000) >>
                        0x10;
              if (0x7e < iVar149) {
                iVar149 = 0x7f;
              }
              if (0x7e < iVar150) {
                iVar150 = 0x7f;
              }
              *pbVar31 = (byte)iVar149 ^ 0x80;
              pbVar31[1] = (byte)iVar150 ^ 0x80;
            } while (uVar50 < uVar48);
          }
          uVar47 = uVar47 + 2;
          iVar33 = iVar33 + 1;
          uVar35 = uVar35 + (uint)local_c0;
        } while (uVar47 < local_c0._4_4_);
      }
    }
                    /* try { // try from 0010b7e4 to 0010b7ef has its CatchHandler @ 0010bf90 */
    AndroidBitmap_unlockPixels(param_1,param_2);
                    /* try { // try from 0010b7f0 to 0010b7ff has its CatchHandler @ 0010bf8c */
    iVar33 = (int)&stack0xffffffffffffffa0;
    std::__ndk1::basic_ofstream<char,std::__ndk1::char_traits<char>>::basic_ofstream
              ((basic_string *)&local_3d0,iVar33 - 0x80);
                    /* try { // try from 0010b804 to 0010b83f has its CatchHandler @ 0010bf98 */
    std::__ndk1::basic_ostream<char,std::__ndk1::char_traits<char>>::write
              ((char *)&local_3d0,(long)__s);
    lVar39 = std::__ndk1::basic_filebuf<char,std::__ndk1::char_traits<char>>::close();
    if (lVar39 == 0) {
      std::__ndk1::ios_base::clear((int)&local_3d0 + (int)*(undefined8 *)(local_3d0 - 0x18));
    }
    plVar1 = (long *)(local_3d0 - 0x18);
    local_3d0 = *(ulong *)PTR_VTT_00120dc8;
    uVar35 = *(uint *)((long)auStack_3b0 + *plVar1);
    *(undefined8 *)((long)&local_3d0 + *(long *)(local_3d0 - 0x18)) =
         *(undefined8 *)(PTR_VTT_00120dc8 + 0x18);
    std::__ndk1::basic_filebuf<char,std::__ndk1::char_traits<char>>::~basic_filebuf
              ((basic_filebuf<char,std::__ndk1::char_traits<char>> *)&local_3c8);
    std::__ndk1::basic_ostream<char,std::__ndk1::char_traits<char>>::~basic_ostream
              ((basic_ostream<char,std::__ndk1::char_traits<char>> *)&local_3d0);
    std::__ndk1::basic_ios<char,std::__ndk1::char_traits<char>>::~basic_ios(abStack_320);
    if ((uVar35 & 5) == 0) {
                    /* try { // try from 0010b8a8 to 0010b8b3 has its CatchHandler @ 0010bf84 */
      _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2B8ne180000ILi0EEEPKc
                (local_130,param_3);
      cVar32 = std::__ndk1::
               basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>::rfind
                         ((char)&stack0xffffffffffffffa0 + '0',0x2f);
                    /* try { // try from 0010b8c8 to 0010b8d3 has its CatchHandler @ 0010bf74 */
      std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>::
      resize((ulong)local_130,cVar32);
                    /* try { // try from 0010b8d8 to 0010b8eb has its CatchHandler @ 0010bf70 */
      std::__ndk1::
      operator+[abi_ne180000_<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>
                (local_148,local_130,"/libzxalgo_monopan.so");
                    /* try { // try from 0010b8f0 to 0010b8f7 has its CatchHandler @ 0010bf60 */
      std::__ndk1::to_string((uint)local_c0);
                    /* try { // try from 0010b8fc to 0010b903 has its CatchHandler @ 0010bf50 */
      std::__ndk1::to_string(local_c0._4_4_);
                    /* try { // try from 0010b904 to 0010b917 has its CatchHandler @ 0010bf40 */
      std::__ndk1::operator+(local_190,"LD_LIBRARY_PATH=",local_130);
      local_1c0 = (void *)((ulong)local_148 | 1);
      if (((byte)local_148[0] & 1) != 0) {
        local_1c0 = local_138;
      }
      local_198 = 0;
      local_1b8 = __name;
      if ((local_e0 & 1) != 0) {
        local_1b8 = local_d0;
      }
      local_1b0 = __name_00;
      if ((local_100 & 1) != 0) {
        local_1b0 = local_f0;
      }
      local_1a8 = (void *)((ulong)local_160 | 1);
      if ((local_160[0] & 1) != 0) {
        local_1a8 = local_150;
      }
      local_1a0 = (void *)((ulong)local_178 | 1);
      if ((local_178[0] & 1) != 0) {
        local_1a0 = local_168;
      }
      local_1c8 = param_3;
                    /* try { // try from 0010b9a0 to 0010b9ab has its CatchHandler @ 0010bf30 */
      std::__ndk1::to_string(param_6);
                    /* try { // try from 0010b9ac to 0010b9b7 has its CatchHandler @ 0010bf20 */
      std::__ndk1::to_string(param_7);
                    /* try { // try from 0010b9b8 to 0010b9c7 has its CatchHandler @ 0010bf10 */
      std::__ndk1::to_string(param_8);
      local_260 = (void *)((ulong)local_130 | 1);
      if ((local_130[0] & 1) != 0) {
        local_260 = local_120;
      }
      local_250 = __name;
      if ((local_e0 & 1) != 0) {
        local_250 = local_d0;
      }
      local_248 = __name_00;
      if ((local_100 & 1) != 0) {
        local_248 = local_f0;
      }
      local_240 = (void *)((ulong)local_160 | 1);
      if ((local_160[0] & 1) != 0) {
        local_240 = local_150;
      }
      local_238 = (void *)((ulong)local_178 | 1);
      if ((local_178[0] & 1) != 0) {
        local_238 = local_168;
      }
      local_218 = 0;
      local_230 = (void *)((ulong)local_1e0 | 1);
      if ((local_1e0[0] & 1) != 0) {
        local_230 = local_1d0;
      }
      local_270 = 0;
      local_228 = (void *)((ulong)local_1f8 | 1);
      if ((local_1f8[0] & 1) != 0) {
        local_228 = local_1e8;
      }
      local_220 = (void *)((ulong)local_210 | 1);
      if ((local_210[0] & 1) != 0) {
        local_220 = local_200;
      }
      local_278 = (char *)((ulong)local_190 | 1);
      if ((local_190[0] & 1) != 0) {
        local_278 = local_180;
      }
      __argv = &local_1c8;
      if (param_5 != (char *)0x0) {
        __argv = &local_268;
      }
                    /* try { // try from 0010bac4 to 0010badf has its CatchHandler @ 0010bf88 */
      local_268 = param_3;
      local_258 = param_5;
      uVar35 = posix_spawn(&local_27c,param_3,(posix_spawn_file_actions_t *)0x0,
                           (posix_spawnattr_t *)0x0,__argv,&local_278);
      if (uVar35 == 0) {
        local_3d0 = local_3d0 & 0xffffffff00000000;
        uVar35 = 0;
        do {
                    /* try { // try from 0010baf0 to 0010bafb has its CatchHandler @ 0010bfb0 */
          while (_Var36 = waitpid(local_27c,(int *)&local_3d0,1), _Var36 < 0) {
            piVar40 = (int *)__errno();
            if (*piVar40 != 4) {
LAB_0010bb70:
              uVar35 = 0xffffffff;
              goto LAB_0010bb74;
            }
          }
          if (_Var36 != 0) {
            if ((local_3d0 & 0x7f) != 0) goto LAB_0010bb70;
            uVar35 = (uint)local_3d0 >> 8 & 0xff;
            if (uVar35 != 0) goto LAB_0010bb74;
                    /* try { // try from 0010bcb0 to 0010bcc3 has its CatchHandler @ 0010bf00 */
            std::__ndk1::basic_ifstream<char,std::__ndk1::char_traits<char>>::basic_ifstream
                      ((basic_string *)&local_3d0,iVar33 - 0xa0);
                    /* try { // try from 0010bce0 to 0010bce7 has its CatchHandler @ 0010bef0 */
            if (((*(byte *)((long)auStack_3b0 + *(long *)(local_3d0 - 0x18)) & 5) == 0) &&
               (std::__ndk1::basic_istream<char,std::__ndk1::char_traits<char>>::tellg(),
               extraout_x1 == uVar46)) {
                    /* try { // try from 0010bcf8 to 0010bd1b has its CatchHandler @ 0010beec */
              std::__ndk1::basic_istream<char,std::__ndk1::char_traits<char>>::seekg
                        ((fpos)&local_3d0);
              std::__ndk1::basic_istream<char,std::__ndk1::char_traits<char>>::read
                        ((char *)&local_3d0,(long)__s_00);
              uVar35 = 0;
              if ((*(byte *)((long)auStack_3b0 + *(long *)(local_3d0 - 0x18)) & 5) != 0) {
                uVar35 = 0xfffffffd;
              }
            }
            else {
              uVar35 = 0xfffffffe;
            }
            std::__ndk1::basic_ifstream<char,std::__ndk1::char_traits<char>>::~basic_ifstream
                      ((basic_ifstream<char,std::__ndk1::char_traits<char>> *)&local_3d0);
            applyAlgorithm(_JNIEnv*,_jobject*,char_const*,char_const*,char_const*,int,int,int)::$_0
            ::operator()((__0 *)&local_110);
            if (uVar35 == 0) {
                    /* try { // try from 0010bd5c to 0010bed3 has its CatchHandler @ 0010bf88 */
              iVar33 = AndroidBitmap_lockPixels(param_1,param_2,&local_118);
              uVar41 = DAT_00102f10;
              if (iVar33 == 0) {
                if (local_c0._4_4_ != 0) {
                  uVar46 = 0;
                  do {
                    iVar33 = (int)local_c0;
                    if (iVar33 != 0) {
                      uVar51 = 0;
                      uVar55 = 0;
                      lVar39 = local_118 + uVar46 * (local_b8 & 0xffffffff);
                      do {
                        if (param_5 == (char *)0x0) {
                          iVar34 = (int)((uint)*(byte *)((long)__s_00 +
                                                        (ulong)(uint)((int)uVar55 +
                                                                     (int)uVar46 * iVar33)) * 0x12a
                                        + -0x1220) >> 8;
                          if (0xfe < iVar34) {
                            iVar34 = 0xff;
                          }
                          bVar11 = (byte)iVar34 & ((byte)(iVar34 >> 0x1f) ^ 0xff);
                          *(byte *)(lVar39 + (ulong)((int)uVar51 + 2)) = bVar11;
                          *(byte *)(lVar39 + (ulong)((int)uVar51 + 1)) = bVar11;
                          *(byte *)(lVar39 + (uVar51 & 0xffffffff)) = bVar11;
                        }
                        else {
                          pbVar31 = (byte *)((long)__s_00 +
                                            (ulong)(iVar33 * ((uint)(uVar46 >> 1) & 0x7fffffff)) +
                                            (uVar55 & 0xfffffffe) + uVar53);
                          bVar11 = *(byte *)((long)__s_00 +
                                            (ulong)(uint)((int)uVar55 + (int)uVar46 * iVar33));
                          iVar152 = *pbVar31 - 0x80;
                          iVar149 = pbVar31[1] - 0x80;
                          puVar2 = (undefined *)(lVar39 + (uVar51 & 0xfffffffc));
                          iVar34 = (uint)bVar11 + (iVar152 * 0x1c520 + 0x8000 >> 0x10);
                          if (0xfe < iVar34) {
                            iVar34 = 0xff;
                          }
                          puVar2[2] = (byte)iVar34 & ((byte)(iVar34 >> 0x1f) ^ 0xff);
                          uVar73 = NEON_smin(CONCAT44((uint)bVar11 +
                                                      (iVar152 * -0x57cf + 0x8000 +
                                                       iVar149 * (int)((ulong)uVar41 >> 0x20) >>
                                                      0x10),(uint)bVar11 +
                                                            (iVar149 * (int)uVar41 + 0x8000 >> 0x10)
                                                     ),0xff000000ff,4);
                          uVar73 = NEON_smax(uVar73,0,4);
                          *puVar2 = (char)uVar73;
                          puVar2[1] = (char)((ulong)uVar73 >> 0x20);
                        }
                        uVar55 = uVar55 + 1;
                        uVar51 = uVar51 + 4;
                      } while (uVar55 < (local_c0 & 0xffffffff));
                    }
                    uVar46 = uVar46 + 1;
                  } while (uVar46 < local_c0._4_4_);
                }
                AndroidBitmap_unlockPixels(param_1,param_2);
                uVar35 = 0;
              }
              else {
                uVar35 = 0xfffffffc;
              }
            }
            goto LAB_0010bb7c;
          }
                    /* try { // try from 0010bb18 to 0010bb1f has its CatchHandler @ 0010bf0c */
          usleep(50000);
          bVar29 = uVar35 < 599;
          uVar35 = uVar35 + 1;
        } while (bVar29);
                    /* try { // try from 0010bb30 to 0010bb37 has its CatchHandler @ 0010bf04 */
        kill(local_27c,9);
        uVar35 = 0xfffffffb;
        do {
                    /* try { // try from 0010bb40 to 0010bb4b has its CatchHandler @ 0010bf08 */
          _Var36 = waitpid(local_27c,(int *)&local_3d0,0);
          if (-1 < _Var36) {
            uVar35 = 0xfffffffb;
            break;
          }
          piVar40 = (int *)__errno();
        } while (*piVar40 == 4);
      }
LAB_0010bb74:
      applyAlgorithm(_JNIEnv*,_jobject*,char_const*,char_const*,char_const*,int,int,int)::$_0::
      operator()((__0 *)&local_110);
LAB_0010bb7c:
      puVar2 = &UNK_00103949;
      if (param_5 != (char *)0x0) {
        puVar2 = &DAT_0010394c;
      }
                    /* try { // try from 0010bb98 to 0010bbb3 has its CatchHandler @ 0010bf88 */
      __android_log_print(4,"LeicaNative","%s original algorithm result=%d size=%ux%u",puVar2,uVar35
                          ,local_c0 & 0xffffffff,local_c0._4_4_);
      bVar29 = uVar35 == 0;
      if ((local_210[0] & 1) != 0) {
        operator_delete(local_200);
      }
      if ((local_1f8[0] & 1) != 0) {
        operator_delete(local_1e8);
      }
      if ((local_1e0[0] & 1) != 0) {
        operator_delete(local_1d0);
      }
      if ((local_190[0] & 1) != 0) {
        operator_delete(local_180);
      }
      if ((local_178[0] & 1) != 0) {
        operator_delete(local_168);
      }
      if ((local_160[0] & 1) != 0) {
        operator_delete(local_150);
      }
      if (((byte)local_148[0] & 1) != 0) {
        operator_delete(local_138);
      }
      if ((local_130[0] & 1) != 0) {
        operator_delete(local_120);
      }
      goto LAB_0010ae48;
    }
    applyAlgorithm(_JNIEnv*,_jobject*,char_const*,char_const*,char_const*,int,int,int)::$_0::
    operator()((__0 *)&local_110);
  }
  bVar29 = false;
LAB_0010ae48:
  if ((local_100 & 1) != 0) {
    operator_delete(local_f0);
  }
  if ((local_e0 & 1) != 0) {
    operator_delete(local_d0);
  }
  operator_delete(__s_00);
  operator_delete(__s);
  return bVar29;
}



/* 0010c118 Java_com_codex_lmoments_NativeModel_applyLut */

uint Java_com_codex_lmoments_NativeModel_applyLut
               (long *param_1,undefined8 param_2,_JNIEnv *param_3,long param_4,uint param_5)

{
  uint uVar1;
  _jobject *p_Var2;
  
  uVar1 = 0;
  if ((param_3 != (_JNIEnv *)0x0) && (param_4 != 0)) {
    uVar1 = param_5;
    p_Var2 = (_jobject *)(**(code **)(*param_1 + 0x548))(param_1,param_4,0);
    uVar1 = (anonymous_namespace)::applyLut
                      ((_anonymous_namespace_ *)param_1,param_3,p_Var2,(char *)(ulong)param_5,uVar1,
                       -1.0,5000.0);
    if (p_Var2 != (_jobject *)0x0) {
      (**(code **)(*param_1 + 0x550))(param_1,param_4,p_Var2);
    }
    uVar1 = uVar1 & 1;
  }
  return uVar1;
}



/* 0010c1c0 Java_com_codex_lmoments_NativeModel_applyMonochrome */

uint Java_com_codex_lmoments_NativeModel_applyMonochrome
               (long *param_1,undefined8 param_2,_jobject *param_3,long param_4,long param_5)

{
  uint uVar1;
  char *pcVar2;
  char *pcVar3;
  
  uVar1 = 0;
  if (((param_3 != (_jobject *)0x0) && (param_4 != 0)) && (param_5 != 0)) {
    pcVar2 = (char *)(**(code **)(*param_1 + 0x548))(param_1,param_4,0);
    pcVar3 = (char *)(**(code **)(*param_1 + 0x548))(param_1,param_5,0);
    uVar1 = (anonymous_namespace)::applyAlgorithm
                      ((_JNIEnv *)param_1,param_3,pcVar2,pcVar3,(char *)0x0,0,200,5000);
    if (pcVar2 != (char *)0x0) {
      (**(code **)(*param_1 + 0x550))(param_1,param_4,pcVar2);
    }
    if (pcVar3 != (char *)0x0) {
      (**(code **)(*param_1 + 0x550))(param_1,param_5,pcVar3);
    }
    uVar1 = uVar1 & 1;
  }
  return uVar1;
}



/* 0010c2a4 Java_com_codex_lmoments_LegendaryPostProcessor_applyStyle */

uint Java_com_codex_lmoments_LegendaryPostProcessor_applyStyle
               (long *param_1,undefined8 param_2,_jobject *param_3,long param_4,long param_5,
               long param_6,int param_7,int param_8,int param_9)

{
  uint uVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  uint uVar5;
  
  if (param_3 == (_jobject *)0x0) {
    return 0;
  }
  if (param_4 == 0) {
    return 0;
  }
  if (param_5 == 0) {
    return 0;
  }
  if (param_6 == 0) {
    return 0;
  }
  pcVar2 = (char *)(**(code **)(*param_1 + 0x548))(param_1,param_4,0);
  pcVar3 = (char *)(**(code **)(*param_1 + 0x548))(param_1,param_5,0);
  pcVar4 = (char *)(**(code **)(*param_1 + 0x548))(param_1,param_6,0);
  if (((pcVar2 == (char *)0x0) || (pcVar3 == (char *)0x0)) || (pcVar4 == (char *)0x0)) {
    uVar5 = 0;
    uVar1 = 0;
    if (pcVar2 == (char *)0x0) goto LAB_0010c3a0;
  }
  else {
    uVar1 = (anonymous_namespace)::applyAlgorithm
                      ((_JNIEnv *)param_1,param_3,pcVar2,pcVar3,pcVar4,param_7,param_8,param_9);
    uVar1 = uVar1 & 1;
  }
  uVar5 = uVar1;
  (**(code **)(*param_1 + 0x550))(param_1,param_4,pcVar2);
LAB_0010c3a0:
  if (pcVar3 != (char *)0x0) {
    (**(code **)(*param_1 + 0x550))(param_1,param_5,pcVar3);
  }
  if (pcVar4 != (char *)0x0) {
    (**(code **)(*param_1 + 0x550))(param_1,param_6,pcVar4);
  }
  return uVar5;
}



/* 0010c3f8 Java_com_codex_lmoments_LegendaryPostProcessor_applyAdaptiveLut */

_jobject *
Java_com_codex_lmoments_LegendaryPostProcessor_applyAdaptiveLut
          (float param_1,float param_2,long *param_3,undefined8 param_4,_JNIEnv *param_5,
          long param_6,int param_7)

{
  uint uVar1;
  _jobject *p_Var2;
  
  p_Var2 = (_jobject *)0x0;
  if (((param_5 != (_JNIEnv *)0x0) && (param_6 != 0)) &&
     (p_Var2 = (_jobject *)(**(code **)(*param_3 + 0x548))(param_3,param_6,0),
     p_Var2 != (_jobject *)0x0)) {
    uVar1 = (anonymous_namespace)::applyLut
                      ((_anonymous_namespace_ *)param_3,param_5,p_Var2,(char *)0x0,param_7,param_1,
                       param_2);
    (**(code **)(*param_3 + 0x550))(param_3,param_6,p_Var2);
    p_Var2 = (_jobject *)(ulong)(uVar1 & 1);
  }
  return p_Var2;
}



/* 0010c49c Java_com_codex_lmoments_LegendaryPostProcessor_previewLut */

long Java_com_codex_lmoments_LegendaryPostProcessor_previewLut
               (float param_1,float param_2,long *param_3,undefined8 param_4,long param_5)

{
  char *pcVar1;
  vector *pvVar2;
  ulong uVar3;
  void *local_58;
  void *local_50;
  undefined8 local_48;
  
  if (param_5 != 0) {
    pcVar1 = (char *)(**(code **)(*param_3 + 0x548))(param_3,param_5,0);
    if (pcVar1 == (char *)0x0) {
      param_5 = 0;
    }
    else {
      local_58 = (void *)0x0;
      local_50 = (void *)0x0;
      local_48 = 0;
                    /* try { // try from 0010c4ec to 0010c4ff has its CatchHandler @ 0010c5c4 */
      pvVar2 = (vector *)previewModel(pcVar1);
      uVar3 = adaptiveLut(pvVar2,param_1,param_2,(vector *)&local_58);
                    /* try { // try from 0010c50c to 0010c51b has its CatchHandler @ 0010c5a8 */
      (**(code **)(*param_3 + 0x550))(param_3,param_5,pcVar1);
      if ((uVar3 & 1) == 0) {
        param_5 = 0;
      }
      else {
                    /* try { // try from 0010c534 to 0010c567 has its CatchHandler @ 0010c5a4 */
        param_5 = (**(code **)(*param_3 + 0x580))(param_3,(int)local_50 - (int)local_58);
        if (param_5 != 0) {
          (**(code **)(*param_3 + 0x680))(param_3,param_5,0,(int)local_50 - (int)local_58);
        }
      }
      if (local_58 != (void *)0x0) {
        local_50 = local_58;
        operator_delete(local_58);
      }
    }
  }
  return param_5;
}



/* 0010c620 adaptiveLut */

/* adaptiveLut(std::__ndk1::vector<unsigned char, std::__ndk1::allocator<unsigned char> > const&,
   float, float, std::__ndk1::vector<unsigned char, std::__ndk1::allocator<unsigned char> >&) */

undefined4 adaptiveLut(vector *param_1,float param_2,float param_3,vector *param_4)

{
  short *psVar1;
  uint uVar2;
  void *pvVar3;
  bool bVar4;
  ulong uVar5;
  long lVar6;
  undefined4 *puVar7;
  long lVar8;
  byte *pbVar9;
  undefined8 *puVar10;
  ulong uVar11;
  ulong uVar12;
  long lVar13;
  undefined uVar14;
  undefined uVar15;
  float fVar16;
  undefined4 uVar17;
  undefined auVar18 [16];
  undefined4 uVar19;
  undefined auVar20 [16];
  void *local_d8;
  void *local_d0;
  float local_c0;
  undefined4 uStack_bc;
  void *local_b8;
  void *local_a8;
  void *local_a0;
  uint local_8c;
  long local_88;
  long lStack_80;
  undefined8 local_78;
  
  uVar17 = 0;
  if (((ABS(param_3) != INFINITY) && (ABS(param_2) != INFINITY)) &&
     (psVar1 = *(short **)param_1, 0x4992 < (ulong)(*(long *)(param_1 + 8) - (long)psVar1))) {
    if (((*psVar1 == 6) && (psVar1[7] == 0x400)) && ((psVar1[8] == 0x1000 && (psVar1[9] == 0x11))))
    {
      local_88 = 0;
      lStack_80 = 0;
      local_78 = 0;
      local_8c = 0;
                    /* try { // try from 0010c6d8 to 0010c6ef has its CatchHandler @ 0010c988 */
      uVar5 = leicaRanges(param_1,0x440,(ulong)(ushort)psVar1[1] + 0x400,(vector *)&local_88,
                          &local_8c);
      if (((uVar5 & 1) == 0) ||
         ((ulong)(*(long *)(param_1 + 8) - *(long *)param_1) < (ulong)local_8c * 0x3993 + 0x4993)) {
        uVar17 = 0;
      }
      else {
        local_c0 = 0.0;
                    /* try { // try from 0010c748 to 0010c757 has its CatchHandler @ 0010c984 */
        std::__ndk1::vector<float,std::__ndk1::allocator<float>>::vector
                  ((vector<float,std::__ndk1::allocator<float>> *)&local_a8,0x3993,&local_c0);
                    /* try { // try from 0010c758 to 0010c767 has its CatchHandler @ 0010c97c */
        leicaWeights((vector *)&local_88,param_2);
        if (lStack_80 != local_88) {
          uVar5 = 0;
          lVar13 = lStack_80;
          lVar8 = local_88;
          do {
            if (0.0 < *(float *)(CONCAT44(uStack_bc,local_c0) + uVar5 * 4)) {
                    /* try { // try from 0010c7cc to 0010c7db has its CatchHandler @ 0010c990 */
              leicaWeights((vector *)(lVar8 + uVar5 * 0x28 + 0x10),param_3);
              if ((long)local_d0 - (long)local_d8 != 0) {
                uVar12 = (long)local_d0 - (long)local_d8 >> 2;
                lVar13 = *(long *)param_1;
                uVar11 = 0;
                if (uVar12 < 2) {
                  uVar12 = 1;
                }
                do {
                  fVar16 = *(float *)((long)local_d8 + uVar11 * 4);
                  if (0.0 < fVar16) {
                    fVar16 = fVar16 * *(float *)(CONCAT44(uStack_bc,local_c0) + uVar5 * 4);
                    uVar2 = *(uint *)(*(long *)(local_88 + uVar5 * 0x28 + 0x10) + uVar11 * 0x28 + 8)
                    ;
                    if (local_a8 < (void *)(lVar13 + 0x4993 + (ulong)uVar2 * 0x3993) &&
                        lVar13 + 0x1000 + (ulong)uVar2 * 0x3993 < (long)local_a8 + 0xe64cU) {
                      lVar8 = 0;
                    }
                    else {
                      lVar8 = -0x3990;
                      puVar10 = (undefined8 *)((long)local_a8 + 0x10);
                      do {
                        lVar6 = lVar13 + 0x1004 + (ulong)uVar2 * 0x3993 + lVar8;
                        uVar17 = *(undefined4 *)(lVar6 + 0x398c);
                        uVar19 = *(undefined4 *)(lVar6 + 0x3990);
                        lVar8 = lVar8 + 8;
                        uVar14 = (undefined)((uint)uVar17 >> 8);
                        uVar15 = (undefined)((uint)uVar19 >> 8);
                        auVar18._6_2_ = 0;
                        auVar18._0_6_ =
                             (uint6)CONCAT14(uVar14,(uint)CONCAT12(uVar14,(ushort)(byte)uVar17)) &
                             0xffff0000ffff;
                        auVar18[8] = (char)((uint)uVar17 >> 0x10);
                        auVar18._9_3_ = 0;
                        auVar18[12] = (char)((uint)uVar17 >> 0x18);
                        auVar18._13_3_ = 0;
                        auVar20._6_2_ = 0;
                        auVar20._0_6_ =
                             (uint6)CONCAT14(uVar15,(uint)CONCAT12(uVar15,(ushort)(byte)uVar19)) &
                             0xffff0000ffff;
                        auVar20[8] = (char)((uint)uVar19 >> 0x10);
                        auVar20._9_3_ = 0;
                        auVar20[12] = (char)((uint)uVar19 >> 0x18);
                        auVar20._13_3_ = 0;
                        auVar18 = NEON_ucvtf(auVar18,4);
                        auVar20 = NEON_ucvtf(auVar20,4);
                        puVar10[-1] = CONCAT44((float)((ulong)puVar10[-1] >> 0x20) +
                                               auVar18._12_4_ * fVar16,
                                               (float)puVar10[-1] + auVar18._8_4_ * fVar16);
                        puVar10[-2] = CONCAT44((float)((ulong)puVar10[-2] >> 0x20) +
                                               auVar18._4_4_ * fVar16,
                                               (float)puVar10[-2] + auVar18._0_4_ * fVar16);
                        puVar10[1] = CONCAT44((float)((ulong)puVar10[1] >> 0x20) +
                                              auVar20._12_4_ * fVar16,
                                              (float)puVar10[1] + auVar20._8_4_ * fVar16);
                        *puVar10 = CONCAT44((float)((ulong)*puVar10 >> 0x20) +
                                            auVar20._4_4_ * fVar16,
                                            (float)*puVar10 + auVar20._0_4_ * fVar16);
                        puVar10 = puVar10 + 4;
                      } while (lVar8 != 0);
                      lVar8 = 0x3990;
                    }
                    lVar6 = lVar8 + -0x3993;
                    puVar7 = (undefined4 *)((long)local_a8 + lVar8 * 4);
                    pbVar9 = (byte *)(lVar13 + 0x1000 + lVar8 + (ulong)uVar2 * 0x3993);
                    do {
                      bVar4 = lVar6 != -1;
                      lVar6 = lVar6 + 1;
                      uVar17 = NEON_fmadd(fVar16,(float)(ulong)*pbVar9,*puVar7);
                      *puVar7 = uVar17;
                      puVar7 = puVar7 + 1;
                      pbVar9 = pbVar9 + 1;
                    } while (bVar4);
                  }
                  uVar11 = uVar11 + 1;
                } while (uVar11 != uVar12);
              }
              lVar13 = lStack_80;
              lVar8 = local_88;
              if (local_d8 != (void *)0x0) {
                local_d0 = local_d8;
                operator_delete(local_d8);
                lVar13 = lStack_80;
                lVar8 = local_88;
              }
            }
            uVar5 = uVar5 + 1;
          } while (uVar5 < (ulong)((lVar13 - lVar8 >> 3) * -0x3333333333333333));
        }
                    /* try { // try from 0010c910 to 0010c91b has its CatchHandler @ 0010c978 */
        std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>::resize
                  ((vector<unsigned_char,std::__ndk1::allocator<unsigned_char>> *)param_4,0x3993);
        lVar13 = 0;
        do {
          *(char *)(*(long *)param_4 + lVar13) = (char)(long)*(float *)((long)local_a8 + lVar13 * 4)
          ;
          lVar13 = lVar13 + 1;
        } while (lVar13 != 0x3993);
        pvVar3 = (void *)CONCAT44(uStack_bc,local_c0);
        if (pvVar3 != (void *)0x0) {
          local_b8 = pvVar3;
          operator_delete(pvVar3);
        }
        if (local_a8 != (void *)0x0) {
          local_a0 = local_a8;
          operator_delete(local_a8);
        }
        uVar17 = 1;
      }
      std::__ndk1::vector<LeicaRange,std::__ndk1::allocator<LeicaRange>>::~vector_abi_ne180000_
                ((vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *)&local_88);
    }
    else {
      uVar17 = 0;
    }
  }
  return uVar17;
}



/* 0010c9c4 previewModel */

/* previewModel(char const*) */

char ** previewModel(char *param_1)

{
  char **this;
  undefined8 *puVar1;
  long lVar2;
  __tree_iterator _Var3;
  pair pVar4;
  long lVar5;
  size_t __n;
  long *plVar7;
  runtime_error *prVar8;
  ulong __n_00;
  void *pvVar9;
  undefined8 local_198;
  size_t local_190;
  void *local_188 [21];
  basic_ios<char,std::__ndk1::char_traits<char>> abStack_e0 [152];
  char *local_48;
  char **ppcVar6;
  
  local_48 = param_1;
  lVar5 = (*(code *)PTR_00120e20)(&PTR_00120e20);
  lVar2 = tpidr_el0;
  if ((*(byte *)(lVar2 + lVar5) & 1) == 0) {
    lVar5 = (*(code *)PTR_00120e30)(&PTR_00120e30);
    puVar1 = (undefined8 *)(lVar2 + lVar5);
    puVar1[2] = 0;
    puVar1[1] = 0;
    *puVar1 = puVar1 + 1;
    __cxa_thread_atexit(std::__ndk1::
                        map<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,std::__ndk1::allocator<std::__ndk1::pair<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>const,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
                        ::~map_abi_ne180000_,puVar1,&__dso_handle);
    lVar5 = (*(code *)PTR_00120e20)(&PTR_00120e20);
    *(undefined *)(lVar2 + lVar5) = 1;
  }
  lVar5 = (*(code *)PTR_00120e30)(&PTR_00120e30);
  __n = strlen(param_1);
  if (0xffffffffffffffef < __n) {
    std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>::
    __throw_length_error_abi_ne180000_();
    goto LAB_0010cc18;
  }
  this = (char **)(lVar2 + lVar5);
  if (__n < 0x17) {
    pvVar9 = (void *)((ulong)&local_198 | 1);
    local_198 = CONCAT71(local_198._1_7_,(char)((int)__n << 1));
    if (__n != 0) goto LAB_0010ca68;
  }
  else {
    pvVar9 = operator_new((__n | 0xf) + 1);
    local_198 = (__n | 0xf) + 2;
    local_190 = __n;
    local_188[0] = pvVar9;
LAB_0010ca68:
    memcpy(pvVar9,param_1,__n);
  }
  *(undefined *)((long)pvVar9 + __n) = 0;
                    /* try { // try from 0010ca7c to 0010ca87 has its CatchHandler @ 0010ccdc */
  _Var3 = std::__ndk1::
          __tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
          ::
          find<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>
                    ((__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
                      *)this,(basic_string *)&local_198);
  ppcVar6 = (char **)(ulong)_Var3;
  if ((local_198 & 1) != 0) {
    operator_delete(local_188[0]);
  }
  if (this + 1 == ppcVar6) {
    std::__ndk1::basic_ifstream<char,std::__ndk1::char_traits<char>>::basic_ifstream
              ((char *)&local_198,(uint)local_48);
                    /* try { // try from 0010cab8 to 0010cabf has its CatchHandler @ 0010ccb4 */
    std::__ndk1::basic_istream<char,std::__ndk1::char_traits<char>>::tellg();
    if (__n_00 - 0x800001 < 0xffffffffff800fff) {
LAB_0010cc18:
      prVar8 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0010cc24 to 0010cc2f has its CatchHandler @ 0010cc8c */
      std::runtime_error::runtime_error(prVar8,"Invalid preview model size");
                    /* try { // try from 0010cc30 to 0010cc47 has its CatchHandler @ 0010ccb4 */
                    /* WARNING: Subroutine does not return */
      __cxa_throw(prVar8,PTR_typeinfo_00120dd0,PTR__runtime_error_00120dd8);
    }
                    /* try { // try from 0010cadc to 0010cae3 has its CatchHandler @ 0010ccac */
    pvVar9 = operator_new(__n_00);
    memset(pvVar9,0,__n_00);
                    /* try { // try from 0010cb04 to 0010cb23 has its CatchHandler @ 0010ccbc */
    std::__ndk1::basic_istream<char,std::__ndk1::char_traits<char>>::seekg((fpos)&local_198);
    plVar7 = (long *)std::__ndk1::basic_istream<char,std::__ndk1::char_traits<char>>::read
                               ((char *)&local_198,(long)pvVar9);
    if ((*(byte *)((long)plVar7 + *(long *)(*plVar7 + -0x18) + 0x20) & 5) != 0) {
      prVar8 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0010cc58 to 0010cc63 has its CatchHandler @ 0010cc7c */
      std::runtime_error::runtime_error(prVar8,"Cannot read preview model");
                    /* try { // try from 0010cc64 to 0010cc7b has its CatchHandler @ 0010ccbc */
                    /* WARNING: Subroutine does not return */
      __cxa_throw(prVar8,PTR_typeinfo_00120dd0,PTR__runtime_error_00120dd8);
    }
                    /* try { // try from 0010cb40 to 0010cb4f has its CatchHandler @ 0010cc9c */
    pVar4 = std::__ndk1::
            __tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
            ::
            __emplace_unique_impl<char_const*&,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>
                      (this,(vector *)&local_48);
    ppcVar6 = (char **)(ulong)pVar4;
    if (pvVar9 != (void *)0x0) {
      operator_delete(pvVar9);
    }
    local_198 = *(ulong *)PTR_VTT_00120dc0;
    *(undefined8 *)((long)&local_198 + *(long *)(local_198 + -0x18)) =
         *(undefined8 *)(PTR_VTT_00120dc0 + 0x18);
    std::__ndk1::basic_filebuf<char,std::__ndk1::char_traits<char>>::~basic_filebuf
              ((basic_filebuf<char,std::__ndk1::char_traits<char>> *)local_188);
    std::__ndk1::basic_istream<char,std::__ndk1::char_traits<char>>::~basic_istream
              ((basic_istream<char,std::__ndk1::char_traits<char>> *)&local_198);
    std::__ndk1::basic_ios<char,std::__ndk1::char_traits<char>>::~basic_ios(abStack_e0);
  }
  return ppcVar6 + 7;
}



/* 0010ccf8 Java_com_codex_lmoments_LegendaryPostProcessor_applyOriginalFilter */

char * Java_com_codex_lmoments_LegendaryPostProcessor_applyOriginalFilter
                 (float param_1,float param_2,float param_3,float param_4,long *param_5,
                 undefined8 param_6,_jobject *param_7,long param_8)

{
  uint uVar1;
  char *pcVar2;
  
  pcVar2 = (char *)0x0;
  if (((param_7 != (_jobject *)0x0) && (param_8 != 0)) &&
     (pcVar2 = (char *)(**(code **)(*param_5 + 0x548))(param_5,param_8,0), pcVar2 != (char *)0x0)) {
    uVar1 = (anonymous_namespace)::applyLeicaFilter
                      ((_JNIEnv *)param_5,param_7,pcVar2,param_1,param_2,param_3,param_4,-1.0,false,
                       -0.35,0.025);
    (**(code **)(*param_5 + 0x550))(param_5,param_8,pcVar2);
    pcVar2 = (char *)(ulong)(uVar1 & 1);
  }
  return pcVar2;
}



/* 0010cdd0 applyLeicaFilter */

/* (anonymous namespace)::applyLeicaFilter(_JNIEnv*, _jobject*, char const*, float, float, float,
   float, float, bool, float, float) */

undefined4
(anonymous_namespace)::applyLeicaFilter
          (_JNIEnv *param_1,_jobject *param_2,char *param_3,float param_4,float param_5,
          float param_6,float param_7,float param_8,bool param_9,float param_10,float param_11)

{
  pthread_t pVar1;
  int iVar2;
  ulong uVar3;
  __thread_struct *this;
  undefined8 uVar4;
  undefined8 in_x6;
  undefined8 in_x7;
  undefined4 uVar5;
  long lVar6;
  pthread_t local_2f0;
  pthread_t local_2e8 [3];
  undefined8 *local_2d0;
  long *plStack_2c8;
  __thread_struct *local_2c0;
  void **ppvStack_2b8;
  __thread_struct *local_2b0;
  float *pfStack_2a8;
  float *local_2a0;
  float *pfStack_298;
  __thread_struct *local_290;
  float *pfStack_288;
  float *local_280;
  void **ppvStack_278;
  long local_270;
  undefined8 local_268;
  undefined8 uStack_260;
  undefined4 local_258;
  __thread_struct local_250 [4];
  __thread_struct local_24c [4];
  float local_248;
  float fStack_244;
  float local_240;
  float fStack_23c;
  float local_238;
  float fStack_234;
  float local_230;
  float fStack_22c;
  void *local_228;
  void *local_220;
  undefined8 local_218;
  void *local_210;
  void *local_208;
  undefined8 uStack_200;
  long local_1f8 [2];
  basic_filebuf<char,std::__ndk1::char_traits<char>> abStack_1e8 [24];
  undefined8 auStack_1d0 [18];
  basic_ios<char,std::__ndk1::char_traits<char>> abStack_140 [156];
  float local_a4;
  float fStack_a0;
  __thread_struct local_9c [4];
  float local_98;
  float fStack_94;
  __thread_struct **local_90;
  
  local_a4 = param_11;
  fStack_a0 = param_10;
  local_9c[0] = (__thread_struct)param_9;
  local_98 = param_8;
  fStack_94 = param_7;
  std::__ndk1::basic_ifstream<char,std::__ndk1::char_traits<char>>::basic_ifstream
            ((char *)local_1f8,(uint)param_3);
  local_208 = (void *)0x0;
  uStack_200 = 0;
  local_210 = (void *)0x0;
                    /* try { // try from 0010ce44 to 0010ce4f has its CatchHandler @ 0010d2b4 */
  std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>::
  __init_with_sentinel_abi_ne180000_<std::__ndk1::istreambuf_iterator<char,std::__ndk1::char_traits<char>>,std::__ndk1::istreambuf_iterator<char,std::__ndk1::char_traits<char>>>
            ((vector<unsigned_char,std::__ndk1::allocator<unsigned_char>> *)&local_210,
             (istreambuf_iterator)
             *(undefined8 *)((long)auStack_1d0 + *(long *)(local_1f8[0] + -0x18)),0);
  local_228 = (void *)0x0;
  local_220 = (void *)0x0;
  local_218 = 0;
                    /* try { // try from 0010ce58 to 0010ce6f has its CatchHandler @ 0010d28c */
  uVar3 = adaptiveShading((vector *)&local_210,param_4,param_5,param_6,&local_248);
  if ((uVar3 & 1) == 0) {
    uVar5 = 0;
  }
  else {
    local_24c[0] = (__thread_struct)(*(short *)((long)local_210 + 0x362) != 0);
    local_250[0] = (__thread_struct)(*(short *)((long)local_210 + 0x366) != 0);
                    /* try { // try from 0010ce9c to 0010ceaf has its CatchHandler @ 0010d284 */
    if ((*(short *)((long)local_210 + 0x362) == 0) ||
       (uVar3 = adaptiveLut((vector *)&local_210,param_4,param_5,(vector *)&local_228),
       (uVar3 & 1) != 0)) {
      local_268 = 0;
      uStack_260 = 0;
      local_258 = 0;
      local_270 = 0;
                    /* try { // try from 0010cec0 to 0010cf03 has its CatchHandler @ 0010d288 */
      iVar2 = AndroidBitmap_getInfo(param_1,param_2,&local_268);
      if (((iVar2 == 0) &&
          (((uStack_260._4_4_ == 1 && ((int)local_268 != 0)) && (local_268._4_4_ != 0)))) &&
         ((iVar2 = AndroidBitmap_lockPixels(param_1,param_2,&local_270), iVar2 == 0 &&
          (local_270 != 0)))) {
        local_2d0 = &local_268;
        plStack_2c8 = &local_270;
        local_2c0 = local_24c;
        ppvStack_2b8 = &local_228;
        local_2b0 = local_9c;
        pfStack_2a8 = &local_98;
        local_2a0 = &fStack_a0;
        pfStack_298 = &local_a4;
        local_290 = local_250;
        pfStack_288 = &local_248;
        local_280 = &fStack_94;
        ppvStack_278 = &local_210;
        if ((local_268 >> 0x20) * (local_268 & 0xffffffff) < 0x100000) {
          applyLeicaFilter(_JNIEnv*,_jobject*,char_const*,float,float,float,float,float,bool,float,float)
          ::$_0::operator()((uint)&local_2d0,0);
        }
        else {
          lVar6 = 0;
          local_2e8[0] = 0;
          local_2e8[1] = 0;
          local_2e8[2] = 0;
          do {
            uVar3 = local_268 >> 0x20;
                    /* try { // try from 0010cfb0 to 0010cfb7 has its CatchHandler @ 0010d074 */
            this = (__thread_struct *)operator_new(8);
                    /* try { // try from 0010cfb8 to 0010cfbf has its CatchHandler @ 0010d05c */
            std::__ndk1::__thread_struct::__thread_struct(this);
                    /* try { // try from 0010cfc4 to 0010cfcb has its CatchHandler @ 0010d050 */
            local_90 = (__thread_struct **)operator_new(0x70);
            *local_90 = this;
            local_90[6] = (__thread_struct *)pfStack_2a8;
            local_90[5] = local_2b0;
            local_90[8] = (__thread_struct *)pfStack_298;
            local_90[7] = (__thread_struct *)local_2a0;
            *(int *)(local_90 + 0xd) = (int)(uVar3 + uVar3 * lVar6 >> 2);
            *(int *)((long)local_90 + 0x6c) = (int)((lVar6 + 2) * uVar3 >> 2);
            local_90[10] = (__thread_struct *)pfStack_288;
            local_90[9] = local_290;
            local_90[0xc] = (__thread_struct *)ppvStack_278;
            local_90[0xb] = (__thread_struct *)local_280;
            local_90[2] = (__thread_struct *)plStack_2c8;
            local_90[1] = (__thread_struct *)local_2d0;
            local_90[4] = (__thread_struct *)ppvStack_2b8;
            local_90[3] = local_2c0;
                    /* try { // try from 0010d004 to 0010d04b has its CatchHandler @ 0010d080 */
            iVar2 = pthread_create(&local_2f0,(pthread_attr_t *)0x0,
                                   std::__ndk1::
                                   __thread_proxy_abi_ne180000_<std::__ndk1::tuple<std::__ndk1::unique_ptr<std::__ndk1::__thread_struct,std::__ndk1::default_delete<std::__ndk1::__thread_struct>>,(anonymous_namespace)::applyLeicaFilter(_JNIEnv*,_jobject*,char_const*,float,float,float,float,float,bool,float,float)::__0,unsigned_int,unsigned_int>>
                                   ,local_90);
            pVar1 = local_2f0;
            if (iVar2 != 0) {
              uVar4 = std::__ndk1::__throw_system_error(iVar2,"thread constructor failed");
                    /* catch() { ... } // from try @ 0010d0b8 with catch @ 0010d258 */
                    /* catch() { ... } // from try @ 0010d188 with catch @ 0010d25c */
              std::__ndk1::thread::~thread((thread *)(local_2e8 + 2));
              std::__ndk1::thread::~thread((thread *)(local_2e8 + 1));
              std::__ndk1::thread::~thread((thread *)local_2e8);
              if (local_228 != (void *)0x0) {
                local_220 = local_228;
                operator_delete(local_228);
              }
              if (local_210 != (void *)0x0) {
                local_208 = local_210;
                operator_delete(local_210);
              }
              std::__ndk1::basic_ifstream<char,std::__ndk1::char_traits<char>>::~basic_ifstream
                        ((basic_ifstream<char,std::__ndk1::char_traits<char>> *)local_1f8);
                    /* WARNING: Subroutine does not return */
              _Unwind_Resume(uVar4);
            }
            if (local_2e8[lVar6] != 0) {
                    /* WARNING: Subroutine does not return */
              std::terminate();
            }
            local_2f0 = 0;
            local_2e8[lVar6] = pVar1;
            std::__ndk1::thread::~thread((thread *)&local_2f0);
            lVar6 = lVar6 + 1;
          } while (lVar6 != 3);
          applyLeicaFilter(_JNIEnv*,_jobject*,char_const*,float,float,float,float,float,bool,float,float)
          ::$_0::operator()((uint)&local_2d0,0);
          if (local_2e8[0] != 0) {
                    /* try { // try from 0010d188 to 0010d1b3 has its CatchHandler @ 0010d25c */
            std::__ndk1::thread::join();
          }
          if (local_2e8[1] != 0) {
            std::__ndk1::thread::join();
          }
          if (local_2e8[2] != 0) {
            std::__ndk1::thread::join();
          }
          std::__ndk1::thread::~thread((thread *)(local_2e8 + 2));
          std::__ndk1::thread::~thread((thread *)(local_2e8 + 1));
          std::__ndk1::thread::~thread((thread *)local_2e8);
        }
                    /* try { // try from 0010d1d0 to 0010d243 has its CatchHandler @ 0010d280 */
        AndroidBitmap_unlockPixels(param_1,param_2);
        __android_log_print((double)param_6,(double)param_4,(double)param_5,(double)local_248,
                            (double)fStack_244,(double)local_240,(double)fStack_23c,
                            (double)local_238,4,"LeicaNative",
                            "Original filter warm=%d LUT=%d shading=%d zoom=%.2f lux=%.1f cct=%.0f params=%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f"
                            ,local_9c[0],local_24c[0],local_250[0],in_x6,in_x7,(double)fStack_234,
                            (double)local_230,(double)fStack_22c);
        uVar5 = 1;
        goto joined_r0x0010d0c8;
      }
    }
    uVar5 = 0;
  }
joined_r0x0010d0c8:
  if (local_228 != (void *)0x0) {
    local_220 = local_228;
    operator_delete(local_228);
  }
  if (local_210 != (void *)0x0) {
    local_208 = local_210;
    operator_delete(local_210);
  }
  local_1f8[0] = *(long *)PTR_VTT_00120dc0;
  *(undefined8 *)((long)local_1f8 + *(long *)(local_1f8[0] + -0x18)) =
       *(undefined8 *)(PTR_VTT_00120dc0 + 0x18);
  std::__ndk1::basic_filebuf<char,std::__ndk1::char_traits<char>>::~basic_filebuf(abStack_1e8);
  std::__ndk1::basic_istream<char,std::__ndk1::char_traits<char>>::~basic_istream
            ((basic_istream<char,std::__ndk1::char_traits<char>> *)local_1f8);
  std::__ndk1::basic_ios<char,std::__ndk1::char_traits<char>>::~basic_ios(abStack_140);
  return uVar5;
}



/* 0010d2c8 Java_com_codex_lmoments_LegendaryPostProcessor_applyBoldOriginalFilter */

char * Java_com_codex_lmoments_LegendaryPostProcessor_applyBoldOriginalFilter
                 (float param_1,float param_2,float param_3,float param_4,float param_5,
                 long *param_6,undefined8 param_7,_jobject *param_8,long param_9)

{
  uint uVar1;
  char *pcVar2;
  float fVar3;
  float fVar4;
  
  pcVar2 = (char *)0x0;
  if (((param_8 != (_jobject *)0x0) && (param_9 != 0)) &&
     (pcVar2 = (char *)(**(code **)(*param_6 + 0x548))(param_6,param_9,0), pcVar2 != (char *)0x0)) {
    fVar4 = 1.0;
    if (param_5 <= 1.0) {
      fVar4 = param_5;
    }
    fVar3 = 0.0;
    if (0.0 <= param_5) {
      fVar3 = fVar4;
    }
    fVar4 = 0.6;
    if (ABS(param_5) != INFINITY) {
      fVar4 = fVar3;
    }
    uVar1 = (anonymous_namespace)::applyLeicaFilter
                      ((_JNIEnv *)param_6,param_8,pcVar2,param_1,param_2,param_3,param_4,fVar4,false
                       ,-0.35,0.025);
    (**(code **)(*param_6 + 0x550))(param_6,param_9,pcVar2);
    pcVar2 = (char *)(ulong)(uVar1 & 1);
  }
  return pcVar2;
}



/* 0010d3e4 Java_com_codex_lmoments_LegendaryPostProcessor_applyWarmOriginalFilter */

char * Java_com_codex_lmoments_LegendaryPostProcessor_applyWarmOriginalFilter
                 (float param_1,float param_2,float param_3,float param_4,float param_5,
                 float param_6,float param_7,long *param_8,undefined8 param_9,_jobject *param_10,
                 long param_11)

{
  uint uVar1;
  char *pcVar2;
  
  pcVar2 = (char *)0x0;
  if (((param_10 != (_jobject *)0x0) && (param_11 != 0)) &&
     (pcVar2 = (char *)(**(code **)(*param_8 + 0x548))(param_8,param_11,0), pcVar2 != (char *)0x0))
  {
    uVar1 = (anonymous_namespace)::applyLeicaFilter
                      ((_JNIEnv *)param_8,param_10,pcVar2,param_1,param_2,param_3,param_4,param_5,
                       true,param_6,param_7);
    (**(code **)(*param_8 + 0x550))(param_8,param_11,pcVar2);
    pcVar2 = (char *)(ulong)(uVar1 & 1);
  }
  return pcVar2;
}



/* 0010d4c8 Java_com_codex_lmoments_LegendaryPostProcessor_previewShading */

long Java_com_codex_lmoments_LegendaryPostProcessor_previewShading
               (float param_1,float param_2,float param_3,long *param_4,undefined8 param_5,
               long param_6)

{
  char *pcVar1;
  vector *pvVar2;
  ulong uVar3;
  long lVar4;
  float afStack_70 [8];
  
  if (param_6 != 0) {
    pcVar1 = (char *)(**(code **)(*param_4 + 0x548))(param_4,param_6,0);
    if (pcVar1 == (char *)0x0) {
      return 0;
    }
                    /* try { // try from 0010d514 to 0010d52f has its CatchHandler @ 0010d594 */
    pvVar2 = (vector *)previewModel(pcVar1);
    uVar3 = adaptiveShading(pvVar2,param_1,param_2,param_3,afStack_70);
    (**(code **)(*param_4 + 0x550))(param_4,param_6,pcVar1);
    if ((uVar3 & 1) != 0) {
      lVar4 = (**(code **)(*param_4 + 0x5a8))(param_4,8);
      if (lVar4 == 0) {
        return 0;
      }
      (**(code **)(*param_4 + 0x6a8))(param_4,lVar4,0,8,afStack_70);
      return lVar4;
    }
  }
  return 0;
}



/* 0010d620 adaptiveShading */

/* adaptiveShading(std::__ndk1::vector<unsigned char, std::__ndk1::allocator<unsigned char> >
   const&, float, float, float, float*) */

bool adaptiveShading(vector *param_1,float param_2,float param_3,float param_4,float *param_5)

{
  float *pfVar1;
  short *psVar2;
  ushort uVar3;
  uint uVar4;
  bool bVar5;
  ulong uVar6;
  ulong uVar7;
  LeicaRange *pLVar8;
  LeicaRange *pLVar9;
  long lVar10;
  ulong uVar11;
  long lVar12;
  long lVar13;
  float fVar14;
  float fVar15;
  void *local_b8;
  void *local_b0;
  LeicaRange *local_a0;
  LeicaRange *local_98;
  undefined8 local_90;
  LeicaRange *local_88;
  LeicaRange *pLStack_80;
  undefined8 local_78;
  undefined8 local_38;
  
  psVar2 = *(short **)param_1;
  if ((((0xfff < (ulong)(*(long *)(param_1 + 8) - (long)psVar2)) && (*psVar2 == 6)) &&
      (psVar2[7] == 0x400)) && ((psVar2[8] == 0x1000 && (psVar2[9] == 0x11)))) {
    if (ABS(param_3) == INFINITY) {
      return false;
    }
    if (ABS(param_2) == INFINITY) {
      return false;
    }
    if (psVar2[10] != 5) {
      return false;
    }
    bVar5 = -1 < (int)param_4;
    uVar4 = ((uint)param_4 & 0x7fffffff) - 0x800000 >> 0x18;
    if (((bVar5 && uVar4 < 0x7e || bVar5 && uVar4 == 0x7e) || (int)param_4 - 1U < 0x7ffffe) ||
        ((!bVar5 || uVar4 >= 0x7e) && (!bVar5 || uVar4 != 0x7e)) && (int)param_4 - 1U == 0x7ffffe) {
      lVar13 = 0;
      local_38 = 0;
      uVar6 = 0x400;
      do {
        local_88 = (LeicaRange *)0x0;
        pLStack_80 = (LeicaRange *)0x0;
        local_78 = 0;
        uVar7 = *(ushort *)(*(long *)param_1 + lVar13 + 2) + uVar6;
        if (0x1000 < uVar7) {
          return false;
        }
                    /* try { // try from 0010d72c to 0010d743 has its CatchHandler @ 0010dba4 */
        uVar6 = leicaRanges(param_1,uVar6 + 0x40,uVar7,(vector *)&local_88,
                            (uint *)((long)&local_38 + 4));
        if (local_88 != (LeicaRange *)0x0) {
          std::__ndk1::vector<LeicaRange,std::__ndk1::allocator<LeicaRange>>::
          __base_destruct_at_end_abi_ne180000_
                    ((vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *)&local_88,local_88);
          operator_delete(local_88);
        }
        if ((uVar6 & 1) == 0) {
          return false;
        }
        lVar13 = lVar13 + 2;
        uVar6 = uVar7;
      } while (lVar13 != 0xc);
      lVar13 = 0;
      local_88 = (LeicaRange *)0x0;
      pLStack_80 = (LeicaRange *)0x0;
      local_78 = 0;
      fVar14 = 0.0;
      do {
        uVar3 = *(ushort *)(*(long *)param_1 + lVar13 + 0x16);
        local_a0 = (LeicaRange *)0x0;
        local_98 = (LeicaRange *)0x0;
        local_90 = 0;
        if (((uVar3 < 4) || (uVar6 = uVar7 + uVar3, 0x1000 < uVar6)) ||
           ((fVar15 = *(float *)(*(long *)param_1 + uVar7), ABS(fVar15) == INFINITY ||
            ((fVar15 <= fVar14 ||
             (uVar7 = leicaRanges(param_1,uVar7 + 4,uVar6,(vector *)&local_a0,(uint *)&local_38),
             (uVar7 & 1) == 0)))))) {
          std::__ndk1::vector<LeicaRange,std::__ndk1::allocator<LeicaRange>>::~vector_abi_ne180000_
                    ((vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *)&local_a0);
          goto LAB_0010d878;
        }
        if ((fVar15 <= param_4) || (local_88 == pLStack_80)) {
                    /* try { // try from 0010d7d0 to 0010d853 has its CatchHandler @ 0010db94 */
          std::__ndk1::vector<LeicaRange,std::__ndk1::allocator<LeicaRange>>::
          __assign_with_size_abi_ne180000_<LeicaRange*,LeicaRange*>
                    ((vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *)&local_88,local_a0,
                     local_98,((long)local_98 - (long)local_a0 >> 3) * -0x3333333333333333);
        }
        lVar13 = lVar13 + 2;
        std::__ndk1::vector<LeicaRange,std::__ndk1::allocator<LeicaRange>>::~vector_abi_ne180000_
                  ((vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *)&local_a0);
        uVar7 = uVar6;
        fVar14 = fVar15;
      } while (lVar13 != 10);
      lVar13 = (local_38 >> 0x20) * 0x3993 + 0x4993;
      if (lVar13 + (local_38 & 0xffffffff) * 0x20 + 0x20 ==
          *(long *)(param_1 + 8) - *(long *)param_1) {
        *(undefined8 *)(param_5 + 2) = 0;
        *(undefined8 *)param_5 = 0;
        *(undefined8 *)(param_5 + 6) = 0;
        *(undefined8 *)(param_5 + 4) = 0;
                    /* try { // try from 0010d8bc to 0010d8cb has its CatchHandler @ 0010db74 */
        leicaWeights((vector *)&local_88,param_2);
        if (pLStack_80 != local_88) {
          uVar6 = 0;
          pLVar8 = pLStack_80;
          pLVar9 = local_88;
          do {
            if (0.0 < *(float *)(local_a0 + uVar6 * 4)) {
                    /* try { // try from 0010d92c to 0010d93b has its CatchHandler @ 0010db78 */
              leicaWeights((vector *)(pLVar9 + uVar6 * 0x28 + 0x10),param_3);
              if ((long)local_b0 - (long)local_b8 == 0) {
                pLVar8 = pLStack_80;
                pLVar9 = local_88;
                if (local_b8 == (void *)0x0) goto LAB_0010d900;
              }
              else {
                uVar11 = (long)local_b0 - (long)local_b8 >> 2;
                lVar10 = *(long *)param_1;
                uVar7 = 0;
                lVar12 = 8;
                if (uVar11 < 2) {
                  uVar11 = 1;
                }
                do {
                  fVar14 = *(float *)((long)local_b8 + uVar7 * 4);
                  if (0.0 < fVar14) {
                    pfVar1 = (float *)(lVar10 + lVar13 +
                                      (ulong)(uint)(*(int *)(*(long *)(local_88 +
                                                                      uVar6 * 0x28 + 0x10) + lVar12)
                                                   << 5));
                    if (ABS(*pfVar1) != INFINITY) {
                      fVar14 = (float)NEON_fmadd(*(float *)(local_a0 + uVar6 * 4) * fVar14,*pfVar1,
                                                 *param_5);
                      *param_5 = fVar14;
                      if (ABS(pfVar1[1]) != INFINITY) {
                        fVar14 = (float)NEON_fmadd(*(float *)(local_a0 + uVar6 * 4) *
                                                   *(float *)((long)local_b8 + uVar7 * 4),pfVar1[1],
                                                   param_5[1]);
                        param_5[1] = fVar14;
                        if (ABS(pfVar1[2]) != INFINITY) {
                          fVar14 = (float)NEON_fmadd(*(float *)(local_a0 + uVar6 * 4) *
                                                     *(float *)((long)local_b8 + uVar7 * 4),
                                                     pfVar1[2],param_5[2]);
                          param_5[2] = fVar14;
                          if (ABS(pfVar1[3]) != INFINITY) {
                            fVar14 = (float)NEON_fmadd(*(float *)(local_a0 + uVar6 * 4) *
                                                       *(float *)((long)local_b8 + uVar7 * 4),
                                                       pfVar1[3],param_5[3]);
                            param_5[3] = fVar14;
                            if (ABS(pfVar1[4]) != INFINITY) {
                              fVar14 = (float)NEON_fmadd(*(float *)(local_a0 + uVar6 * 4) *
                                                         *(float *)((long)local_b8 + uVar7 * 4),
                                                         pfVar1[4],param_5[4]);
                              param_5[4] = fVar14;
                              if (ABS(pfVar1[5]) != INFINITY) {
                                fVar14 = (float)NEON_fmadd(*(float *)(local_a0 + uVar6 * 4) *
                                                           *(float *)((long)local_b8 + uVar7 * 4),
                                                           pfVar1[5],param_5[5]);
                                param_5[5] = fVar14;
                                if (ABS(pfVar1[6]) != INFINITY) {
                                  fVar14 = (float)NEON_fmadd(*(float *)(local_a0 + uVar6 * 4) *
                                                             *(float *)((long)local_b8 + uVar7 * 4),
                                                             pfVar1[6],param_5[6]);
                                  param_5[6] = fVar14;
                                  if (ABS(pfVar1[7]) != INFINITY) {
                                    fVar14 = (float)NEON_fmadd(*(float *)(local_a0 + uVar6 * 4) *
                                                               *(float *)((long)local_b8 + uVar7 * 4
                                                                         ),pfVar1[7],param_5[7]);
                                    param_5[7] = fVar14;
                                    goto LAB_0010dadc;
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                    operator_delete(local_b8);
                    bVar5 = false;
                    goto LAB_0010db60;
                  }
LAB_0010dadc:
                  uVar7 = uVar7 + 1;
                  lVar12 = lVar12 + 0x28;
                } while (uVar11 != uVar7);
              }
              local_b0 = local_b8;
              operator_delete(local_b8);
              pLVar8 = pLStack_80;
              pLVar9 = local_88;
            }
LAB_0010d900:
            uVar6 = uVar6 + 1;
          } while (uVar6 < (ulong)(((long)pLVar8 - (long)pLVar9 >> 3) * -0x3333333333333333));
        }
        if ((*param_5 <= param_5[1]) || (param_5[2] < 0.0)) {
          bVar5 = false;
        }
        else {
          bVar5 = 0.0 < param_5[3];
        }
LAB_0010db60:
        if (local_a0 != (LeicaRange *)0x0) {
          local_98 = local_a0;
          operator_delete(local_a0);
        }
      }
      else {
LAB_0010d878:
        bVar5 = false;
      }
      std::__ndk1::vector<LeicaRange,std::__ndk1::allocator<LeicaRange>>::~vector_abi_ne180000_
                ((vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *)&local_88);
      return bVar5;
    }
  }
  return false;
}



/* 0010dbb8 Java_com_codex_lmoments_SoftwareRaw_render */

undefined8
Java_com_codex_lmoments_SoftwareRaw_render
          (long *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,uint param_5,
          vector *param_6,undefined4 param_7,undefined8 param_8,undefined8 param_9,int param_10,
          uint param_11,undefined8 param_12,char param_13,long param_14,undefined8 param_15)

{
  byte *pbVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  vector *pvVar6;
  undefined8 uVar7;
  long lVar8;
  ulong uVar9;
  ulong uVar10;
  ulong uVar11;
  ulong uVar12;
  ulong uVar13;
  float fVar14;
  float fVar15;
  undefined4 uVar16;
  float fVar17;
  undefined4 uVar18;
  undefined4 uVar19;
  float fVar20;
  float fVar21;
  undefined8 uVar22;
  float fVar23;
  void *local_220;
  void *local_208;
  void *local_200;
  void *local_1f0;
  void *local_1e8;
  undefined8 local_1e0;
  long local_1d8;
  undefined8 local_1d0;
  undefined8 local_1c8;
  undefined4 local_1c0;
  software_raw *local_1b8;
  software_raw *local_1b0;
  undefined4 local_1a0;
  undefined8 local_19c;
  undefined8 uStack_194;
  undefined8 local_18c;
  undefined8 uStack_184;
  undefined8 local_17c;
  undefined8 uStack_174;
  undefined8 local_16c;
  undefined8 uStack_164;
  undefined4 local_15c;
  undefined8 local_158;
  undefined8 uStack_150;
  undefined8 local_148;
  undefined8 uStack_140;
  uint local_138;
  int iStack_134;
  undefined4 local_130;
  int iStack_12c;
  ulong local_128;
  undefined8 uStack_120;
  undefined8 local_118;
  undefined8 uStack_110;
  undefined8 local_108;
  undefined8 uStack_100;
  undefined8 local_f8;
  undefined8 uStack_f0;
  undefined8 local_e8;
  undefined4 uStack_e0;
  undefined4 uStack_dc;
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  undefined4 uStack_d0;
  undefined4 local_cc;
  undefined4 uStack_c8;
  undefined8 uStack_c4;
  long local_b8;
  long lStack_b0;
  undefined8 local_a8;
  undefined8 uStack_a0;
  undefined8 local_98;
  undefined8 uStack_90;
  long local_88;
  undefined8 local_80;
  undefined8 local_78;
  undefined4 local_70;
  
  local_80 = 0;
  local_78 = 0;
  local_70 = 0;
  local_88 = 0;
  if (param_5 - 0x2001 < 0xffffe007) {
    return 0;
  }
  iVar5 = (int)param_6;
  if (iVar5 - 0x2001U < 0xffffe007) {
    return 0;
  }
  uVar9 = (ulong)param_5;
  pvVar6 = param_6;
  iVar3 = (**(code **)(*param_1 + 0x558))(param_1,param_4);
  uVar10 = ((ulong)param_6 & 0xffffffff) * uVar9;
  if ((long)iVar3 != uVar10 * 2) {
    return 0;
  }
  iVar3 = (**(code **)(*param_1 + 0x558))(param_1,param_8);
  if (0x80 < (int)param_11) {
    return 0;
  }
  if (0x80 < param_10) {
    return 0;
  }
  if ((int)param_11 < 1) {
    return 0;
  }
  if (param_10 < 1) {
    return 0;
  }
  if (iVar3 != 0x1a) {
    return 0;
  }
  uVar4 = (**(code **)(*param_1 + 0x558))(param_1);
  if (uVar4 != param_10 * param_11 * 4) {
    return 0;
  }
  iVar3 = (**(code **)(*param_1 + 0x558))(param_1);
  if (iVar3 != 0xc00) {
    return 0;
  }
  iVar3 = AndroidBitmap_getInfo(param_1,param_3,&local_80);
  if (iVar3 != 0) {
    return 0;
  }
  if ((uint)local_80 != param_5) {
    return 0;
  }
  if (local_80._4_4_ != iVar5) {
    return 0;
  }
  if (local_78._4_4_ != 1) {
    return 0;
  }
  iStack_12c = param_10;
  uStack_120 = 0;
  uStack_c4 = 0;
  uStack_c8 = 0;
  uStack_d0 = 0;
  local_cc = 0;
  uStack_d8 = 0;
  uStack_d4 = 0;
  uStack_e0 = 0;
  uStack_dc = 0;
  local_e8 = 0;
  uStack_f0 = 0;
  local_f8 = 0;
  uStack_100 = 0;
  local_108 = 0;
  uStack_110 = 0;
  local_118 = 0;
  lStack_b0 = 0;
  local_b8 = 0;
  uStack_a0 = 0;
  local_a8 = 0;
  uStack_90 = 0;
  local_98 = 0;
  local_128 = (ulong)param_11;
                    /* try { // try from 0010dd68 to 0010de27 has its CatchHandler @ 0010e27c */
  local_138 = param_5;
  iStack_134 = iVar5;
  local_130 = param_7;
  (**(code **)(*param_1 + 0x668))(param_1,param_8,0,0x1a,&local_1a0);
  local_128 = CONCAT44(local_1a0,(undefined4)local_128);
  local_118 = uStack_194;
  uStack_120 = local_19c;
  local_108 = uStack_184;
  uStack_110 = local_18c;
  local_f8 = uStack_174;
  uStack_100 = local_17c;
  local_e8 = uStack_164;
  uStack_f0 = local_16c;
  uStack_d4 = (undefined4)uStack_150;
  uStack_d0 = (undefined4)((ulong)uStack_150 >> 0x20);
  uStack_dc = (undefined4)local_158;
  uStack_d8 = (undefined4)((ulong)local_158 >> 0x20);
  uStack_e0 = local_15c;
  uStack_c4 = uStack_140;
  local_cc = (undefined4)local_148;
  uStack_c8 = (undefined4)((ulong)local_148 >> 0x20);
  std::__ndk1::vector<float,std::__ndk1::allocator<float>>::resize
            ((vector<float,std::__ndk1::allocator<float>> *)&local_b8,(ulong)uVar4);
  std::__ndk1::vector<float,std::__ndk1::allocator<float>>::resize
            ((vector<float,std::__ndk1::allocator<float>> *)&uStack_a0,0xc00);
  (**(code **)(*param_1 + 0x668))(param_1,param_9,0,(ulong)(lStack_b0 - local_b8) >> 2);
  (**(code **)(*param_1 + 0x668))(param_1,param_12,0,0xc00,uStack_a0);
                    /* try { // try from 0010de28 to 0010de33 has its CatchHandler @ 0010e23c */
  std::__ndk1::vector<unsigned_short,std::__ndk1::allocator<unsigned_short>>::vector
            ((vector<unsigned_short,std::__ndk1::allocator<unsigned_short>> *)&local_1b8,uVar10);
                    /* try { // try from 0010de48 to 0010de5b has its CatchHandler @ 0010e230 */
  (**(code **)(*param_1 + 0x640))(param_1,param_4,0,(int)local_1b0 - (int)local_1b8 & 0xfffffffe);
  local_1d0 = 0;
  local_1c8 = 0;
  local_1c0 = 0;
  local_1d8 = 0;
                    /* try { // try from 0010de74 to 0010de7f has its CatchHandler @ 0010e22c */
  iVar3 = (**(code **)(*param_1 + 0x558))(param_1,param_15);
  if (iVar3 != 4) {
    uVar7 = 0;
    goto LAB_0010e1d8;
  }
  local_1f0 = (void *)0x0;
  local_1e8 = (void *)0x0;
  local_1e0 = 0;
                    /* try { // try from 0010de90 to 0010de9b has its CatchHandler @ 0010e220 */
  std::__ndk1::vector<float,std::__ndk1::allocator<float>>::vector
            ((vector<float,std::__ndk1::allocator<float>> *)&local_208,4);
                    /* try { // try from 0010dea8 to 0010e0df has its CatchHandler @ 0010e240 */
  (**(code **)(*param_1 + 0x668))(param_1,param_15,0,4,local_208);
  if (param_14 == 0) {
LAB_0010e0e0:
                    /* try { // try from 0010e0ec to 0010e0ff has its CatchHandler @ 0010e1fc */
    software_raw::develop
              (local_1b8,(ushort *)&local_138,(Calibration *)(ulong)(param_13 != '\0'),
               SUB81(&local_1f0,0),(vector *)&local_208,pvVar6);
                    /* try { // try from 0010e100 to 0010e113 has its CatchHandler @ 0010e200 */
    iVar3 = AndroidBitmap_lockPixels(param_1,param_3,&local_88);
    if (iVar3 == 0) {
      if (0 < iVar5) {
        lVar8 = 0;
        uVar10 = 0;
        do {
          if (uVar9 != 0) {
            memmove((void *)(local_88 + uVar10 * (local_78 & 0xffffffff)),
                    (void *)((long)local_220 + lVar8),
                    (long)local_220 +
                    ((uVar9 * 4 + lVar8) - (long)(void *)((long)local_220 + lVar8)));
          }
          uVar10 = uVar10 + 1;
          lVar8 = lVar8 + uVar9 * 4;
        } while (((ulong)param_6 & 0xffffffff) != uVar10);
      }
                    /* try { // try from 0010e180 to 0010e18b has its CatchHandler @ 0010e200 */
      AndroidBitmap_unlockPixels(param_1,param_3);
      uVar7 = 1;
    }
    else {
      uVar7 = 0;
    }
    if (local_220 != (void *)0x0) {
      operator_delete(local_220);
    }
  }
  else {
    iVar3 = AndroidBitmap_getInfo(param_1,param_14,&local_1d0);
    uVar7 = 0;
    if ((iVar3 == 0) && (local_1c8._4_4_ == 1)) {
      iVar3 = AndroidBitmap_lockPixels(0,param_1,param_14,&local_1d8);
      if (iVar3 == 0) {
        uVar7 = std::__ndk1::vector<float,std::__ndk1::allocator<float>>::resize
                          ((vector<float,std::__ndk1::allocator<float>> *)&local_1f0,0x103);
        if (local_1d0._4_4_ != 0) {
          uVar7 = NEON_fmov(0x3f800000,4);
          uVar10 = 0;
          pvVar6 = (vector *)0x3dcccccd;
          do {
            if ((int)local_1d0 != 0) {
              uVar11 = 0;
              uVar12 = 0;
              do {
                pbVar1 = (byte *)(local_1d8 + (ulong)(uint)((int)local_1c8 * (int)uVar10) +
                                 (uVar11 & 0xffffffe0));
                fVar14 = (float)NEON_ucvtf((uint)pbVar1[1]);
                uVar16 = NEON_ucvtf((uint)*pbVar1);
                uVar19 = NEON_ucvtf((uint)pbVar1[2]);
                uVar18 = NEON_fmadd(uVar16,0x3e59b3d0,fVar14 * 0.7152);
                uVar16 = NEON_fmadd(uVar16,0x3e6a786c,fVar14 * 0.691739);
                fVar14 = (float)NEON_fmadd(uVar19,0x3d93dd98,uVar18);
                fVar15 = (float)NEON_fmadd(uVar19,0x3da26139,uVar16);
                if (param_13 != '\0') {
                  fVar14 = fVar15;
                }
                uVar4 = (uint)fVar14;
                if (0xfe < (int)uVar4) {
                  uVar4 = 0xff;
                }
                uVar13 = -(ulong)(uVar4 >> 0x1f) & 0xfffffffc00000000 | (ulong)uVar4 << 2;
                *(float *)((long)local_1f0 + uVar13) = *(float *)((long)local_1f0 + uVar13) + 1.0;
                fVar15 = (float)NEON_ucvtf((uint)*pbVar1);
                fVar17 = (float)NEON_ucvtf((uint)pbVar1[1]);
                fVar20 = (float)NEON_ucvtf((uint)pbVar1[2]);
                fVar15 = fVar15 / 255.0;
                fVar17 = fVar17 / 255.0;
                fVar20 = fVar20 / 255.0;
                fVar14 = fVar17;
                if (fVar15 <= fVar17) {
                  fVar14 = fVar15;
                }
                fVar21 = fVar20;
                if (fVar14 <= fVar20) {
                  fVar21 = fVar14;
                }
                fVar14 = fVar17;
                if (fVar17 <= fVar15) {
                  fVar14 = fVar15;
                }
                fVar23 = fVar20;
                if (fVar20 <= fVar14) {
                  fVar23 = fVar14;
                }
                bVar2 = 0.1 <= fVar21;
                if ((bVar2 && fVar23 == 0.9 || bVar2 && fVar23 < 0.9) && fVar23 - fVar21 == 0.2 ||
                    (bVar2 && fVar23 == 0.9 || bVar2 && fVar23 < 0.9) && fVar23 - fVar21 < 0.2) {
                  uVar22 = *(undefined8 *)((long)local_1f0 + 0x404);
                  *(undefined8 *)((long)local_1f0 + 0x404) =
                       CONCAT44((float)((ulong)uVar7 >> 0x20) + (float)((ulong)uVar22 >> 0x20),
                                fVar20 / fVar17 + (float)uVar22);
                  *(float *)((long)local_1f0 + 0x400) =
                       fVar15 / fVar17 + *(float *)((long)local_1f0 + 0x400);
                }
                uVar12 = uVar12 + 8;
                uVar11 = uVar11 + 0x20;
              } while (uVar12 < (local_1d0 & 0xffffffff));
            }
            uVar10 = uVar10 + 8;
          } while (uVar10 < local_1d0._4_4_);
        }
        AndroidBitmap_unlockPixels(uVar7,param_1,param_14);
        goto LAB_0010e0e0;
      }
      uVar7 = 0;
    }
  }
  if (local_208 != (void *)0x0) {
    local_200 = local_208;
    operator_delete(local_208);
  }
  if (local_1f0 != (void *)0x0) {
    local_1e8 = local_1f0;
    operator_delete(local_1f0);
  }
LAB_0010e1d8:
  if (local_1b8 != (software_raw *)0x0) {
    local_1b0 = local_1b8;
    operator_delete(local_1b8);
  }
  software_raw::Calibration::~Calibration((Calibration *)&local_138);
  return uVar7;
}



/* 0010e300 Java_com_codex_lmoments_SoftwareRaw_fuse */

long Java_com_codex_lmoments_SoftwareRaw_fuse
               (long *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,uint param_5,
               ulong param_6)

{
  size_t sVar1;
  void ***pppvVar2;
  void ***pppvVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  void **ppvVar7;
  void *pvVar8;
  long lVar9;
  long lVar10;
  void *pvVar11;
  int iVar12;
  int iVar13;
  undefined4 uVar14;
  void ***pppvVar15;
  ulong uVar16;
  ulong uVar17;
  void ***pppvVar18;
  ulong uVar19;
  ulong uVar20;
  ulong uVar21;
  void ***pppvVar22;
  ulong uVar23;
  void ***pppvVar24;
  long lVar25;
  ulong uVar26;
  long lVar27;
  void ***pppvVar28;
  void ***pppvVar29;
  void **ppvVar30;
  void **ppvVar31;
  int local_d8;
  undefined4 uStack_d4;
  int local_d0;
  undefined4 local_c0 [2];
  undefined8 local_b8;
  void *local_b0;
  void *local_a8;
  void *local_a0;
  void ***local_98;
  void ***local_90;
  void ***local_88;
  void **local_80;
  void **local_78;
  void **local_70;
  
  uVar14 = (undefined4)(param_6 >> 0x20);
  iVar12 = (int)param_6;
  iVar13 = iVar12;
                    /* try { // try from 0010e33c to 0010e36f has its CatchHandler @ 0010e8f0 */
  uVar4 = (**(code **)(*param_1 + 0x558))(param_1,param_3);
  if (uVar4 - 6 < 0xfffffffc) {
    lVar27 = 0;
  }
  else {
    uVar5 = (**(code **)(*param_1 + 0x558))(param_1,param_4);
    lVar27 = 0;
    if ((((iVar12 < 0x2001) && ((int)param_5 < 0x2001)) && (0x1f < iVar12)) &&
       ((0x1f < (int)param_5 && (uVar5 == uVar4)))) {
      uVar16 = (ulong)uVar4;
      local_98 = &local_80;
      local_80 = (void **)0x0;
      local_78 = (void **)0x0;
      uVar26 = (uVar16 + (ulong)uVar4 * 2) * 8;
      local_70 = (void **)0x0;
      local_90 = (void ***)((ulong)local_90 & 0xffffffffffffff00);
                    /* try { // try from 0010e3c4 to 0010e3cb has its CatchHandler @ 0010e8d8 */
      ppvVar7 = (void **)operator_new(uVar26);
      lVar27 = uVar26 - 0x18;
      local_70 = ppvVar7 + uVar16 * 3;
      sVar1 = (lVar27 - (ulong)(byte)((char)lVar27 + (char)(((uint)lVar27 & 0xff) / 0x18) * -0x18))
              + 0x18;
      local_80 = ppvVar7;
      memset(ppvVar7,0,sVar1);
      local_78 = (void **)((long)ppvVar7 + sVar1);
      local_98 = (void ***)0x0;
      local_90 = (void ***)0x0;
      local_88 = (void ***)0x0;
                    /* try { // try from 0010e428 to 0010e42f has its CatchHandler @ 0010e8cc */
      pvVar8 = operator_new(uVar16 * 0x38);
      lVar27 = uVar16 * 0x38 - 0x38;
      local_a0 = (void *)((long)pvVar8 + uVar16 * 0x38);
      sVar1 = (lVar27 - (ulong)(byte)((char)lVar27 + (char)(((uint)lVar27 >> 3 & 0x1f) / 7) * -0x38)
              ) + 0x38;
      local_b0 = pvVar8;
      memset(pvVar8,0,sVar1);
      uVar26 = 0;
      uVar17 = (param_6 & 0xffffffff) * (ulong)param_5;
      local_a8 = (void *)((long)pvVar8 + sVar1);
      do {
                    /* try { // try from 0010e4a0 to 0010e4af has its CatchHandler @ 0010e900 */
        lVar9 = (**(code **)(*param_1 + 0x568))(param_1,param_3,uVar26 & 0xffffffff);
                    /* try { // try from 0010e4bc to 0010e5ab has its CatchHandler @ 0010e904 */
        lVar10 = (**(code **)(*param_1 + 0x568))(param_1,param_4,uVar26 & 0xffffffff);
        lVar27 = 0;
        if ((lVar9 == 0) || (lVar10 == 0)) goto LAB_0010e80c;
        iVar6 = (**(code **)(*param_1 + 0x558))(param_1,lVar9);
        if ((uVar17 * 2 != (long)iVar6) ||
           (iVar6 = (**(code **)(*param_1 + 0x558))(param_1,lVar10), iVar6 != 0xe)) {
          lVar27 = 0;
          goto LAB_0010e80c;
        }
        ppvVar7 = local_80 + uVar26 * 3;
        pvVar11 = *ppvVar7;
        pvVar8 = ppvVar7[1];
        uVar19 = (long)pvVar8 - (long)pvVar11 >> 1;
        if (uVar17 < uVar19 || uVar17 - uVar19 == 0) {
          if (uVar17 < uVar19) {
            pvVar8 = (void *)((long)pvVar11 + uVar17 * 2);
            ppvVar7[1] = pvVar8;
          }
        }
        else {
          std::__ndk1::vector<unsigned_short,std::__ndk1::allocator<unsigned_short>>::__append
                    ((vector<unsigned_short,std::__ndk1::allocator<unsigned_short>> *)ppvVar7,
                     uVar17 - uVar19);
          pvVar11 = local_80[uVar26 * 3];
          pvVar8 = (local_80 + uVar26 * 3)[1];
        }
        (**(code **)(*param_1 + 0x640))(param_1,lVar9,0,(int)pvVar8 - (int)pvVar11 & 0xfffffffe);
        (**(code **)(*param_1 + 0x668))
                  (param_1,lVar10,0,0xe,(void *)((long)local_b0 + uVar26 * 0x38));
        pppvVar28 = local_90;
        pppvVar3 = local_98;
        ppvVar7 = (void **)local_80[uVar26 * 3];
        if (local_90 < local_88) {
          pppvVar24 = local_90 + 1;
          *local_90 = ppvVar7;
        }
        else {
          lVar25 = (long)local_90 - (long)local_98;
          lVar27 = lVar25 >> 3;
          uVar19 = lVar27 + 1;
          if (uVar19 >> 0x3d != 0) {
                    /* try { // try from 0010e89c to 0010e8a7 has its CatchHandler @ 0010e8fc */
            std::__ndk1::vector<unsigned_short_const*,std::__ndk1::allocator<unsigned_short_const*>>
            ::__throw_length_error_abi_ne180000_();
LAB_0010e8a4:
                    /* WARNING: Subroutine does not return */
            std::__throw_bad_array_new_length_abi_ne180000_();
          }
          uVar20 = (long)local_88 - (long)local_98 >> 2;
          if (uVar20 <= uVar19) {
            uVar20 = uVar19;
          }
          if (0x7ffffffffffffff7 < (ulong)((long)local_88 - (long)local_98)) {
            uVar20 = 0x1fffffffffffffff;
          }
          if (uVar20 == 0) {
            pvVar8 = (void *)0x0;
          }
          else {
            if (uVar20 >> 0x3d != 0) goto LAB_0010e8a4;
                    /* try { // try from 0010e62c to 0010e62f has its CatchHandler @ 0010e8ec */
            pvVar8 = operator_new(uVar20 << 3);
          }
          pppvVar15 = (void ***)((long)pvVar8 + lVar27 * 8);
          lVar27 = (long)pppvVar28 - (long)pppvVar3;
          pppvVar24 = pppvVar15 + 1;
          *pppvVar15 = ppvVar7;
          pppvVar18 = pppvVar15;
          pppvVar29 = pppvVar28;
          if (lVar27 != 0) {
            uVar19 = lVar27 - 8;
            pppvVar29 = local_98;
            if ((0x37 < uVar19) && (0x1f < (ulong)((long)pppvVar28 + (-lVar25 - (long)pvVar8)))) {
              pppvVar22 = pppvVar28 + -2;
              uVar19 = (uVar19 >> 3) + 1;
              uVar21 = uVar19 & 0x3ffffffffffffffc;
              pppvVar28 = pppvVar28 + -uVar21;
              pppvVar18 = pppvVar15 + -uVar21;
              pppvVar15 = pppvVar15 + -2;
              uVar23 = uVar21;
              do {
                pppvVar2 = pppvVar22 + -1;
                ppvVar31 = pppvVar22[-2];
                ppvVar30 = pppvVar22[1];
                ppvVar7 = *pppvVar22;
                uVar23 = uVar23 - 4;
                pppvVar22 = pppvVar22 + -4;
                pppvVar15[-1] = *pppvVar2;
                pppvVar15[-2] = ppvVar31;
                pppvVar15[1] = ppvVar30;
                *pppvVar15 = ppvVar7;
                pppvVar15 = pppvVar15 + -4;
              } while (uVar23 != 0);
              pppvVar15 = pppvVar18;
              if (uVar19 == uVar21) goto LAB_0010e708;
            }
            do {
              pppvVar28 = pppvVar28 + -1;
              pppvVar18 = pppvVar15 + -1;
              *pppvVar18 = *pppvVar28;
              pppvVar15 = pppvVar18;
            } while (pppvVar28 != pppvVar3);
          }
LAB_0010e708:
          local_88 = (void ***)((long)pvVar8 + uVar20 * 8);
          local_98 = pppvVar18;
          if (pppvVar29 != (void ***)0x0) {
            local_90 = pppvVar24;
            operator_delete(pppvVar29);
          }
        }
        local_90 = pppvVar24;
                    /* try { // try from 0010e730 to 0010e74f has its CatchHandler @ 0010e904 */
        (**(code **)(*param_1 + 0xb8))(param_1,lVar9);
        (**(code **)(*param_1 + 0xb8))(param_1,lVar10);
        uVar26 = uVar26 + 1;
      } while (uVar26 != uVar16);
      local_b8 = 0;
      local_c0[0] = 1;
                    /* try { // try from 0010e768 to 0010e77f has its CatchHandler @ 0010e8ac */
      raw_fusion::fuse((raw_fusion *)&local_98,(vector *)&local_b0,(vector *)(ulong)param_5,iVar12,
                       (int)local_c0,(Stats *)CONCAT44(uVar14,iVar13));
                    /* try { // try from 0010e788 to 0010e7a3 has its CatchHandler @ 0010e8a8 */
      __android_log_print(local_b8,4,"LeicaRaw","fusion frames=%d/%d accepted=%.3f",local_c0[0],
                          uVar4);
                    /* try { // try from 0010e7b8 to 0010e7f3 has its CatchHandler @ 0010e8b0 */
      lVar27 = (**(code **)(*param_1 + 0x580))(param_1,local_d0 - local_d8 & 0xfffffffe);
      if (lVar27 != 0) {
        (**(code **)(*param_1 + 0x680))(param_1,lVar27,0,local_d0 - local_d8 & 0xfffffffe);
      }
      if ((void *)CONCAT44(uStack_d4,local_d8) != (void *)0x0) {
        operator_delete((void *)CONCAT44(uStack_d4,local_d8));
      }
LAB_0010e80c:
      if (local_b0 != (void *)0x0) {
        local_a8 = local_b0;
        operator_delete(local_b0);
      }
      if (local_98 != (void ***)0x0) {
        local_90 = local_98;
        operator_delete(local_98);
      }
      ppvVar7 = local_80;
      ppvVar30 = local_78;
      if (local_80 != (void **)0x0) {
        while (ppvVar31 = ppvVar30, ppvVar31 != ppvVar7) {
          ppvVar30 = ppvVar31 + -3;
          pvVar8 = *ppvVar30;
          if (pvVar8 != (void *)0x0) {
            ppvVar31[-2] = pvVar8;
            operator_delete(pvVar8);
          }
        }
        local_78 = ppvVar7;
        operator_delete(local_80);
      }
    }
  }
  return lVar27;
}



/* 0010e988 Java_com_codex_lmoments_LegendaryPostProcessor_protectShadows */

undefined4
Java_com_codex_lmoments_LegendaryPostProcessor_protectShadows
          (undefined8 param_1,undefined8 param_2,long param_3,long param_4,char param_5)

{
  byte *pbVar1;
  byte *pbVar2;
  int iVar3;
  uint uVar4;
  ulong uVar5;
  ulong uVar6;
  undefined4 uVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  long local_70;
  long local_68;
  undefined8 local_60;
  undefined8 local_58;
  undefined4 local_50;
  undefined8 local_48;
  undefined8 local_40;
  undefined4 local_38;
  
  local_48 = 0;
  local_40 = 0;
  local_38 = 0;
  local_60 = 0;
  local_58 = 0;
  local_50 = 0;
  if (((param_3 != 0) && (param_4 != 0)) &&
     (iVar3 = AndroidBitmap_getInfo(param_1,param_3,&local_48), iVar3 == 0)) {
    iVar3 = AndroidBitmap_getInfo(param_1,param_4,&local_60);
    if (iVar3 != 0) {
      return 0;
    }
    if (local_40._4_4_ != 1) {
      return 0;
    }
    if (local_58._4_4_ != 1) {
      return 0;
    }
    if ((int)local_48 == (int)local_60) {
      if (local_48._4_4_ == local_60._4_4_) {
        local_70 = 0;
        local_68 = 0;
        iVar3 = AndroidBitmap_lockPixels(param_1,param_3,&local_68);
        if (iVar3 == 0) {
          iVar3 = AndroidBitmap_lockPixels(param_1,param_4,&local_70);
          if (iVar3 == 0) {
            if (local_48._4_4_ != 0) {
              uVar4 = 0;
              do {
                if ((int)local_48 != 0) {
                  uVar5 = 0;
                  uVar6 = 0;
                  do {
                    pbVar1 = (byte *)(local_70 + (uVar5 & 0xfffffffc) +
                                     (ulong)((int)local_58 * uVar4));
                    fVar8 = (float)((uint)*pbVar1 * 0x36 + (uint)pbVar1[1] * 0xb7 +
                                   (uint)pbVar1[2] * 0x13) / 256.0;
                    pbVar2 = (byte *)(local_68 + (uVar5 & 0xfffffffc) +
                                     (ulong)((int)local_40 * uVar4));
                    fVar11 = (float)(ulong)(uint)*pbVar1;
                    if (param_5 != '\0') {
                      fVar11 = fVar8;
                    }
                    fVar12 = (float)NEON_ucvtf((uint)*pbVar2);
                    fVar9 = (float)NEON_fminnm((128.0 - fVar8) / 96.0,0x3f800000);
                    if (fVar9 <= 0.0) {
                      fVar9 = 0.0;
                    }
                    fVar10 = (float)NEON_fmadd(fVar9,0xc0000000,0x40400000);
                    fVar10 = fVar10 * fVar9 * fVar9 * 0.85;
                    fVar11 = (float)NEON_fmadd(fVar11 - fVar12,fVar10,fVar12);
                    *pbVar2 = (byte)(long)fVar11;
                    fVar11 = fVar8;
                    if (param_5 == '\0') {
                      fVar11 = (float)NEON_ucvtf((uint)pbVar1[1]);
                    }
                    fVar9 = (float)NEON_ucvtf((uint)pbVar2[1]);
                    fVar11 = (float)NEON_fmadd(fVar11 - fVar9,fVar10,fVar9);
                    pbVar2[1] = (byte)(long)fVar11;
                    if (param_5 == '\0') {
                      fVar8 = (float)NEON_ucvtf((uint)pbVar1[2]);
                    }
                    uVar6 = uVar6 + 1;
                    uVar5 = uVar5 + 4;
                    fVar11 = (float)NEON_fmadd(fVar8 - (float)(ulong)pbVar2[2],fVar10,
                                               (float)(ulong)pbVar2[2]);
                    pbVar2[2] = (byte)(long)fVar11;
                  } while (uVar6 < (local_48 & 0xffffffff));
                }
                uVar4 = uVar4 + 1;
              } while (uVar4 < local_48._4_4_);
            }
            AndroidBitmap_unlockPixels(param_1,param_4);
            uVar7 = 1;
          }
          else {
            uVar7 = 0;
          }
          AndroidBitmap_unlockPixels(param_1,param_3);
          return uVar7;
        }
      }
    }
  }
  return 0;
}



/* 0010ec00 sampleLut */

/* (anonymous namespace)::sampleLut(std::__ndk1::vector<unsigned char,
   std::__ndk1::allocator<unsigned char> > const&, int, int, int) */

undefined4 (anonymous_namespace)::sampleLut(vector *param_1,int param_2,int param_3,int param_4)

{
  byte *pbVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte *pbVar4;
  byte *pbVar5;
  byte *pbVar6;
  byte *pbVar7;
  byte *pbVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  long lVar12;
  long lVar13;
  int iVar14;
  long lVar15;
  long lVar16;
  long lVar17;
  long lVar18;
  long lVar19;
  float fVar20;
  undefined4 uVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  float fVar35;
  float fVar36;
  float fVar37;
  float fVar38;
  float fVar39;
  float fVar40;
  float fVar41;
  float fVar42;
  float fVar43;
  float fVar44;
  float fVar45;
  float fVar46;
  float fVar47;
  
  fVar20 = ((float)param_2 * 16.0) / 255.0;
  fVar22 = ((float)param_3 * 16.0) / 255.0;
  iVar11 = (int)fVar20;
  iVar9 = iVar11;
  if (0xe < iVar11) {
    iVar9 = 0xf;
  }
  fVar23 = ((float)param_4 * 16.0) / 255.0;
  iVar14 = (int)fVar22;
  iVar10 = iVar14;
  if (0xe < iVar14) {
    iVar10 = 0xf;
  }
  lVar15 = (long)iVar14 + (long)iVar14 * 0x10;
  lVar19 = lVar15 + (long)(iVar9 + 1) * 0x121;
  lVar15 = lVar15 + (long)iVar11 * 0x121;
  lVar16 = *(long *)param_1;
  lVar13 = (long)(iVar10 + 1) + (long)(iVar10 + 1) * 0x10;
  lVar12 = lVar13 + (long)iVar11 * 0x121;
  iVar11 = (int)fVar23;
  lVar13 = lVar13 + (long)(iVar9 + 1) * 0x121;
  iVar9 = iVar11;
  if (0xe < iVar11) {
    iVar9 = 0xf;
  }
  lVar17 = (long)iVar11;
  lVar18 = (long)(iVar9 + 1);
  fVar23 = fVar23 - (float)(int)fVar23;
  pbVar1 = (byte *)(lVar16 + (lVar19 + lVar17) * 3);
  pbVar2 = (byte *)(lVar16 + (lVar15 + lVar17) * 3);
  pbVar3 = (byte *)(lVar16 + (lVar15 + lVar18) * 3);
  pbVar4 = (byte *)(lVar16 + (lVar19 + lVar18) * 3);
  fVar32 = (float)NEON_ucvtf((uint)pbVar2[2]);
  fVar28 = (float)NEON_ucvtf((uint)pbVar1[2]);
  fVar35 = (float)NEON_ucvtf((uint)pbVar3[2]);
  fVar38 = (float)NEON_ucvtf((uint)pbVar4[2]);
  pbVar5 = (byte *)(lVar16 + (lVar12 + lVar17) * 3);
  pbVar6 = (byte *)(lVar16 + (lVar12 + lVar18) * 3);
  pbVar7 = (byte *)(lVar16 + (lVar13 + lVar17) * 3);
  pbVar8 = (byte *)(lVar16 + (lVar13 + lVar18) * 3);
  fVar24 = (float)NEON_ucvtf((uint)*pbVar2);
  fVar27 = (float)NEON_ucvtf((uint)pbVar1[1]);
  fVar26 = (float)NEON_ucvtf((uint)*pbVar1);
  fVar25 = (float)NEON_ucvtf((uint)pbVar2[1]);
  fVar36 = (float)NEON_ucvtf((uint)pbVar3[1]);
  fVar37 = (float)NEON_ucvtf((uint)*pbVar3);
  fVar39 = (float)NEON_ucvtf((uint)pbVar4[1]);
  fVar40 = (float)NEON_ucvtf((uint)*pbVar4);
  fVar31 = (float)NEON_ucvtf((uint)pbVar5[2]);
  fVar34 = (float)NEON_ucvtf((uint)pbVar5[1]);
  fVar33 = (float)NEON_ucvtf((uint)*pbVar5);
  fVar41 = (float)NEON_ucvtf((uint)pbVar6[2]);
  fVar42 = (float)NEON_ucvtf((uint)pbVar6[1]);
  fVar43 = (float)NEON_ucvtf((uint)*pbVar6);
  fVar44 = (float)NEON_ucvtf((uint)pbVar7[2]);
  fVar45 = (float)NEON_ucvtf((uint)pbVar7[1]);
  fVar46 = (float)NEON_ucvtf((uint)*pbVar7);
  fVar47 = (float)NEON_ucvtf((uint)pbVar8[2]);
  fVar29 = (float)NEON_ucvtf((uint)pbVar8[1]);
  fVar30 = (float)NEON_ucvtf((uint)*pbVar8);
  fVar32 = (float)NEON_fmadd(fVar35 - fVar32,fVar23,fVar32);
  fVar28 = (float)NEON_fmadd(fVar38 - fVar28,fVar23,fVar28);
  fVar25 = (float)NEON_fmadd(fVar36 - fVar25,fVar23,fVar25);
  fVar27 = (float)NEON_fmadd(fVar39 - fVar27,fVar23,fVar27);
  fVar24 = (float)NEON_fmadd(fVar37 - fVar24,fVar23,fVar24);
  fVar26 = (float)NEON_fmadd(fVar40 - fVar26,fVar23,fVar26);
  fVar35 = (float)NEON_fmadd(fVar41 - fVar31,fVar23,fVar31);
  fVar36 = (float)NEON_fmadd(fVar47 - fVar44,fVar23,fVar44);
  fVar34 = (float)NEON_fmadd(fVar42 - fVar34,fVar23,fVar34);
  fVar37 = (float)NEON_fmadd(fVar29 - fVar45,fVar23,fVar45);
  fVar31 = (float)NEON_fmadd(fVar43 - fVar33,fVar23,fVar33);
  fVar23 = (float)NEON_fmadd(fVar30 - fVar46,fVar23,fVar46);
  fVar22 = fVar22 - (float)(int)fVar22;
  fVar29 = (float)NEON_fmadd(fVar35 - fVar32,fVar22,fVar32);
  fVar28 = (float)NEON_fmadd(fVar36 - fVar28,fVar22,fVar28);
  fVar25 = (float)NEON_fmadd(fVar34 - fVar25,fVar22,fVar25);
  fVar27 = (float)NEON_fmadd(fVar37 - fVar27,fVar22,fVar27);
  fVar24 = (float)NEON_fmadd(fVar31 - fVar24,fVar22,fVar24);
  fVar22 = (float)NEON_fmadd(fVar23 - fVar26,fVar22,fVar26);
  fVar20 = fVar20 - (float)(int)fVar20;
  uVar21 = NEON_fmadd(fVar28 - fVar29,fVar20,fVar29);
  NEON_fmadd(fVar27 - fVar25,fVar20,fVar25);
  NEON_fmadd(fVar22 - fVar24,fVar20,fVar24);
  return uVar21;
}



/* 0010ee94 operator() */

/* (anonymous namespace)::applyAlgorithm(_JNIEnv*, _jobject*, char const*, char const*, char const*,
   int, int, int)::$_0::TEMPNAMEPLACEHOLDERVALUE() const */

int __thiscall
(anonymous_namespace)::
applyAlgorithm(_JNIEnv*,_jobject*,char_const*,char_const*,char_const*,int,int,int)::$_0::operator()
          (__0 *this)

{
  int iVar1;
  byte *pbVar2;
  byte *pbVar3;
  
  pbVar2 = *(byte **)this;
  pbVar3 = *(byte **)(pbVar2 + 0x10);
  if ((*pbVar2 & 1) == 0) {
    pbVar3 = pbVar2 + 1;
  }
  unlink((char *)pbVar3);
  pbVar2 = *(byte **)(this + 8);
  pbVar3 = *(byte **)(pbVar2 + 0x10);
  if ((*pbVar2 & 1) == 0) {
    pbVar3 = pbVar2 + 1;
  }
  iVar1 = unlink((char *)pbVar3);
  return iVar1;
}



/* 0010eedc leicaRanges */

/* leicaRanges(std::__ndk1::vector<unsigned char, std::__ndk1::allocator<unsigned char> > const&,
   unsigned long, unsigned long, std::__ndk1::vector<LeicaRange, std::__ndk1::allocator<LeicaRange>
   >&, unsigned int&) */

bool leicaRanges(vector *param_1,ulong param_2,ulong param_3,vector *param_4,uint *param_5)

{
  ushort *puVar1;
  uint uVar2;
  ushort uVar3;
  bool bVar4;
  undefined8 *puVar5;
  ulong uVar6;
  uint uVar7;
  uint uVar8;
  ulong uVar9;
  uint uVar10;
  float local_b0;
  float fStack_ac;
  uint local_a8;
  LeicaRange *local_a0;
  undefined8 local_98;
  undefined8 uStack_90;
  float local_88;
  float fStack_84;
  undefined4 local_80;
  undefined8 *local_78;
  undefined8 *local_70;
  undefined8 *local_68;
  
  if ((((ulong)(*(long *)(param_1 + 8) - *(long *)param_1) < param_3) || (param_3 < param_2 + 2)) ||
     (uVar7 = (uint)*(ushort *)(*(long *)param_1 + param_2), uVar7 - 0x21 < 0xffffffe0)) {
LAB_0010ef2c:
    bVar4 = false;
  }
  else {
    uVar8 = 0;
    uVar6 = param_2 + 2;
    do {
      uVar9 = uVar6 + 6;
      if (param_3 < uVar9) goto LAB_0010ef2c;
      puVar1 = (ushort *)(*(long *)param_1 + uVar6);
      local_88 = (float)NEON_ucvtf((uint)*puVar1);
      local_80 = 0;
      local_70 = (undefined8 *)0x0;
      local_68 = (undefined8 *)0x0;
      fStack_84 = (float)NEON_ucvtf((uint)puVar1[1]);
      local_78 = (undefined8 *)0x0;
      uVar3 = puVar1[2];
      uVar10 = (uint)uVar3;
      if ((uVar3 - 0x21 < 0xffffffe0) ||
         (uVar6 = uVar9 + (ulong)(uint)uVar3 * 6,
         (param_3 < uVar6 || local_88 != fStack_84) && (param_3 < uVar6 || fStack_84 <= local_88)))
      {
        bVar4 = false;
      }
      else {
        do {
          puVar5 = local_70;
          puVar1 = (ushort *)(*(long *)param_1 + uVar9);
          local_b0 = (float)NEON_ucvtf((uint)*puVar1);
          fStack_ac = (float)NEON_ucvtf((uint)puVar1[1]);
          uVar3 = puVar1[2];
          local_98 = 0;
          uStack_90 = 0;
          local_a0 = (LeicaRange *)0x0;
          local_a8 = (uint)uVar3;
          if ((fStack_ac < local_b0) ||
             ((local_78 != local_70 && (local_b0 <= *(float *)((long)local_70 + -0x24)))))
          goto LAB_0010f15c;
          uVar2 = *param_5;
          if (uVar2 < local_a8 || uVar2 == uVar3) {
            uVar2 = (uint)uVar3;
          }
          *param_5 = uVar2;
          if (local_70 < local_68) {
            local_70[3] = 0;
            local_70[4] = 0;
            *(uint *)(local_70 + 1) = local_a8;
            *local_70 = CONCAT44(fStack_ac,local_b0);
            local_70[2] = 0;
                    /* try { // try from 0010f0ac to 0010f0af has its CatchHandler @ 0010f1a8 */
            std::__ndk1::vector<LeicaRange,std::__ndk1::allocator<LeicaRange>>::
            __init_with_size_abi_ne180000_<LeicaRange*,LeicaRange*>
                      ((vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *)(local_70 + 2),
                       (LeicaRange *)0x0,(LeicaRange *)0x0,0);
            local_70 = puVar5 + 5;
          }
          else {
                    /* try { // try from 0010f0b8 to 0010f0c3 has its CatchHandler @ 0010f1a0 */
            local_70 = (undefined8 *)
                       std::__ndk1::vector<LeicaRange,std::__ndk1::allocator<LeicaRange>>::
                       __push_back_slow_path<LeicaRange_const&>
                                 ((vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *)&local_78
                                  ,(LeicaRange *)&local_b0);
          }
          if (local_a0 != (LeicaRange *)0x0) {
            std::__ndk1::vector<LeicaRange,std::__ndk1::allocator<LeicaRange>>::
            __base_destruct_at_end_abi_ne180000_
                      ((vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *)&local_a0,local_a0);
            operator_delete(local_a0);
          }
          uVar10 = uVar10 - 1;
          uVar9 = uVar9 + 6;
        } while (uVar10 != 0);
        puVar5 = *(undefined8 **)(param_4 + 8);
        if ((*(undefined8 **)param_4 == puVar5) || (*(float *)((long)puVar5 - 0x24) < local_88)) {
          if (puVar5 < *(undefined8 **)(param_4 + 0x10)) {
            puVar5[3] = 0;
            puVar5[4] = 0;
            *(undefined4 *)(puVar5 + 1) = local_80;
            *puVar5 = CONCAT44(fStack_84,local_88);
            puVar5[2] = 0;
                    /* try { // try from 0010f148 to 0010f14b has its CatchHandler @ 0010f188 */
            std::__ndk1::vector<LeicaRange,std::__ndk1::allocator<LeicaRange>>::
            __init_with_size_abi_ne180000_<LeicaRange*,LeicaRange*>
                      ((vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *)(puVar5 + 2),
                       (LeicaRange *)local_78,(LeicaRange *)local_70,
                       ((long)local_70 - (long)local_78 >> 3) * -0x3333333333333333);
            puVar5 = puVar5 + 5;
            *(undefined8 **)(param_4 + 8) = puVar5;
          }
          else {
                    /* try { // try from 0010f164 to 0010f16b has its CatchHandler @ 0010f198 */
            puVar5 = (undefined8 *)
                     std::__ndk1::vector<LeicaRange,std::__ndk1::allocator<LeicaRange>>::
                     __push_back_slow_path<LeicaRange_const&>
                               ((vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *)param_4,
                                (LeicaRange *)&local_88);
          }
          bVar4 = true;
          *(undefined8 **)(param_4 + 8) = puVar5;
        }
        else {
LAB_0010f15c:
          bVar4 = false;
        }
      }
      if (local_78 != (undefined8 *)0x0) {
        std::__ndk1::vector<LeicaRange,std::__ndk1::allocator<LeicaRange>>::
        __base_destruct_at_end_abi_ne180000_
                  ((vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *)&local_78,
                   (LeicaRange *)local_78);
        operator_delete(local_78);
      }
      if (!bVar4) goto LAB_0010ef2c;
      uVar8 = uVar8 + 1;
      uVar6 = uVar9;
    } while (uVar8 != uVar7);
    bVar4 = uVar9 == param_3;
  }
  return bVar4;
}



/* 0010f1c8 leicaWeights */

/* leicaWeights(std::__ndk1::vector<LeicaRange, std::__ndk1::allocator<LeicaRange> > const&, float)
    */

void leicaWeights(vector *param_1,float param_2)

{
  void *pvVar1;
  float *pfVar2;
  void *pvVar3;
  undefined8 uVar4;
  void **in_x8;
  long lVar5;
  long lVar6;
  ulong uVar7;
  float fVar8;
  float fVar9;
  
  pfVar2 = *(float **)param_1;
  lVar6 = *(long *)(param_1 + 8);
  in_x8[1] = (void *)0x0;
  in_x8[2] = (void *)0x0;
  *in_x8 = (void *)0x0;
  lVar6 = lVar6 - (long)pfVar2;
  lVar5 = lVar6 >> 3;
  uVar7 = lVar5 * -0x3333333333333333;
  if (lVar6 == 0) {
    pvVar3 = (void *)0x0;
  }
  else {
    if (uVar7 >> 0x3e != 0) {
                    /* try { // try from 0010f2c4 to 0010f2cb has its CatchHandler @ 0010f2cc */
      uVar4 = std::__ndk1::vector<float,std::__ndk1::allocator<float>>::
              __throw_length_error_abi_ne180000_();
                    /* catch() { ... } // from try @ 0010f218 with catch @ 0010f2cc
                       catch() { ... } // from try @ 0010f2c4 with catch @ 0010f2cc */
      pvVar3 = *in_x8;
      if (pvVar3 != (void *)0x0) {
        in_x8[1] = pvVar3;
        operator_delete(pvVar3);
      }
                    /* WARNING: Subroutine does not return */
      _Unwind_Resume(uVar4);
    }
                    /* try { // try from 0010f218 to 0010f21f has its CatchHandler @ 0010f2cc */
    pvVar3 = operator_new(lVar5 * 0x3333333333333334);
    pvVar1 = (void *)((long)pvVar3 + lVar5 * 0x3333333333333334);
    *in_x8 = pvVar3;
    in_x8[2] = pvVar1;
    memset(pvVar3,0,lVar5 * 0x3333333333333334);
    in_x8[1] = pvVar1;
  }
  lVar6 = 0;
  do {
    lVar5 = lVar6;
    if (uVar7 - lVar5 == 0) {
      return;
    }
    fVar8 = pfVar2[1];
    fVar9 = 1.0;
    lVar6 = lVar5;
    if ((param_2 <= fVar8) || (lVar6 = uVar7 - 1, uVar7 - 1 == lVar5)) goto LAB_0010f2a8;
    fVar9 = pfVar2[10];
    lVar6 = lVar5 + 1;
    pfVar2 = pfVar2 + 10;
  } while (fVar9 <= param_2);
  fVar9 = (param_2 - fVar8) / (fVar9 - fVar8);
  *(float *)((long)pvVar3 + (lVar5 + 1) * 4) = fVar9;
  fVar9 = 1.0 - fVar9;
  lVar6 = lVar5;
LAB_0010f2a8:
  *(float *)((long)pvVar3 + lVar6 * 4) = fVar9;
  return;
}



/* 0010f2ec operator() */

/* WARNING: Removing unreachable block (ram,0x00110350) */
/* WARNING: Removing unreachable block (ram,0x00110358) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* (anonymous namespace)::applyLeicaFilter(_JNIEnv*, _jobject*, char const*, float, float, float,
   float, float, bool, float, float)::$_0::TEMPNAMEPLACEHOLDERVALUE(unsigned int, unsigned int)
   const */

void (anonymous_namespace)::
     applyLeicaFilter(_JNIEnv*,_jobject*,char_const*,float,float,float,float,float,bool,float,float)
     ::$_0::operator()(uint param_1,uint param_2)

{
  byte *pbVar1;
  uint uVar2;
  float *pfVar3;
  char cVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  uint **ppuVar8;
  uint in_w2;
  int iVar9;
  long lVar10;
  long lVar11;
  int iVar12;
  ulong uVar13;
  uint *puVar14;
  ulong uVar15;
  ulong uVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  undefined8 uVar28;
  undefined8 uVar29;
  undefined8 uVar30;
  float in_s1;
  float fVar31;
  undefined4 uVar32;
  undefined4 uVar33;
  float fVar34;
  float fVar35;
  ulong uVar36;
  float in_s2;
  uint uVar37;
  float fVar38;
  float fVar39;
  undefined8 uVar40;
  float fVar41;
  float fVar42;
  ulong uVar43;
  undefined8 uVar44;
  float fVar45;
  ulong uVar46;
  float fVar47;
  undefined8 uVar48;
  float fVar49;
  byte bVar52;
  float fVar50;
  float fVar51;
  byte bVar53;
  float fVar54;
  float fVar55;
  float fVar56;
  float fVar57;
  float fVar58;
  undefined4 uVar59;
  float fVar60;
  float fVar61;
  float fVar62;
  float fVar63;
  float fVar65;
  float fVar66;
  undefined8 uVar67;
  uint local_120;
  undefined8 local_100;
  undefined8 uStack_f8;
  undefined8 uStack_f0;
  undefined8 local_e8;
  undefined4 local_e0;
  undefined8 local_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 local_b8;
  undefined4 local_b0;
  ulong uVar64;
  
  uVar7 = DAT_00102f98;
  uVar6 = DAT_00102f90;
  uVar5 = DAT_00102f40;
  ppuVar8 = (uint **)(ulong)param_1;
  if (param_2 < in_w2) {
    uVar28 = NEON_fmov(0x3f800000,4);
    puVar14 = *ppuVar8;
    fVar60 = 1.0;
    uVar13 = (ulong)*puVar14;
    local_120 = param_2;
    do {
      if ((int)uVar13 != 0) {
        uVar15 = 0;
        uVar16 = 0;
        fVar17 = (float)(ulong)local_120;
        do {
          cVar4 = *(char *)ppuVar8[2];
          pbVar1 = (byte *)(*(long *)ppuVar8[1] + (uVar15 & 0xfffffffc) +
                           (ulong)(puVar14[2] * local_120));
          if (cVar4 == '\0') {
            fVar18 = (float)NEON_ucvtf((uint)*pbVar1);
            in_s1 = (float)NEON_ucvtf((uint)pbVar1[1]);
            in_s2 = (float)NEON_ucvtf((uint)pbVar1[2]);
          }
          else {
            fVar18 = (float)sampleLut((vector *)ppuVar8[3],(uint)*pbVar1,(uint)pbVar1[1],
                                      (uint)pbVar1[2]);
          }
          uVar37 = (uint)(long)fVar18;
          if (0xfe < (int)uVar37) {
            uVar37 = 0xff;
          }
          uVar29 = NEON_smin(CONCAT44((int)(long)in_s2,(int)(long)in_s1),0xff000000ff,4);
          fVar18 = (float)(uVar37 & ((int)uVar37 >> 0x1f ^ 0xffffffffU));
          uVar29 = NEON_smax(uVar29,0,4);
          uVar29 = NEON_scvtf(uVar29,4);
          fVar21 = (float)((ulong)uVar28 >> 0x20);
          fVar65 = (float)((ulong)uVar29 >> 0x20);
          if (*(char *)ppuVar8[4] == '\0') {
            if ((cVar4 != '\0') || (*(short *)(*(long *)ppuVar8[0xb] + 0x360) != 0)) {
              fVar18 = fVar18 / 255.0;
              fVar56 = (float)uVar29 / 255.0;
              fVar65 = fVar65 / 255.0;
              fVar54 = fVar65;
              if (fVar65 <= fVar56) {
                fVar54 = fVar56;
              }
              fVar58 = ((fVar18 - fVar54) + -0.03) / 0.22;
              fVar54 = fVar60;
              if (fVar58 <= 1.0) {
                fVar54 = fVar58;
              }
              fVar19 = 0.0;
              if (0.0 <= fVar58) {
                fVar19 = fVar54;
              }
              fVar54 = fVar56;
              if (fVar56 <= fVar18) {
                fVar54 = fVar18;
              }
              fVar58 = ((fVar65 - fVar54) + -0.03) / 0.22;
              fVar54 = fVar60;
              if (fVar58 <= 1.0) {
                fVar54 = fVar58;
              }
              fVar31 = 0.0;
              if (0.0 <= fVar58) {
                fVar31 = fVar54;
              }
              fVar54 = fVar65;
              if (fVar65 <= fVar18) {
                fVar54 = fVar18;
              }
              fVar58 = ((fVar56 - fVar54) + -0.02) / 0.2;
              fVar54 = fVar60;
              if (fVar58 <= 1.0) {
                fVar54 = fVar58;
              }
              fVar63 = (float)NEON_fmadd(fVar19,0xc0000000,0x40400000);
              fVar20 = 0.0;
              if (0.0 <= fVar58) {
                fVar20 = fVar54;
              }
              fVar54 = (float)NEON_fmadd(fVar31,0xc0000000,0x40400000);
              fVar50 = (float)NEON_fmadd(fVar20,0xc0000000,0x40400000);
              fVar50 = fVar20 * fVar20 * fVar50;
              uVar32 = NEON_fmadd(fVar19 * fVar19 * fVar63 * 0.16,fVar18 - fVar56,fVar56);
              fVar19 = (float)NEON_fmadd(fVar50,0xbe4ccccd,0x3f800000);
              fVar58 = (float)NEON_fmadd(fVar31 * fVar31 * fVar54 * 0.18,fVar65 - fVar56,uVar32);
              fVar54 = (float)NEON_fmadd(fVar50,0xbe800000,0x3f800000);
              fVar18 = (float)NEON_fmadd(fVar50 * 0.1,fVar56,fVar18);
              uVar29 = CONCAT44(fVar19 * fVar65 * fVar54,fVar58 * fVar54);
              fVar54 = fVar54 * fVar18;
              uVar30 = NEON_fcmgt(uVar29,uVar28,4);
              uVar30 = NEON_bsl(uVar30,uVar28,uVar29,1);
              fVar18 = fVar60;
              if (fVar54 <= 1.0) {
                fVar18 = fVar54;
              }
              uVar29 = NEON_fcmlt(uVar29,0,4);
              fVar65 = (float)uVar30 * 255.0;
              fVar58 = (float)((ulong)uVar30 >> 0x20) * 255.0;
              fVar56 = (float)CONCAT13((byte)((uint)fVar65 >> 0x18) & ~(byte)((ulong)uVar29 >> 0x18)
                                       ,CONCAT12((byte)((uint)fVar65 >> 0x10) &
                                                 ~(byte)((ulong)uVar29 >> 0x10),
                                                 CONCAT11((byte)((uint)fVar65 >> 8) &
                                                          ~(byte)((ulong)uVar29 >> 8),
                                                          SUB41(fVar65,0) & ~(byte)uVar29)));
              fVar65 = 0.0;
              if (0.0 <= fVar54) {
                fVar65 = fVar18 * 255.0;
              }
              fVar19 = (float)NEON_fmadd(fVar65,0x3e991687,fVar56 * 0.587);
              fVar54 = (float)(CONCAT17((byte)((uint)fVar58 >> 0x18) &
                                        ~(byte)((ulong)uVar29 >> 0x38),
                                        CONCAT16((byte)((uint)fVar58 >> 0x10) &
                                                 ~(byte)((ulong)uVar29 >> 0x30),
                                                 CONCAT15((byte)((uint)fVar58 >> 8) &
                                                          ~(byte)((ulong)uVar29 >> 0x28),
                                                          CONCAT14(SUB41(fVar58,0) &
                                                                   ~(byte)((ulong)uVar29 >> 0x20),
                                                                   fVar56)))) >> 0x20);
              fVar19 = fVar19 + fVar54 * 0.114;
              fVar18 = (float)NEON_fmadd(fVar65 - fVar19,0x3f6e147b,fVar19);
              uVar29 = CONCAT44(fVar19 + (fVar54 - fVar19) * 0.93,fVar19 + (fVar56 - fVar19) * 0.93)
              ;
            }
            fVar65 = (float)*ppuVar8[5];
            if (0.0 <= fVar65) {
              uVar40 = NEON_fmov(0x40800000,4);
              fVar18 = fVar18 / 255.0;
              fVar31 = (float)uVar29 / 255.0;
              fVar20 = (float)((ulong)uVar29 >> 0x20) / 255.0;
              uVar30 = NEON_rev64(CONCAT44(fVar20,fVar31),4);
              uVar29 = NEON_fcmgt(0x3a83126f3a83126f,CONCAT44(fVar18,fVar31),4);
              uVar29 = NEON_bit(CONCAT44(fVar18,fVar31),0x3a83126f3a83126f,uVar29,1);
              fVar58 = (float)uVar30 / (float)uVar29;
              fVar19 = (float)((ulong)uVar30 >> 0x20) / (float)((ulong)uVar29 >> 0x20);
              fVar56 = 1.0;
              fVar63 = (fVar19 + -0.9) / 0.15;
              fVar54 = fVar56;
              if (fVar65 <= 1.0) {
                fVar54 = fVar65;
              }
              fVar50 = 0.0;
              if (0.0 <= fVar65) {
                fVar50 = fVar54;
              }
              fVar55 = (fVar58 + -0.9) / 0.15;
              fVar54 = 0.6;
              if (ABS(fVar65) != INFINITY) {
                fVar54 = fVar50;
              }
              fVar65 = fVar56;
              if (fVar63 <= 1.0) {
                fVar65 = fVar63;
              }
              fVar50 = 0.0;
              if (0.0 <= fVar63) {
                fVar50 = fVar65;
              }
              fVar65 = fVar56;
              if (fVar55 <= 1.0) {
                fVar65 = fVar55;
              }
              fVar23 = (float)NEON_fmadd(fVar50,0xc0000000,0x40400000);
              fVar22 = 0.0;
              fVar63 = 0.0;
              if (0.0 <= fVar55) {
                fVar63 = fVar65;
              }
              fVar65 = fVar20;
              if (fVar20 <= fVar31) {
                fVar65 = fVar31;
              }
              fVar55 = ((fVar18 - fVar65) + -0.03) / 0.19;
              fVar65 = fVar56;
              if (fVar55 <= 1.0) {
                fVar65 = fVar55;
              }
              fVar24 = fVar22;
              if (0.0 <= fVar55) {
                fVar24 = fVar65;
              }
              fVar65 = fVar20;
              if (fVar20 <= fVar18) {
                fVar65 = fVar18;
              }
              fVar55 = ((fVar31 - fVar65) + -0.025) / 0.175;
              fVar57 = (float)NEON_fmadd(fVar18,0x3e991687,fVar31 * 0.587);
              fVar57 = fVar57 + fVar20 * 0.114;
              fVar65 = fVar56;
              if (fVar55 <= 1.0) {
                fVar65 = fVar55;
              }
              uVar29 = CONCAT44((fVar19 + (float)((ulong)DAT_00102f88 >> 0x20)) / 0.2,
                                (fVar58 + (float)DAT_00102f88) * (float)uVar40);
              uVar30 = CONCAT44((fVar57 + (float)((ulong)DAT_00102f58 >> 0x20)) /
                                (float)((ulong)DAT_00102f80 >> 0x20),
                                (fVar57 + (float)DAT_00102f58) / (float)DAT_00102f80);
              fVar58 = fVar22;
              if (0.0 <= fVar55) {
                fVar58 = fVar65;
              }
              uVar40 = NEON_fcmgt(uVar29,uVar28,4);
              uVar44 = NEON_fcmlt(uVar29,0,4);
              fVar65 = fVar31;
              if (fVar31 <= fVar18) {
                fVar65 = fVar18;
              }
              uVar40 = NEON_bsl(uVar40,uVar28,uVar29,1);
              uVar29 = NEON_fmov(0x40400000,4);
              fVar57 = (float)CONCAT13((byte)((ulong)uVar40 >> 0x18) &
                                       ~(byte)((ulong)uVar44 >> 0x18),
                                       CONCAT12((byte)((ulong)uVar40 >> 0x10) &
                                                ~(byte)((ulong)uVar44 >> 0x10),
                                                CONCAT11((byte)((ulong)uVar40 >> 8) &
                                                         ~(byte)((ulong)uVar44 >> 8),
                                                         (byte)uVar40 & ~(byte)uVar44)));
              fVar25 = (float)(CONCAT17((byte)((ulong)uVar40 >> 0x38) &
                                        ~(byte)((ulong)uVar44 >> 0x38),
                                        CONCAT16((byte)((ulong)uVar40 >> 0x30) &
                                                 ~(byte)((ulong)uVar44 >> 0x30),
                                                 CONCAT15((byte)((ulong)uVar40 >> 0x28) &
                                                          ~(byte)((ulong)uVar44 >> 0x28),
                                                          CONCAT14((byte)((ulong)uVar40 >> 0x20) &
                                                                   ~(byte)((ulong)uVar44 >> 0x20),
                                                                   fVar57)))) >> 0x20);
              fVar38 = (float)uVar29;
              fVar42 = (float)((ulong)uVar29 >> 0x20);
              uVar29 = NEON_fcmgt(uVar30,uVar28,4);
              uVar40 = NEON_fcmlt(uVar30,0,4);
              uVar29 = NEON_bsl(uVar29,uVar28,uVar30,1);
              fVar55 = ((fVar20 - fVar65) + -0.03) / 0.19;
              fVar26 = (float)CONCAT13((byte)((ulong)uVar29 >> 0x18) &
                                       ~(byte)((ulong)uVar40 >> 0x18),
                                       CONCAT12((byte)((ulong)uVar29 >> 0x10) &
                                                ~(byte)((ulong)uVar40 >> 0x10),
                                                CONCAT11((byte)((ulong)uVar29 >> 8) &
                                                         ~(byte)((ulong)uVar40 >> 8),
                                                         (byte)uVar29 & ~(byte)uVar40)));
              fVar19 = (float)NEON_fmadd(fVar63,0xc0000000,0x40400000);
              fVar27 = (float)(CONCAT17((byte)((ulong)uVar29 >> 0x38) &
                                        ~(byte)((ulong)uVar40 >> 0x38),
                                        CONCAT16((byte)((ulong)uVar29 >> 0x30) &
                                                 ~(byte)((ulong)uVar40 >> 0x30),
                                                 CONCAT15((byte)((ulong)uVar29 >> 0x28) &
                                                          ~(byte)((ulong)uVar40 >> 0x28),
                                                          CONCAT14((byte)((ulong)uVar29 >> 0x20) &
                                                                   ~(byte)((ulong)uVar40 >> 0x20),
                                                                   fVar26)))) >> 0x20);
              fVar34 = (float)NEON_fmadd(fVar58,0xc0000000,0x40400000);
              fVar66 = (float)NEON_fmadd(fVar24,0xc0000000,0x40400000);
              fVar65 = fVar56;
              if (fVar55 <= 1.0) {
                fVar65 = fVar55;
              }
              fVar34 = fVar58 * fVar58 * fVar34;
              if (0.0 <= fVar55) {
                fVar22 = fVar65;
              }
              fVar55 = (float)NEON_fmadd(fVar54,0xbee66666,0x3f800000);
              fVar50 = (1.0 - fVar63 * fVar63 * fVar19) *
                       fVar25 * fVar25 * (fVar42 + fVar25 * -2.0) * (1.0 - fVar50 * fVar50 * fVar23)
                       * fVar57 * fVar57 * (fVar38 + fVar57 * -2.0);
              fVar19 = (float)NEON_fmadd(fVar22,0xc0000000,0x40400000);
              fVar55 = fVar55 * (1.0 - fVar27 * fVar27 * (fVar42 + fVar27 * -2.0)) *
                                fVar26 * fVar26 * (fVar38 + fVar26 * -2.0);
              fVar65 = (float)NEON_fmadd(fVar50,0xbf59999a,0x3f800000);
              fVar19 = fVar22 * fVar22 * fVar19;
              fVar63 = (float)NEON_fmadd(fVar54,0xbf59999a,0x3f800000);
              fVar58 = fVar24 * fVar24 * fVar66 * fVar65;
              fVar22 = fVar19 * 0.14;
              fVar23 = (float)NEON_fmadd(fVar34 * 0.07 * fVar31,fVar55,fVar18);
              fVar18 = (float)NEON_fmadd(fVar34 * -0.1,fVar55,0x3f800000);
              uVar32 = NEON_fmadd(fVar34,0x3dcccccd,fVar22);
              uVar33 = NEON_fmadd(fVar58 * -0.08,fVar23 - fVar31,-(fVar22 * (fVar20 - fVar31)));
              uVar59 = NEON_fmadd(fVar58,0x3d0f5c29,uVar32);
              uVar32 = NEON_fmadd(fVar58,0x3dcccccd,fVar19 * 0.1);
              fVar58 = (float)NEON_fmadd(uVar33,fVar55,fVar31);
              fVar31 = (float)NEON_fmsub(uVar59,fVar55,0x3f800000);
              uVar32 = NEON_fmadd(uVar32,fVar55,0x3f800000);
              fVar19 = fVar18 * fVar20 * fVar31;
              fVar20 = (float)NEON_fmadd(fVar23 * fVar31,0x3e991687,fVar58 * fVar31 * 0.587);
              fVar20 = fVar20 + fVar19 * 0.114;
              fVar55 = (fVar20 + -0.07) / 0.23;
              fVar22 = (fVar20 + -0.72) / 0.26;
              fVar18 = fVar56;
              if (fVar55 <= 1.0) {
                fVar18 = fVar55;
              }
              fVar26 = (fVar20 + -0.015) / 0.075;
              fVar57 = 0.0;
              fVar24 = fVar57;
              if (0.0 <= fVar55) {
                fVar24 = fVar18;
              }
              uVar29 = CONCAT44((fVar20 + (float)((ulong)DAT_00102f68 >> 0x20)) /
                                (float)((ulong)DAT_00102fa0 >> 0x20),
                                (fVar20 + (float)DAT_00102f68) / (float)DAT_00102fa0);
              fVar55 = (float)NEON_fmadd(fVar54,0xbf19999a,0x3f800000);
              fVar50 = (float)NEON_fmadd(fVar50,0xbf266666,0x3f800000);
              uVar30 = CONCAT44((fVar20 + (float)((ulong)DAT_00102f38 >> 0x20)) / 0.18,
                                (fVar20 + (float)DAT_00102f38) / 0.18);
              fVar18 = fVar56;
              if (fVar22 <= 1.0) {
                fVar18 = fVar22;
              }
              uVar40 = NEON_fcmlt(uVar29,0,4);
              fVar25 = fVar57;
              if (0.0 <= fVar22) {
                fVar25 = fVar18;
              }
              fVar18 = fVar56;
              if (fVar26 <= 1.0) {
                fVar18 = fVar26;
              }
              uVar44 = NEON_fcmgt(uVar29,uVar28,4);
              if (0.0 <= fVar26) {
                fVar57 = fVar18;
              }
              uVar29 = NEON_bsl(uVar44,uVar28,uVar29,1);
              uVar67 = NEON_fcmgt(uVar30,uVar28,4);
              uVar44 = NEON_fcmlt(uVar30,0,4);
              fVar22 = (float)CONCAT13((byte)((ulong)uVar29 >> 0x18) &
                                       ~(byte)((ulong)uVar40 >> 0x18),
                                       CONCAT12((byte)((ulong)uVar29 >> 0x10) &
                                                ~(byte)((ulong)uVar40 >> 0x10),
                                                CONCAT11((byte)((ulong)uVar29 >> 8) &
                                                         ~(byte)((ulong)uVar40 >> 8),
                                                         (byte)uVar29 & ~(byte)uVar40)));
              uVar30 = NEON_bit(uVar30,uVar28,uVar67,1);
              fVar27 = (float)CONCAT13((byte)((ulong)uVar30 >> 0x18) &
                                       ~(byte)((ulong)uVar44 >> 0x18),
                                       CONCAT12((byte)((ulong)uVar30 >> 0x10) &
                                                ~(byte)((ulong)uVar44 >> 0x10),
                                                CONCAT11((byte)((ulong)uVar30 >> 8) &
                                                         ~(byte)((ulong)uVar44 >> 8),
                                                         (byte)uVar30 & ~(byte)uVar44)));
              fVar34 = (float)(CONCAT17((byte)((ulong)uVar30 >> 0x38) &
                                        ~(byte)((ulong)uVar44 >> 0x38),
                                        CONCAT16((byte)((ulong)uVar30 >> 0x30) &
                                                 ~(byte)((ulong)uVar44 >> 0x30),
                                                 CONCAT15((byte)((ulong)uVar30 >> 0x28) &
                                                          ~(byte)((ulong)uVar44 >> 0x28),
                                                          CONCAT14((byte)((ulong)uVar30 >> 0x20) &
                                                                   ~(byte)((ulong)uVar44 >> 0x20),
                                                                   fVar27)))) >> 0x20);
              fVar26 = (float)(CONCAT17((byte)((ulong)uVar29 >> 0x38) &
                                        ~(byte)((ulong)uVar40 >> 0x38),
                                        CONCAT16((byte)((ulong)uVar29 >> 0x30) &
                                                 ~(byte)((ulong)uVar40 >> 0x30),
                                                 CONCAT15((byte)((ulong)uVar29 >> 0x28) &
                                                          ~(byte)((ulong)uVar40 >> 0x28),
                                                          CONCAT14((byte)((ulong)uVar29 >> 0x20) &
                                                                   ~(byte)((ulong)uVar40 >> 0x20),
                                                                   fVar22)))) >> 0x20);
              fVar18 = (float)NEON_fmadd(fVar25,0xc0000000,0x40400000);
              uVar33 = NEON_fmadd(fVar25 * fVar25 * fVar18,0xbf4ccccd,0x3f800000);
              fVar50 = (float)NEON_fmadd(((float)DAT_00102f60 + (float)DAT_00102fb8 * fVar20) *
                                         fVar55 * fVar50 * 0.55 * fVar20 * (1.0 - fVar20) *
                                         ((float)((ulong)DAT_00102f60 >> 0x20) +
                                         (float)((ulong)DAT_00102fb8 >> 0x20) * fVar57) *
                                         fVar57 * fVar57,uVar33,fVar20);
              fVar18 = 1e-06;
              if (1e-06 <= fVar20) {
                fVar18 = fVar20;
              }
              fVar65 = fVar65 * (fVar22 * fVar22 * (fVar38 + fVar22 * -2.0) * 0.006 *
                                 ((float)uVar28 - fVar27 * fVar27 * (fVar38 + fVar27 * -2.0)) -
                                fVar26 * fVar26 * (fVar42 + fVar26 * -2.0) * fVar63 * 0.008 *
                                (fVar21 - fVar34 * fVar34 * (fVar42 + fVar34 * -2.0)));
              fVar18 = fVar50 / fVar18;
              fVar21 = (float)NEON_fmadd(fVar24,0xc0000000,0x40400000);
              fVar21 = (float)NEON_fmadd(fVar54 * -0.3,1.0 - fVar24 * fVar24 * fVar21,uVar32);
              fVar54 = (float)NEON_fmadd(fVar23 * fVar31 - fVar20,fVar21,fVar20);
              fVar54 = fVar54 * fVar18 + fVar65;
              fVar58 = (fVar20 + (fVar58 * fVar31 - fVar20) * fVar21) * fVar18 -
                       (fVar65 * 0.185) / 0.587;
              fVar65 = (fVar20 + (fVar19 - fVar20) * fVar21) * fVar18 - fVar65;
              fVar18 = fVar58;
              if (fVar54 <= fVar58) {
                fVar18 = fVar54;
              }
              fVar21 = fVar65;
              if (fVar18 <= fVar65) {
                fVar21 = fVar18;
              }
              fVar18 = fVar58;
              if (fVar58 <= fVar54) {
                fVar18 = fVar54;
              }
              fVar19 = fVar65;
              if (fVar65 <= fVar18) {
                fVar19 = fVar18;
              }
              if (fVar21 < 0.0) {
                fVar18 = fVar50 - fVar21;
                if (fVar50 - fVar21 <= 1e-06) {
                  fVar18 = 1e-06;
                }
                fVar56 = (float)NEON_fminnm(fVar50 / fVar18,0x3f800000);
              }
              fVar18 = fVar56;
              if (1.0 < fVar19) {
                fVar18 = fVar19 - fVar50;
                if (fVar19 - fVar50 <= 1e-06) {
                  fVar18 = 1e-06;
                }
                fVar18 = (1.0 - fVar50) / fVar18;
                if (fVar56 <= fVar18) {
                  fVar18 = fVar56;
                }
              }
              fVar21 = (float)NEON_fmadd(fVar54 - fVar50,fVar18,fVar50);
              uVar29 = CONCAT44(fVar50 + (fVar65 - fVar50) * fVar18,
                                fVar50 + (fVar58 - fVar50) * fVar18);
              fVar65 = fVar60;
              if (fVar21 <= 1.0) {
                fVar65 = fVar21;
              }
              uVar30 = NEON_fcmgt(uVar29,uVar28,4);
              uVar30 = NEON_bsl(uVar30,uVar28,uVar29,1);
              uVar29 = NEON_fcmlt(uVar29,0,4);
              fVar54 = (float)uVar30 * 255.0;
              fVar56 = (float)((ulong)uVar30 >> 0x20) * 255.0;
              fVar18 = 0.0;
              if (0.0 <= fVar21) {
                fVar18 = fVar65 * 255.0;
              }
              uVar29 = CONCAT17((byte)((uint)fVar56 >> 0x18) & ~(byte)((ulong)uVar29 >> 0x38),
                                CONCAT16((byte)((uint)fVar56 >> 0x10) &
                                         ~(byte)((ulong)uVar29 >> 0x30),
                                         CONCAT15((byte)((uint)fVar56 >> 8) &
                                                  ~(byte)((ulong)uVar29 >> 0x28),
                                                  CONCAT14(SUB41(fVar56,0) &
                                                           ~(byte)((ulong)uVar29 >> 0x20),
                                                           CONCAT13((byte)((uint)fVar54 >> 0x18) &
                                                                    ~(byte)((ulong)uVar29 >> 0x18),
                                                                    CONCAT12((byte)((uint)fVar54 >>
                                                                                   0x10) &
                                                                             ~(byte)((ulong)uVar29
                                                                                    >> 0x10),
                                                                             CONCAT11((byte)((uint)
                                                  fVar54 >> 8) & ~(byte)((ulong)uVar29 >> 8),
                                                  SUB41(fVar54,0) & ~(byte)uVar29)))))));
            }
            in_s1 = (float)((ulong)uVar29 >> 0x20);
            if (*(char *)ppuVar8[8] == '\0') {
              fVar65 = 0.0;
            }
            else {
              fVar21 = fVar18 / 255.0;
              fVar54 = (float)uVar29 / 255.0;
              fVar56 = in_s1 / 255.0;
              fVar65 = (float)NEON_ucvtf(puVar14[1]);
              fVar65 = (float)leicaShadingDelta(fVar21,fVar54,fVar56,(float)(uVar16 & 0xffffffff),
                                                fVar17,(float)uVar13,fVar65,(float *)ppuVar8[9],
                                                (float)*ppuVar8[10]);
              fVar65 = fVar65 * 255.0;
              if ((fVar65 < 0.0) && (0.0 <= (float)*ppuVar8[5])) {
                uVar32 = NEON_fmadd(fVar21,0x3e991687,fVar54 * 0.587);
                fVar31 = (float)NEON_fmadd(fVar56,0x3de978d5,uVar32);
                fVar19 = (fVar31 + -0.65) * 4.0;
                fVar58 = fVar60;
                if (fVar19 <= 1.0) {
                  fVar58 = fVar19;
                }
                fVar20 = 0.0;
                if (0.0 <= fVar19) {
                  fVar20 = fVar58;
                }
                fVar58 = 0.001;
                if (0.001 <= fVar21) {
                  fVar58 = fVar21;
                }
                fVar21 = 0.001;
                if (0.001 <= fVar54) {
                  fVar21 = fVar54;
                }
                uVar40 = CONCAT44((fVar54 / fVar58 + (float)((ulong)uVar6 >> 0x20)) /
                                  (float)((ulong)DAT_00102f28 >> 0x20),
                                  (fVar54 / fVar58 + (float)uVar6) / (float)DAT_00102f28);
                fVar54 = (fVar56 / fVar21 + -0.3) * 4.0;
                uVar67 = NEON_fcmlt(uVar40,0,4);
                fVar56 = (fVar56 / fVar21 + -0.9) / 0.15;
                uVar44 = NEON_fcmgt(uVar40,uVar28,4);
                uVar30 = CONCAT44(*ppuVar8[5],(fVar31 + -0.04) / 0.16);
                uVar40 = NEON_bit(uVar40,uVar28,uVar44,1);
                uVar44 = NEON_fmov(0x40400000,4);
                fVar21 = fVar60;
                if (fVar54 <= 1.0) {
                  fVar21 = fVar54;
                }
                uVar48 = NEON_fcmgt(uVar30,uVar28,4);
                fVar19 = (float)CONCAT13((byte)((ulong)uVar40 >> 0x18) &
                                         ~(byte)((ulong)uVar67 >> 0x18),
                                         CONCAT12((byte)((ulong)uVar40 >> 0x10) &
                                                  ~(byte)((ulong)uVar67 >> 0x10),
                                                  CONCAT11((byte)((ulong)uVar40 >> 8) &
                                                           ~(byte)((ulong)uVar67 >> 8),
                                                           (byte)uVar40 & ~(byte)uVar67)));
                fVar58 = 0.0;
                if (0.0 <= fVar54) {
                  fVar58 = fVar21;
                }
                fVar31 = (float)(CONCAT17((byte)((ulong)uVar40 >> 0x38) &
                                          ~(byte)((ulong)uVar67 >> 0x38),
                                          CONCAT16((byte)((ulong)uVar40 >> 0x30) &
                                                   ~(byte)((ulong)uVar67 >> 0x30),
                                                   CONCAT15((byte)((ulong)uVar40 >> 0x28) &
                                                            ~(byte)((ulong)uVar67 >> 0x28),
                                                            CONCAT14((byte)((ulong)uVar40 >> 0x20) &
                                                                     ~(byte)((ulong)uVar67 >> 0x20),
                                                                     fVar19)))) >> 0x20);
                uVar40 = NEON_fcmlt(uVar30,0,4);
                uVar30 = NEON_bit(uVar30,uVar28,uVar48,1);
                fVar54 = (float)NEON_fmadd(fVar58,0xc0000000,0x40400000);
                fVar21 = fVar60;
                if (fVar56 <= 1.0) {
                  fVar21 = fVar56;
                }
                fVar50 = (float)CONCAT13((byte)((ulong)uVar30 >> 0x18) &
                                         ~(byte)((ulong)uVar40 >> 0x18),
                                         CONCAT12((byte)((ulong)uVar30 >> 0x10) &
                                                  ~(byte)((ulong)uVar40 >> 0x10),
                                                  CONCAT11((byte)((ulong)uVar30 >> 8) &
                                                           ~(byte)((ulong)uVar40 >> 8),
                                                           (byte)uVar30 & ~(byte)uVar40)));
                fVar63 = 0.0;
                if (0.0 <= fVar56) {
                  fVar63 = fVar21;
                }
                fVar56 = (float)NEON_fmadd(fVar63,0xc0000000,0x40400000);
                fVar21 = (float)NEON_fmadd(fVar20,0xc0000000,0x40400000);
                uVar32 = NEON_fmadd((1.0 - fVar63 * fVar63 * fVar56) *
                                    fVar58 * fVar58 * fVar54 *
                                    (1.0 - fVar31 * fVar31 *
                                           ((float)((ulong)uVar44 >> 0x20) + fVar31 * -2.0)) *
                                    fVar19 * fVar19 * ((float)uVar44 + fVar19 * -2.0),0xbf4ccccd,
                                    0x3f800000);
                fVar21 = (float)NEON_fmadd((1.0 - fVar20 * fVar20 * fVar21) *
                                           fVar50 * fVar50 * ((float)uVar7 + (float)uVar5 * fVar50)
                                           * ((float)((ulong)uVar7 >> 0x20) +
                                             (float)((ulong)uVar5 >> 0x20) *
                                             (float)(CONCAT17((byte)((ulong)uVar30 >> 0x38) &
                                                              ~(byte)((ulong)uVar40 >> 0x38),
                                                              CONCAT16((byte)((ulong)uVar30 >> 0x30)
                                                                       & ~(byte)((ulong)uVar40 >>
                                                                                0x30),
                                                                       CONCAT15((byte)((ulong)uVar30
                                                                                      >> 0x28) &
                                                                                ~(byte)((ulong)
                                                  uVar40 >> 0x28),
                                                  CONCAT14((byte)((ulong)uVar30 >> 0x20) &
                                                           ~(byte)((ulong)uVar40 >> 0x20),fVar50))))
                                                  >> 0x20)) * 0.3,uVar32,0x3f800000);
                fVar65 = fVar65 * fVar21;
              }
            }
            in_s2 = (float)uVar29 + fVar65;
            iVar9 = (int)(long)(fVar18 + fVar65);
            fVar65 = in_s1 + fVar65;
          }
          else {
            fVar18 = fVar18 / 255.0;
            fVar58 = (float)*ppuVar8[5];
            fVar54 = (float)*ppuVar8[6];
            fVar56 = (float)*ppuVar8[7];
            pfVar3 = (float *)0x0;
            if (*(char *)ppuVar8[8] != '\0') {
              pfVar3 = (float *)ppuVar8[9];
            }
            uVar37 = puVar14[1];
            fVar31 = (float)*ppuVar8[10];
            fVar19 = 0.0;
            if (ABS(fVar18) == INFINITY) {
LAB_00110044:
              fVar19 = fVar19 / 12.92;
            }
            else {
              fVar20 = fVar60;
              if (fVar18 <= 1.0) {
                fVar20 = fVar18;
              }
              if ((fVar18 < 0.0) || (fVar19 = fVar20, fVar20 <= 0.04045)) goto LAB_00110044;
              fVar19 = powf((fVar20 + 0.055) / 1.055,2.4);
            }
            fVar63 = (float)uVar29 / 255.0;
            fVar65 = fVar65 / 255.0;
            uVar64 = CONCAT44(fVar65,fVar63);
            fVar20 = 0.0;
            if (ABS(fVar63) == INFINITY) {
LAB_001100d4:
              fVar20 = fVar20 / 12.92;
            }
            else {
              fVar50 = fVar60;
              if (fVar63 <= 1.0) {
                fVar50 = fVar63;
              }
              if ((fVar63 < 0.0) || (fVar20 = fVar50, fVar50 <= 0.04045)) goto LAB_001100d4;
              fVar20 = powf((fVar50 + 0.055) / 1.055,2.4);
            }
            fVar63 = 0.0;
            if (ABS(fVar65) == INFINITY) {
LAB_0011015c:
              fVar63 = fVar63 / 12.92;
            }
            else {
              fVar50 = fVar60;
              if (fVar65 <= 1.0) {
                fVar50 = fVar65;
              }
              if ((fVar65 < 0.0) || (fVar63 = fVar50, fVar50 <= 0.04045)) goto LAB_0011015c;
              fVar63 = powf((fVar50 + 0.055) / 1.055,2.4);
            }
            uVar32 = NEON_fmadd(fVar19,0x3e6a784f,fVar20 * 0.6917385);
            fVar19 = (float)NEON_fmadd(fVar63,0x3da2612d,uVar32);
            fVar65 = 0.0;
            if (ABS(fVar19) == INFINITY) {
LAB_0011020c:
              fVar65 = fVar65 * 12.92;
            }
            else {
              fVar20 = fVar60;
              if (fVar19 <= 1.0) {
                fVar20 = fVar19;
              }
              if ((fVar19 < 0.0) || (fVar65 = fVar20, fVar20 <= 0.0031308)) goto LAB_0011020c;
              fVar65 = powf(fVar20,0.4166667);
              fVar65 = (float)NEON_fmadd(fVar65,0x3f870a3d,0xbd6147ae);
            }
            uVar46 = NEON_cmlt(uVar64,0,4);
            uVar2 = (uint)fVar18 & 0x7fffffff;
            fVar19 = (fVar65 + -0.75) / 0.17;
            uVar36 = uVar64 & 0x7fffffff7fffffff;
            iVar9 = (int)(uVar36 >> 0x20);
            uVar43 = NEON_cmhi(0x7fffff007fffff,CONCAT44(iVar9 + -1,(int)uVar36 + -1),4);
            uVar29 = NEON_fcmgt(uVar64,uVar28,4);
            uVar43 = uVar43 & uVar46;
            fVar65 = fVar60;
            if (fVar19 <= 1.0) {
              fVar65 = fVar19;
            }
            uVar30 = NEON_cmeq(uVar36,0x7f8000007f800000,4);
            fVar20 = 0.0;
            if (0.0 <= fVar19) {
              fVar20 = fVar65;
            }
            uVar36 = NEON_cmhi(0x7f0000007f000000,
                               CONCAT44(iVar9 + -0x800000,(int)uVar36 + -0x800000),4);
            fVar65 = fVar60;
            if (fVar18 <= 1.0) {
              fVar65 = fVar18;
            }
            fVar63 = (float)NEON_fmadd(fVar20,0xc0000000,0x40400000);
            uVar36 = uVar36 & uVar46;
            uVar29 = NEON_bsl(uVar29,uVar28,uVar64,1);
            fVar63 = fVar20 * fVar20 * fVar63;
            fVar19 = 0.0;
            if ((uVar2 != 0x7f800000 && (-1 < (int)fVar18 || 0x7ffffe < uVar2 - 1)) &&
                (-1 < (int)fVar18 || 0x7e < uVar2 - 0x800000 >> 0x18)) {
              fVar19 = fVar65;
            }
            bVar52 = (byte)((ulong)uVar29 >> 0x18) &
                     ~((byte)(uVar43 >> 0x18) | (byte)((ulong)uVar30 >> 0x18) |
                      (byte)(uVar36 >> 0x18));
            fVar65 = (float)CONCAT13(bVar52,CONCAT12((byte)((ulong)uVar29 >> 0x10) &
                                                     ~((byte)(uVar43 >> 0x10) |
                                                       (byte)((ulong)uVar30 >> 0x10) |
                                                      (byte)(uVar36 >> 0x10)),
                                                     CONCAT11((byte)((ulong)uVar29 >> 8) &
                                                              ~((byte)(uVar43 >> 8) |
                                                                (byte)((ulong)uVar30 >> 8) |
                                                               (byte)(uVar36 >> 8)),
                                                              (byte)uVar29 &
                                                              ~((byte)uVar43 | (byte)uVar30 |
                                                               (byte)uVar36))));
            bVar53 = (byte)((ulong)uVar29 >> 0x38) &
                     ~((byte)(uVar43 >> 0x38) | (byte)((ulong)uVar30 >> 0x38) |
                      (byte)(uVar36 >> 0x38));
            fVar20 = 1.0 - fVar63;
            fVar18 = (float)(CONCAT17(bVar53,CONCAT16((byte)((ulong)uVar29 >> 0x30) &
                                                      ~((byte)(uVar43 >> 0x30) |
                                                        (byte)((ulong)uVar30 >> 0x30) |
                                                       (byte)(uVar36 >> 0x30)),
                                                      CONCAT15((byte)((ulong)uVar29 >> 0x28) &
                                                               ~((byte)(uVar43 >> 0x28) |
                                                                 (byte)((ulong)uVar30 >> 0x28) |
                                                                (byte)(uVar36 >> 0x28)),
                                                               CONCAT14((byte)((ulong)uVar29 >> 0x20
                                                                              ) & ~((byte)(uVar43 >>
                                                                                          0x20) |
                                                                                    (byte)((ulong)
                                                  uVar30 >> 0x20) | (byte)(uVar36 >> 0x20)),fVar65))
                                                  )) >> 0x20);
            if (((fVar19 == 0.0) && (fVar65 == 0.0)) && (fVar18 == 0.0)) {
joined_r0x00111378:
              if (pfVar3 == (float *)0x0) goto LAB_00110330;
LAB_0011035c:
              fVar56 = (float)uVar13;
              fVar54 = (float)(uVar16 & 0xffffffff);
              fVar50 = (float)NEON_ucvtf(uVar37);
              fVar21 = fVar50;
              fVar58 = fVar17;
              if (fVar56 < fVar50) {
                fVar58 = (fVar56 + -1.0) - fVar54;
                fVar21 = fVar56;
                fVar54 = fVar17;
                fVar56 = fVar50;
              }
              fVar21 = (float)leicaShadingDelta(fVar19,fVar65,fVar18,fVar54,fVar58,fVar56,fVar21,
                                                pfVar3,fVar31);
            }
            else {
              fVar55 = 1.0;
              fVar50 = fVar60;
              if (fVar58 <= 1.0) {
                fVar50 = fVar58;
              }
              fVar54 = fVar54 * fVar20;
              fVar22 = 0.0;
              if (0.0 <= fVar58) {
                fVar22 = fVar50;
              }
              fVar50 = 0.6;
              if (ABS(fVar58) != INFINITY) {
                fVar50 = fVar22;
              }
              fVar58 = 0.5;
              if (fVar54 <= 0.5) {
                fVar58 = fVar54;
              }
              fVar22 = -1.25;
              if (-1.25 <= fVar54) {
                fVar22 = fVar58;
              }
              fVar58 = -0.35;
              if (ABS(fVar54) != INFINITY) {
                fVar58 = fVar22;
              }
              fVar54 = 0.35;
              if (fVar56 <= 0.35) {
                fVar54 = fVar56;
              }
              fVar22 = -0.35;
              if (-0.35 <= fVar56) {
                fVar22 = fVar54;
              }
              fVar54 = 0.2;
              if (ABS(fVar56) != INFINITY) {
                fVar54 = fVar22;
              }
              uVar2 = (uint)fVar19 & 0x7fffffff;
              fVar56 = 0.0;
              if (((uVar2 == 0x7f800000 || (int)fVar19 < 0 && uVar2 - 1 < 0x7fffff) ||
                   (int)fVar19 < 0 && uVar2 - 0x800000 >> 0x18 < 0x7f) ||
                 (fVar56 = fVar19, fVar19 <= 0.04045)) {
                fVar56 = fVar56 / 12.92;
              }
              else {
                fVar56 = powf((fVar19 + 0.055) / 1.055,2.4);
              }
              uVar2 = (uint)fVar65 & 0x7fffffff;
              fVar22 = 0.0;
              if (((uVar2 == 0x7f800000 || (char)bVar52 < '\0' && uVar2 - 1 < 0x7fffff) ||
                   (char)bVar52 < '\0' && uVar2 - 0x800000 >> 0x18 < 0x7f) ||
                 (fVar22 = fVar65, fVar65 <= 0.04045)) {
                fVar22 = fVar22 / 12.92;
              }
              else {
                fVar22 = powf((fVar65 + 0.055) / 1.055,2.4);
              }
              uVar2 = (uint)fVar18 & 0x7fffffff;
              fVar23 = 0.0;
              if (((uVar2 == 0x7f800000 || (char)bVar53 < '\0' && uVar2 - 1 < 0x7fffff) ||
                   (char)bVar53 < '\0' && uVar2 - 0x800000 >> 0x18 < 0x7f) ||
                 (fVar23 = fVar18, fVar18 <= 0.04045)) {
                fVar23 = fVar23 / 12.92;
              }
              else {
                fVar23 = powf((fVar18 + 0.055) / 1.055,2.4);
              }
              uVar32 = NEON_fmadd(fVar56,0x3e6a784f,fVar22 * 0.6917385);
              fVar57 = (float)NEON_fmadd(fVar23,0x3da2612d,uVar32);
              fVar24 = 0.0;
              if (ABS(fVar57) == INFINITY) {
LAB_00110b98:
                fVar24 = fVar24 * 12.92;
              }
              else {
                fVar26 = fVar60;
                if (fVar57 <= 1.0) {
                  fVar26 = fVar57;
                }
                if ((fVar57 < 0.0) || (fVar24 = fVar26, fVar26 <= 0.0031308)) goto LAB_00110b98;
                fVar24 = powf(fVar26,0.4166667);
                fVar24 = (float)NEON_fmadd(fVar24,0x3f870a3d,0xbd6147ae);
              }
              fVar26 = 0.96;
              uVar29 = NEON_fmov(0x40400000,4);
              if (0.0 < fVar58) {
                fVar26 = 0.75;
              }
              fVar25 = 0.04000002;
              if (0.0 < fVar58) {
                fVar25 = 0.23;
              }
              uVar30 = CONCAT44((fVar24 - fVar26) / fVar25,(fVar24 + -0.06) / 0.19);
              fVar34 = (fVar24 + -0.75) / 0.23;
              uVar44 = NEON_fcmgt(uVar30,uVar28,4);
              uVar40 = NEON_fcmlt(uVar30,0,4);
              uVar30 = NEON_bit(uVar30,uVar28,uVar44,1);
              fVar25 = (float)CONCAT13((byte)((ulong)uVar30 >> 0x18) &
                                       ~(byte)((ulong)uVar40 >> 0x18),
                                       CONCAT12((byte)((ulong)uVar30 >> 0x10) &
                                                ~(byte)((ulong)uVar40 >> 0x10),
                                                CONCAT11((byte)((ulong)uVar30 >> 8) &
                                                         ~(byte)((ulong)uVar40 >> 8),
                                                         (byte)uVar30 & ~(byte)uVar40)));
              fVar27 = (float)(CONCAT17((byte)((ulong)uVar30 >> 0x38) &
                                        ~(byte)((ulong)uVar40 >> 0x38),
                                        CONCAT16((byte)((ulong)uVar30 >> 0x30) &
                                                 ~(byte)((ulong)uVar40 >> 0x30),
                                                 CONCAT15((byte)((ulong)uVar30 >> 0x28) &
                                                          ~(byte)((ulong)uVar40 >> 0x28),
                                                          CONCAT14((byte)((ulong)uVar30 >> 0x20) &
                                                                   ~(byte)((ulong)uVar40 >> 0x20),
                                                                   fVar25)))) >> 0x20);
              fVar38 = (float)uVar29;
              fVar66 = (float)((ulong)uVar29 >> 0x20);
              fVar26 = fVar55;
              if (fVar34 <= 1.0) {
                fVar26 = fVar34;
              }
              fVar42 = fVar25 * fVar25 * (fVar38 + fVar25 * -2.0);
              fVar25 = 0.0;
              if (0.0 <= fVar34) {
                fVar25 = fVar26;
              }
              fVar26 = (float)NEON_fmadd(fVar25,0xc0000000,0x40400000);
              fVar39 = (float)NEON_fmadd(fVar50,0xbe19999a,0x3f800000);
              fVar34 = (float)NEON_fmadd(fVar50,0xbf0ccccd,0x3f800000);
              fVar27 = exp2f(fVar39 * fVar58 * (1.0 - fVar27 * fVar27 * (fVar66 + fVar27 * -2.0)) *
                                               fVar42);
              uVar29 = NEON_fcmgt(0x3a83126f3a83126f,CONCAT44(fVar65,fVar19),4);
              uVar29 = NEON_bit(CONCAT44(fVar65,fVar19),0x3a83126f3a83126f,uVar29,1);
              fVar39 = fVar65 / (float)uVar29;
              fVar41 = fVar18 / (float)((ulong)uVar29 >> 0x20);
              fVar47 = (fVar39 + -0.9) / 0.15;
              fVar57 = fVar57 * fVar27;
              fVar58 = fVar55;
              if (fVar57 <= 1.0) {
                fVar58 = fVar57;
              }
              fVar51 = (fVar41 + -0.9) / 0.15;
              fVar35 = 0.0;
              if (0.0 <= fVar57) {
                fVar35 = fVar58;
              }
              fVar58 = fVar65;
              if (fVar65 <= fVar19) {
                fVar58 = fVar19;
              }
              fVar57 = fVar18;
              if (fVar18 <= fVar58) {
                fVar57 = fVar58;
              }
              fVar58 = fVar65;
              if (fVar19 <= fVar65) {
                fVar58 = fVar19;
              }
              fVar62 = (fVar24 + -0.03) / 0.15;
              fVar49 = fVar18;
              if (fVar58 <= fVar18) {
                fVar49 = fVar58;
              }
              fVar58 = fVar57;
              if (fVar57 <= 0.0001) {
                fVar58 = 0.0001;
              }
              uVar29 = NEON_fmov(0x40800000,4);
              fVar61 = fVar55;
              if (fVar47 <= 1.0) {
                fVar61 = fVar47;
              }
              uVar29 = CONCAT44((fVar41 + (float)((ulong)DAT_00102fa8 >> 0x20)) *
                                (float)((ulong)uVar29 >> 0x20),(fVar39 + (float)DAT_00102fa8) / 0.2)
              ;
              fVar41 = 0.0;
              fVar39 = 0.0;
              if (0.0 <= fVar47) {
                fVar39 = fVar61;
              }
              fVar47 = fVar55;
              if (fVar51 <= 1.0) {
                fVar47 = fVar51;
              }
              uVar30 = NEON_fcmgt(uVar29,uVar28,4);
              fVar61 = fVar41;
              if (0.0 <= fVar51) {
                fVar61 = fVar47;
              }
              uVar30 = NEON_bsl(uVar30,uVar28,uVar29,1);
              uVar29 = NEON_fcmlt(uVar29,0,4);
              fVar47 = fVar55;
              if (fVar62 <= 1.0) {
                fVar47 = fVar62;
              }
              fVar45 = (float)CONCAT13((byte)((ulong)uVar30 >> 0x18) &
                                       ~(byte)((ulong)uVar29 >> 0x18),
                                       CONCAT12((byte)((ulong)uVar30 >> 0x10) &
                                                ~(byte)((ulong)uVar29 >> 0x10),
                                                CONCAT11((byte)((ulong)uVar30 >> 8) &
                                                         ~(byte)((ulong)uVar29 >> 8),
                                                         (byte)uVar30 & ~(byte)uVar29)));
              fVar51 = fVar41;
              if (0.0 <= fVar62) {
                fVar51 = fVar47;
              }
              fVar47 = (float)(CONCAT17((byte)((ulong)uVar30 >> 0x38) &
                                        ~(byte)((ulong)uVar29 >> 0x38),
                                        CONCAT16((byte)((ulong)uVar30 >> 0x30) &
                                                 ~(byte)((ulong)uVar29 >> 0x30),
                                                 CONCAT15((byte)((ulong)uVar30 >> 0x28) &
                                                          ~(byte)((ulong)uVar29 >> 0x28),
                                                          CONCAT14((byte)((ulong)uVar30 >> 0x20) &
                                                                   ~(byte)((ulong)uVar29 >> 0x20),
                                                                   fVar45)))) >> 0x20);
              uVar29 = CONCAT44((fVar24 + (float)((ulong)DAT_00102fb0 >> 0x20)) /
                                (float)((ulong)DAT_00102f78 >> 0x20),
                                ((fVar57 - fVar49) / fVar58 + (float)DAT_00102fb0) /
                                (float)DAT_00102f78);
              if (fVar65 <= fVar18) {
                fVar18 = fVar65;
              }
              fVar58 = (float)NEON_fmadd(fVar39,0xc0000000,0x40400000);
              uVar30 = NEON_fcmgt(uVar29,uVar28,4);
              fVar65 = ((fVar18 - fVar19) + -0.015) / 0.085;
              uVar40 = NEON_fcmlt(uVar29,0,4);
              fVar49 = (float)NEON_fmadd(fVar61,0xc0000000,0x40400000);
              uVar29 = NEON_bit(uVar29,uVar28,uVar30,1);
              fVar19 = (float)CONCAT13((byte)((ulong)uVar29 >> 0x18) &
                                       ~(byte)((ulong)uVar40 >> 0x18),
                                       CONCAT12((byte)((ulong)uVar29 >> 0x10) &
                                                ~(byte)((ulong)uVar40 >> 0x10),
                                                CONCAT11((byte)((ulong)uVar29 >> 8) &
                                                         ~(byte)((ulong)uVar40 >> 8),
                                                         (byte)uVar29 & ~(byte)uVar40)));
              fVar57 = (float)(CONCAT17((byte)((ulong)uVar29 >> 0x38) &
                                        ~(byte)((ulong)uVar40 >> 0x38),
                                        CONCAT16((byte)((ulong)uVar29 >> 0x30) &
                                                 ~(byte)((ulong)uVar40 >> 0x30),
                                                 CONCAT15((byte)((ulong)uVar29 >> 0x28) &
                                                          ~(byte)((ulong)uVar40 >> 0x28),
                                                          CONCAT14((byte)((ulong)uVar29 >> 0x20) &
                                                                   ~(byte)((ulong)uVar40 >> 0x20),
                                                                   fVar19)))) >> 0x20);
              fVar62 = (float)NEON_fmadd(fVar51,0xc0000000,0x40400000);
              fVar18 = fVar55;
              if (fVar65 <= 1.0) {
                fVar18 = fVar65;
              }
              if (0.0 <= fVar65) {
                fVar41 = fVar18;
              }
              fVar65 = (1.0 - fVar61 * fVar61 * fVar49) *
                       fVar45 * fVar45 * (fVar38 + fVar45 * -2.0) * (1.0 - fVar39 * fVar39 * fVar58)
                       * fVar47 * fVar47 * (fVar66 + fVar47 * -2.0);
              fVar18 = (float)NEON_fmadd(fVar41,0xc0000000,0x40400000);
              fVar39 = (float)NEON_fmadd(fVar65,0xbf4ccccd,0x3f800000);
              fVar58 = (float)NEON_fmadd(fVar41 * fVar41 * fVar18,0xbf666666,0x3f800000);
              fVar58 = fVar58 * fVar39 * fVar51 * fVar51 * fVar62 *
                                         (fVar21 - fVar57 * fVar57 * (fVar66 + fVar57 * -2.0)) *
                                         ((float)uVar28 - fVar19 * fVar19 * (fVar38 + fVar19 * -2.0)
                                         );
              fVar21 = (float)NEON_fmadd(fVar54 * 0.2,fVar58,0x3f800000);
              fVar18 = (float)NEON_fmadd(fVar54 * 0.75,fVar58,0x3f800000);
              fVar54 = (float)NEON_fmadd(fVar54 * -0.9,fVar58,0x3f800000);
              uVar32 = NEON_fmadd(fVar56 * fVar27 * fVar18,0x3e6a784f,
                                  fVar22 * fVar27 * fVar21 * 0.6917385);
              fVar58 = (float)NEON_fmadd(fVar23 * fVar27 * fVar54,0x3da2612d,uVar32);
              fVar19 = fVar35 / fVar58;
              if (fVar58 <= 1e-06) {
                fVar19 = 1.0;
              }
              fVar58 = fVar23;
              if (fVar23 <= fVar56) {
                fVar58 = fVar56;
              }
              uVar40 = CONCAT44(fVar23,fVar22);
              uVar30 = NEON_fcmgt(uVar40,CONCAT44(fVar22,fVar56),4);
              uVar29 = NEON_ext(uVar40,(ulong)(uint)fVar56,4,1);
              uVar30 = NEON_bit(CONCAT44(fVar22,fVar56),uVar40,uVar30,1);
              fVar57 = ((fVar22 - fVar58) + -0.015) / 0.185;
              uVar29 = CONCAT44((((float)((ulong)uVar29 >> 0x20) - (float)((ulong)uVar30 >> 0x20)) +
                                -0.015) / 0.185,(((float)uVar29 - (float)uVar30) + -0.015) / 0.185);
              fVar24 = (fVar24 + -0.03) / 0.19;
              fVar58 = fVar55;
              if (fVar57 <= 1.0) {
                fVar58 = fVar57;
              }
              uVar30 = NEON_fcmgt(uVar29,uVar28,4);
              uVar40 = NEON_fcmlt(uVar29,0,4);
              fVar39 = 0.0;
              if (0.0 <= fVar57) {
                fVar39 = fVar58;
              }
              uVar29 = NEON_bsl(uVar30,uVar28,uVar29,1);
              fVar57 = (float)CONCAT13((byte)((ulong)uVar29 >> 0x18) &
                                       ~(byte)((ulong)uVar40 >> 0x18),
                                       CONCAT12((byte)((ulong)uVar29 >> 0x10) &
                                                ~(byte)((ulong)uVar40 >> 0x10),
                                                CONCAT11((byte)((ulong)uVar29 >> 8) &
                                                         ~(byte)((ulong)uVar40 >> 8),
                                                         (byte)uVar29 & ~(byte)uVar40)));
              fVar41 = (float)(CONCAT17((byte)((ulong)uVar29 >> 0x38) &
                                        ~(byte)((ulong)uVar40 >> 0x38),
                                        CONCAT16((byte)((ulong)uVar29 >> 0x30) &
                                                 ~(byte)((ulong)uVar40 >> 0x30),
                                                 CONCAT15((byte)((ulong)uVar29 >> 0x28) &
                                                          ~(byte)((ulong)uVar40 >> 0x28),
                                                          CONCAT14((byte)((ulong)uVar29 >> 0x20) &
                                                                   ~(byte)((ulong)uVar40 >> 0x20),
                                                                   fVar57)))) >> 0x20);
              fVar58 = fVar55;
              if (fVar24 <= 1.0) {
                fVar58 = fVar24;
              }
              fVar47 = 0.0;
              if (0.0 <= fVar24) {
                fVar47 = fVar58;
              }
              fVar58 = (float)NEON_fmadd(fVar47,0xc0000000,0x40400000);
              fVar24 = (float)NEON_fmadd(fVar39,0xc0000000,0x40400000);
              uVar32 = NEON_fmadd(fVar57 * fVar57 * (fVar38 + fVar57 * -2.0) +
                                  fVar41 * fVar41 * (fVar66 + fVar41 * -2.0),0x3d0f5c29,0x3db851ec);
              fVar58 = (float)NEON_fmadd(uVar32,fVar34 * (1.0 - fVar25 * fVar25 * fVar26) * fVar42,
                                         fVar50 * 0.28 * (1.0 - fVar47 * fVar47 * fVar58));
              fVar24 = (float)NEON_fmadd(fVar39 * fVar39 * fVar24,0xbf3851ec,0x3f800000);
              fVar50 = (float)NEON_fmadd(fVar65,0xbf0ccccd,0x3f800000);
              fVar50 = fVar50 * fVar24 * fVar58;
              fVar65 = 0.58;
              if (fVar50 <= 0.58) {
                fVar65 = fVar50;
              }
              fVar58 = fVar55;
              if (0.0 <= fVar50) {
                fVar58 = 1.0 - fVar65;
              }
              fVar56 = (float)NEON_fmadd(fVar56 * fVar27 * fVar18 * fVar19 - fVar35,fVar58,fVar35);
              fVar21 = (float)NEON_fmadd(fVar22 * fVar27 * fVar21 * fVar19 - fVar35,fVar58,fVar35);
              fVar65 = (float)NEON_fmadd(fVar23 * fVar27 * fVar54 * fVar19 - fVar35,fVar58,fVar35);
              fVar18 = fVar21;
              if (fVar56 <= fVar21) {
                fVar18 = fVar56;
              }
              fVar54 = fVar65;
              if (fVar18 <= fVar65) {
                fVar54 = fVar18;
              }
              fVar18 = fVar21;
              if (fVar21 <= fVar56) {
                fVar18 = fVar56;
              }
              fVar58 = fVar65;
              if (fVar65 <= fVar18) {
                fVar58 = fVar18;
              }
              if (fVar54 < 0.0) {
                fVar18 = fVar35 - fVar54;
                if (fVar35 - fVar54 <= 1e-06) {
                  fVar18 = 1e-06;
                }
                fVar55 = (float)NEON_fminnm(fVar35 / fVar18,0x3f800000);
              }
              fVar18 = fVar55;
              if (1.0 < fVar58) {
                fVar18 = fVar58 - fVar35;
                if (fVar58 - fVar35 <= 1e-06) {
                  fVar18 = 1e-06;
                }
                fVar18 = (1.0 - fVar35) / fVar18;
                if (fVar55 <= fVar18) {
                  fVar18 = fVar55;
                }
              }
              fVar54 = (float)NEON_fmadd(fVar56 - fVar35,fVar18,fVar35);
              fVar56 = (float)NEON_fmadd(fVar21 - fVar35,fVar18,fVar35);
              fVar21 = fVar60;
              if (fVar54 <= 1.0) {
                fVar21 = fVar54;
              }
              fVar58 = 0.0;
              if (0.0 <= fVar54) {
                fVar58 = fVar21;
              }
              fVar65 = (float)NEON_fmadd(fVar65 - fVar35,fVar18,fVar35);
              fVar18 = fVar60;
              if (fVar56 <= 1.0) {
                fVar18 = fVar56;
              }
              fVar21 = 0.0;
              if (0.0 <= fVar56) {
                fVar21 = fVar18;
              }
              uVar2 = (uint)fVar58 & 0x7fffffff;
              fVar18 = fVar60;
              if (fVar65 <= 1.0) {
                fVar18 = fVar65;
              }
              fVar54 = 0.0;
              if (0.0 <= fVar65) {
                fVar54 = fVar18;
              }
              fVar19 = 0.0;
              if (((0x7f800000 < uVar2 ||
                   (uVar2 == 0x7f800000 || (int)fVar58 < 0 && uVar2 - 1 < 0x7fffff)) ||
                   (int)fVar58 < 0 && uVar2 - 0x800000 >> 0x18 < 0x7f) ||
                 (fVar19 = fVar58, fVar58 <= 0.0031308)) {
                fVar19 = fVar19 * 12.92;
              }
              else {
                fVar18 = powf(fVar58,0.4166667);
                fVar19 = (float)NEON_fmadd(fVar18,0x3f870a3d,0xbd6147ae);
              }
              uVar2 = (uint)fVar21 & 0x7fffffff;
              fVar65 = 0.0;
              if (((0x7f800000 < uVar2 ||
                   (uVar2 == 0x7f800000 || (int)fVar21 < 0 && uVar2 - 1 < 0x7fffff)) ||
                   (int)fVar21 < 0 && uVar2 - 0x800000 >> 0x18 < 0x7f) ||
                 (fVar65 = fVar21, fVar21 <= 0.0031308)) {
                fVar65 = fVar65 * 12.92;
              }
              else {
                fVar18 = powf(fVar21,0.4166667);
                fVar65 = (float)NEON_fmadd(fVar18,0x3f870a3d,0xbd6147ae);
              }
              uVar2 = (uint)fVar54 & 0x7fffffff;
              fVar18 = 0.0;
              if (((uVar2 < 0x7f800001 &&
                   (uVar2 != 0x7f800000 && (-1 < (int)fVar54 || 0x7ffffe < uVar2 - 1))) &&
                   (-1 < (int)fVar54 || 0x7e < uVar2 - 0x800000 >> 0x18)) &&
                 (fVar18 = fVar54, 0.0031308 < fVar54)) {
                fVar18 = powf(fVar54,0.4166667);
                fVar18 = (float)NEON_fmadd(fVar18,0x3f870a3d,0xbd6147ae);
                goto joined_r0x00111378;
              }
              fVar18 = fVar18 * 12.92;
              if (pfVar3 != (float *)0x0) goto LAB_0011035c;
LAB_00110330:
              fVar21 = 0.0;
            }
            fVar54 = fVar20 * 1.25;
            if (0.0 <= fVar21) {
              fVar54 = 1.0;
            }
            fVar21 = fVar21 * fVar54;
            fVar19 = fVar19 + fVar21;
            fVar65 = fVar65 + fVar21;
            fVar18 = fVar18 + fVar21;
            fVar21 = fVar60;
            if (fVar19 <= 1.0) {
              fVar21 = fVar19;
            }
            in_s1 = 0.0;
            if (0.0 <= fVar19) {
              in_s1 = fVar21;
            }
            fVar21 = fVar60;
            if (fVar65 <= 1.0) {
              fVar21 = fVar65;
            }
            in_s2 = 0.0;
            if (0.0 <= fVar65) {
              in_s2 = fVar21;
            }
            fVar21 = fVar60;
            if (fVar18 <= 1.0) {
              fVar21 = fVar18;
            }
            fVar65 = 0.0;
            if (0.0 <= fVar18) {
              fVar65 = fVar21;
            }
            if (fVar63 < 1.0) {
              uVar37 = (uint)in_s1 & 0x7fffffff;
              fVar18 = 0.0;
              if (((0x7f800000 < uVar37 ||
                   (uVar37 == 0x7f800000 || (int)in_s1 < 0 && uVar37 - 1 < 0x7fffff)) ||
                   (int)in_s1 < 0 && uVar37 - 0x800000 >> 0x18 < 0x7f) ||
                 (fVar18 = in_s1, in_s1 <= 0.04045)) {
                fVar18 = fVar18 / 12.92;
              }
              else {
                fVar18 = powf((in_s1 + 0.055) / 1.055,2.4);
              }
              uVar37 = (uint)in_s2 & 0x7fffffff;
              fVar21 = 0.0;
              if (((0x7f800000 < uVar37 ||
                   (uVar37 == 0x7f800000 || (int)in_s2 < 0 && uVar37 - 1 < 0x7fffff)) ||
                   (int)in_s2 < 0 && uVar37 - 0x800000 >> 0x18 < 0x7f) ||
                 (fVar21 = in_s2, in_s2 <= 0.04045)) {
                fVar21 = fVar21 / 12.92;
              }
              else {
                fVar21 = powf((in_s2 + 0.055) / 1.055,2.4);
              }
              uVar37 = (uint)fVar65 & 0x7fffffff;
              fVar54 = 0.0;
              if (((0x7f800000 < uVar37 ||
                   (uVar37 == 0x7f800000 || (int)fVar65 < 0 && uVar37 - 1 < 0x7fffff)) ||
                   (int)fVar65 < 0 && uVar37 - 0x800000 >> 0x18 < 0x7f) ||
                 (fVar54 = fVar65, fVar65 <= 0.04045)) {
                fVar54 = fVar54 / 12.92;
              }
              else {
                fVar54 = powf((fVar65 + 0.055) / 1.055,2.4);
              }
              uVar32 = NEON_fmadd(fVar18,0x3e6a784f,fVar21 * 0.6917385);
              uVar33 = NEON_fmadd(fVar18,0x3ef91fd4,fVar21 * 0.2656677);
              fVar58 = (float)NEON_fmadd(fVar54,0x3da2612d,uVar32);
              uVar33 = NEON_fmadd(fVar54,0x3e4af979,uVar33);
              uVar59 = NEON_fmadd(fVar21,0x3d38c8cf,fVar54 * 1.043944);
              uVar32 = NEON_fmadd(uVar33,0x3f51ab74,fVar58 * 0.3619063);
              fVar65 = (float)NEON_fmadd(uVar59,0xbe03f77d,uVar32);
              fVar65 = cbrtf(fVar65);
              uVar32 = NEON_fmadd(uVar33,0x3d0719de,fVar58 * 0.9292868);
              fVar56 = (float)NEON_fmadd(uVar59,0x3d140c6e,uVar32);
              fVar56 = cbrtf(fVar56);
              uVar32 = NEON_fmadd(uVar33,0x3d455572,fVar58 * 0.2642395);
              uVar33 = NEON_fmadd(fVar65,0x3e578153,fVar56 * 0.7936178);
              fVar65 = (float)NEON_fmadd(uVar59,0x3f223031,uVar32);
              fVar65 = cbrtf(fVar65);
              local_b0 = 0;
              local_e0 = 0;
              local_100 = 0;
              uStack_f0 = 0;
              fVar56 = (float)NEON_fmadd(fVar65,0xbb856ec6,uVar33);
              local_d0 = 0;
              fVar65 = fVar60;
              if (fVar56 <= 1.0) {
                fVar65 = fVar56;
              }
              uStack_c0 = _UNK_00102eb8;
              uStack_c8 = _DAT_00102eb0;
              local_b8 = 0x3f000000;
              fVar58 = 0.0;
              if (0.0 <= fVar56) {
                fVar58 = fVar65;
              }
              uStack_f8 = DAT_00102f70;
              local_e8 = 0xc0be35b5;
              if (fVar58 <= 0.15) {
                lVar10 = 0;
              }
              else if (fVar58 <= 0.3) {
                lVar10 = 1;
              }
              else if (fVar58 <= 0.45) {
                lVar10 = 2;
              }
              else if (fVar58 <= 0.65) {
                lVar10 = 3;
              }
              else if (fVar58 <= 0.8) {
                lVar10 = 4;
              }
              else if (fVar58 <= 0.9) {
                lVar10 = 5;
              }
              else if (fVar58 <= 0.97) {
                lVar10 = 6;
              }
              else {
                lVar10 = 7;
              }
              lVar11 = lVar10 * 4;
              fVar56 = (float)(&DAT_00102fd0)[lVar10] - (float)(&DAT_00102fcc)[lVar10];
              fVar65 = (fVar58 - (float)(&DAT_00102fcc)[lVar10]) / fVar56;
              fVar58 = fVar65 * fVar65;
              fVar19 = fVar65 * fVar58;
              fVar31 = (float)NEON_fmadd(fVar58,0xc0000000,fVar19);
              fVar63 = (float)NEON_fnmsub(fVar19,0x40000000,fVar58 * 3.0);
              uVar32 = NEON_fmadd(fVar63 + 1.0,*(undefined4 *)((long)&local_d0 + lVar11),
                                  *(float *)((long)&local_100 + lVar11) * fVar56 * (fVar65 + fVar31)
                                 );
              uVar33 = NEON_fmadd(fVar19,0xc0000000,fVar58 * 3.0);
              uVar32 = NEON_fmadd(uVar33,*(undefined4 *)((long)&local_d0 + lVar11 + 4),uVar32);
              fVar56 = (float)NEON_fmadd(fVar56 * (fVar19 - fVar58),
                                         *(undefined4 *)((long)&local_100 + lVar11 + 4),uVar32);
              fVar65 = fVar60;
              if (fVar56 <= 1.0) {
                fVar65 = fVar56;
              }
              fVar58 = -0.0;
              if (0.0 <= fVar56) {
                fVar58 = fVar65 * -0.25;
              }
              fVar65 = exp2f(fVar20 * fVar58);
              fVar18 = fVar18 * fVar65;
              in_s1 = 0.0;
              if (ABS(fVar18) == INFINITY) {
LAB_001114e0:
                in_s1 = in_s1 * 12.92;
              }
              else {
                fVar56 = fVar60;
                if (fVar18 <= 1.0) {
                  fVar56 = fVar18;
                }
                if ((fVar18 < 0.0) || (in_s1 = fVar56, fVar56 <= 0.0031308)) goto LAB_001114e0;
                fVar18 = powf(fVar56,0.4166667);
                in_s1 = (float)NEON_fmadd(fVar18,0x3f870a3d,0xbd6147ae);
              }
              fVar21 = fVar21 * fVar65;
              in_s2 = 0.0;
              if (ABS(fVar21) == INFINITY) {
LAB_0011156c:
                in_s2 = in_s2 * 12.92;
              }
              else {
                fVar18 = fVar60;
                if (fVar21 <= 1.0) {
                  fVar18 = fVar21;
                }
                if ((fVar21 < 0.0) || (in_s2 = fVar18, fVar18 <= 0.0031308)) goto LAB_0011156c;
                fVar18 = powf(fVar18,0.4166667);
                in_s2 = (float)NEON_fmadd(fVar18,0x3f870a3d,0xbd6147ae);
              }
              fVar54 = fVar54 * fVar65;
              fVar65 = 0.0;
              if (ABS(fVar54) != INFINITY) {
                fVar18 = fVar60;
                if (fVar54 <= 1.0) {
                  fVar18 = fVar54;
                }
                if ((0.0 <= fVar54) && (fVar65 = fVar18, 0.0031308 < fVar18)) {
                  fVar18 = powf(fVar18,0.4166667);
                  fVar65 = (float)NEON_fmadd(fVar18,0x3f870a3d,0xbd6147ae);
                  goto LAB_0010f3b4;
                }
              }
              fVar65 = fVar65 * 12.92;
            }
LAB_0010f3b4:
            in_s1 = in_s1 * 255.0;
            in_s2 = in_s2 * 255.0;
            fVar65 = fVar65 * 255.0;
            iVar9 = (int)(long)in_s1;
          }
          if (0xfe < iVar9) {
            iVar9 = 0xff;
          }
          iVar12 = (int)(long)in_s2;
          if (0xfe < iVar12) {
            iVar12 = 0xff;
          }
          *pbVar1 = (byte)iVar9 & ((byte)(iVar9 >> 0x1f) ^ 0xff);
          uVar16 = uVar16 + 1;
          uVar15 = uVar15 + 4;
          pbVar1[1] = (byte)iVar12 & ((byte)(iVar12 >> 0x1f) ^ 0xff);
          iVar9 = (int)(long)fVar65;
          if (0xfe < iVar9) {
            iVar9 = 0xff;
          }
          pbVar1[2] = (byte)iVar9 & ((byte)(iVar9 >> 0x1f) ^ 0xff);
          puVar14 = *ppuVar8;
          uVar13 = (ulong)*puVar14;
        } while (uVar16 < uVar13);
      }
      local_120 = local_120 + 1;
    } while (local_120 != in_w2);
  }
  return;
}



/* 00111614 __thread_proxy[abi:ne180000]<std::__ndk1::tuple<std::__ndk1::unique_ptr<std::__ndk1::__thread_struct,std::__ndk1::default_delete<std::__ndk1::__thread_struct>>,(anonymous_namespace)::applyLeicaFilter(_JNIEnv*,_jobject*,char_const*,float,float,float,float,float,bool,float,float)::$_0,unsigned_int,unsigned_int>> */

/* void* 
   std::__ndk1::__thread_proxy[abi:ne180000]<std::__ndk1::tuple<std::__ndk1::unique_ptr<std::__ndk1::__thread_struct,
   std::__ndk1::default_delete<std::__ndk1::__thread_struct> >, (anonymous
   namespace)::applyLeicaFilter(_JNIEnv*, _jobject*, char const*, float, float, float, float, float,
   bool, float, float)::$_0, unsigned int, unsigned int> >(void*) */

void * std::__ndk1::
       __thread_proxy_abi_ne180000_<std::__ndk1::tuple<std::__ndk1::unique_ptr<std::__ndk1::__thread_struct,std::__ndk1::default_delete<std::__ndk1::__thread_struct>>,(anonymous_namespace)::applyLeicaFilter(_JNIEnv*,_jobject*,char_const*,float,float,float,float,float,bool,float,float)::__0,unsigned_int,unsigned_int>>
                 (void *param_1)

{
  pthread_key_t __key;
  pthread_key_t *ppVar1;
  void *__pointer;
  __thread_struct *this;
  
                    /* try { // try from 0011162c to 0011163f has its CatchHandler @ 00111684 */
  ppVar1 = (pthread_key_t *)std::__ndk1::__thread_local_data();
                    /* WARNING: Load size is inaccurate */
  __pointer = *param_1;
  __key = *ppVar1;
  *(undefined8 *)param_1 = 0;
  pthread_setspecific(__key,__pointer);
  (anonymous_namespace)::
  applyLeicaFilter(_JNIEnv*,_jobject*,char_const*,float,float,float,float,float,bool,float,float)::
  $_0::operator()((int)param_1 + 8,*(uint *)((long)param_1 + 0x68));
                    /* WARNING: Load size is inaccurate */
  this = *param_1;
  *(undefined8 *)param_1 = 0;
  if (this != (__thread_struct *)0x0) {
    std::__ndk1::__thread_struct::~__thread_struct(this);
    operator_delete(this);
  }
  operator_delete(param_1);
  return (void *)0x0;
}



/* 00111698 ~unique_ptr[abi:ne180000] */

/* std::__ndk1::unique_ptr<std::__ndk1::tuple<std::__ndk1::unique_ptr<std::__ndk1::__thread_struct,
   std::__ndk1::default_delete<std::__ndk1::__thread_struct> >, (anonymous
   namespace)::applyLeicaFilter(_JNIEnv*, _jobject*, char const*, float, float, float, float, float,
   bool, float, float)::$_0, unsigned int, unsigned int>,
   std::__ndk1::default_delete<std::__ndk1::tuple<std::__ndk1::unique_ptr<std::__ndk1::__thread_struct,
   std::__ndk1::default_delete<std::__ndk1::__thread_struct> >, (anonymous
   namespace)::applyLeicaFilter(_JNIEnv*, _jobject*, char const*, float, float, float, float, float,
   bool, float, float)::$_0, unsigned int, unsigned int> > >::~unique_ptr[abi:ne180000]() */

void __thiscall
std::__ndk1::
unique_ptr<std::__ndk1::tuple<std::__ndk1::unique_ptr<std::__ndk1::__thread_struct,std::__ndk1::default_delete<std::__ndk1::__thread_struct>>,(anonymous_namespace)::applyLeicaFilter(_JNIEnv*,_jobject*,char_const*,float,float,float,float,float,bool,float,float)::$_0,unsigned_int,unsigned_int>,std::__ndk1::default_delete<std::__ndk1::tuple<std::__ndk1::unique_ptr<std::__ndk1::__thread_struct,std::__ndk1::default_delete<std::__ndk1::__thread_struct>>,(anonymous_namespace)::applyLeicaFilter(_JNIEnv*,_jobject*,char_const*,float,float,float,float,float,bool,float,float)::$_0,unsigned_int,unsigned_int>>>
::~unique_ptr_abi_ne180000_
          (unique_ptr<std::__ndk1::tuple<std::__ndk1::unique_ptr<std::__ndk1::__thread_struct,std::__ndk1::default_delete<std::__ndk1::__thread_struct>>,(anonymous_namespace)::applyLeicaFilter(_JNIEnv*,_jobject*,char_const*,float,float,float,float,float,bool,float,float)::__0,unsigned_int,unsigned_int>,std::__ndk1::default_delete<std::__ndk1::tuple<std::__ndk1::unique_ptr<std::__ndk1::__thread_struct,std::__ndk1::default_delete<std::__ndk1::__thread_struct>>,(anonymous_namespace)::applyLeicaFilter(_JNIEnv*,_jobject*,char_const*,float,float,float,float,float,bool,float,float)::__0,unsigned_int,unsigned_int>>>
           *this)

{
  __thread_struct **pp_Var1;
  __thread_struct *this_00;
  
  pp_Var1 = *(__thread_struct ***)this;
  *(undefined8 *)this = 0;
  if (pp_Var1 != (__thread_struct **)0x0) {
    this_00 = *pp_Var1;
    *pp_Var1 = (__thread_struct *)0x0;
    if (this_00 != (__thread_struct *)0x0) {
      std::__ndk1::__thread_struct::~__thread_struct(this_00);
      operator_delete(this_00);
    }
    operator_delete(pp_Var1);
    return;
  }
  return;
}



/* 001116e8 leicaShadingDelta */

/* leicaShadingDelta(float, float, float, float, float, float, float, float const*, float) */

float leicaShadingDelta(float param_1,float param_2,float param_3,float param_4,float param_5,
                       float param_6,float param_7,float *param_8,float param_9)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  
  fVar1 = (float)NEON_fmadd(param_6,0xbf000000,param_4 + 0.5);
  fVar1 = fVar1 / param_7;
  fVar12 = (param_5 + 0.5) / param_7 + -0.5;
  fVar11 = param_9 * 0.005;
  fVar2 = fVar12 + -0.5;
  fVar8 = (float)DAT_00102f20 * fVar11;
  fVar9 = (float)((ulong)DAT_00102f20 >> 0x20) * fVar11;
  fVar10 = fVar1 + -0.5;
  fVar9 = sinf((fVar2 + fVar9) * 78.233 + (fVar10 + fVar9) * 12.9898);
  fVar8 = sinf((fVar2 + fVar8) * 78.233 + (fVar10 + fVar8) * 12.9898);
  fVar3 = (float)DAT_00102f30 * fVar11;
  fVar7 = (float)((ulong)DAT_00102f30 >> 0x20) * fVar11;
  fVar7 = sinf((fVar2 + fVar7) * 78.233 + (fVar10 + fVar7) * 12.9898);
  fVar3 = sinf((fVar2 + fVar3) * 78.233 + (fVar10 + fVar3) * 12.9898);
  fVar4 = (float)DAT_00102f48 * fVar11;
  fVar11 = (float)((ulong)DAT_00102f48 >> 0x20) * fVar11;
  fVar11 = sinf((fVar2 + fVar11) * 78.233 + (fVar10 + fVar11) * 12.9898);
  fVar2 = sinf((fVar2 + fVar4) * 78.233 + (fVar10 + fVar4) * 12.9898);
  fVar1 = (float)NEON_fmadd(fVar1,fVar1,fVar12 * fVar12);
  fVar4 = param_8[6];
  fVar9 = (float)NEON_fmadd((((fVar8 * 43758.55 - (float)(int)(fVar8 * 43758.55)) + 0.0 +
                              (fVar9 * 43758.55 - (float)(int)(fVar9 * 43758.55)) +
                              (fVar3 * 43758.55 - (float)(int)(fVar3 * 43758.55)) +
                              (fVar7 * 43758.55 - (float)(int)(fVar7 * 43758.55)) +
                              (fVar2 * 43758.55 - (float)(int)(fVar2 * 43758.55)) +
                             (fVar11 * 43758.55 - (float)(int)(fVar11 * 43758.55))) / 6.0) * 0.04,
                            param_8[2],SQRT(fVar1));
  fVar8 = (fVar9 - *param_8) / (param_8[1] - *param_8);
  uVar5 = NEON_fmadd(param_1,0x3eff7cee,param_2 * 0.387);
  fVar7 = (float)NEON_fmadd(param_3,0x3de978d5,uVar5);
  fVar9 = 1.0;
  if (fVar8 <= 1.0) {
    fVar9 = fVar8;
  }
  fVar3 = 0.0;
  if (0.0 <= fVar8) {
    fVar3 = fVar9;
  }
  fVar8 = (float)NEON_fmadd(fVar3,0xc0000000,0x40400000);
  fVar9 = expf(param_8[4] * (param_8[5] - fVar7));
  fVar9 = param_8[7] + fVar4 / (fVar9 + 1.0);
  uVar6 = NEON_fmadd(param_1,0x3e991687,param_2 * 0.587);
  uVar5 = NEON_fmadd(1.0 - fVar9,fVar3 * fVar3 * fVar8,fVar9);
  fVar8 = (float)NEON_fmadd(param_3,0x3de978d5,uVar6);
  fVar9 = (float)NEON_fmadd(uVar5,param_8[3],0xbf800000);
  return fVar8 * fVar9;
}



/* 001119a8 __clang_call_terminate */

void __clang_call_terminate(void)

{
  __cxa_begin_catch();
                    /* WARNING: Subroutine does not return */
  std::terminate();
}



/* 001119b8 resize */

/* std::__ndk1::vector<float, std::__ndk1::allocator<float> >::resize(unsigned long) */

void __thiscall
std::__ndk1::vector<float,std::__ndk1::allocator<float>>::resize
          (vector<float,std::__ndk1::allocator<float>> *this,ulong param_1)

{
  ulong uVar1;
  
  uVar1 = *(long *)(this + 8) - *(long *)this >> 2;
  if (param_1 >= uVar1 && param_1 - uVar1 != 0) {
    __append(this,param_1 - uVar1);
    return;
  }
  if (param_1 < uVar1) {
    *(ulong *)(this + 8) = *(long *)this + param_1 * 4;
  }
  return;
}



/* 001119e4 vector */

/* std::__ndk1::vector<unsigned short, std::__ndk1::allocator<unsigned short> >::vector(unsigned
   long) */

void __thiscall
std::__ndk1::vector<unsigned_short,std::__ndk1::allocator<unsigned_short>>::vector
          (vector<unsigned_short,std::__ndk1::allocator<unsigned_short>> *this,ulong param_1)

{
  void *pvVar1;
  undefined8 uVar2;
  ulong __n;
  
  *(undefined8 *)this = 0;
  *(undefined8 *)(this + 8) = 0;
  *(undefined8 *)(this + 0x10) = 0;
  if (param_1 != 0) {
    if ((long)param_1 < 0) {
                    /* try { // try from 00111a4c to 00111a53 has its CatchHandler @ 00111a54 */
      uVar2 = __throw_length_error_abi_ne180000_();
                    /* catch() { ... } // from try @ 00111a10 with catch @ 00111a54
                       catch() { ... } // from try @ 00111a4c with catch @ 00111a54 */
      pvVar1 = *(void **)this;
      if (pvVar1 != (void *)0x0) {
        *(void **)(this + 8) = pvVar1;
        operator_delete(pvVar1);
      }
                    /* WARNING: Subroutine does not return */
      _Unwind_Resume(uVar2);
    }
    __n = param_1 * 2;
                    /* try { // try from 00111a10 to 00111a17 has its CatchHandler @ 00111a54 */
    pvVar1 = operator_new(__n);
    *(void **)this = pvVar1;
    *(void **)(this + 0x10) = (void *)((long)pvVar1 + param_1 * 2);
    memset(pvVar1,0,__n);
    *(void **)(this + 8) = (void *)((long)pvVar1 + __n);
  }
  return;
}



/* 00111a74 vector */

/* std::__ndk1::vector<float, std::__ndk1::allocator<float> >::vector(unsigned long) */

void __thiscall
std::__ndk1::vector<float,std::__ndk1::allocator<float>>::vector
          (vector<float,std::__ndk1::allocator<float>> *this,ulong param_1)

{
  void *pvVar1;
  undefined8 uVar2;
  ulong __n;
  
  *(undefined8 *)this = 0;
  *(undefined8 *)(this + 8) = 0;
  *(undefined8 *)(this + 0x10) = 0;
  if (param_1 != 0) {
    if (param_1 >> 0x3e != 0) {
                    /* try { // try from 00111ae0 to 00111ae7 has its CatchHandler @ 00111ae8 */
      uVar2 = __throw_length_error_abi_ne180000_();
                    /* catch() { ... } // from try @ 00111aa4 with catch @ 00111ae8
                       catch() { ... } // from try @ 00111ae0 with catch @ 00111ae8 */
      pvVar1 = *(void **)this;
      if (pvVar1 != (void *)0x0) {
        *(void **)(this + 8) = pvVar1;
        operator_delete(pvVar1);
      }
                    /* WARNING: Subroutine does not return */
      _Unwind_Resume(uVar2);
    }
    __n = param_1 * 4;
                    /* try { // try from 00111aa4 to 00111aab has its CatchHandler @ 00111ae8 */
    pvVar1 = operator_new(__n);
    *(void **)this = pvVar1;
    *(void **)(this + 0x10) = (void *)((long)pvVar1 + param_1 * 4);
    memset(pvVar1,0,__n);
    *(void **)(this + 8) = (void *)((long)pvVar1 + __n);
  }
  return;
}



/* 00111b08 develop */

/* WARNING: Removing unreachable block (ram,0x00113a68) */
/* WARNING: Removing unreachable block (ram,0x00113a70) */
/* WARNING: Removing unreachable block (ram,0x00113a84) */
/* WARNING: Removing unreachable block (ram,0x00113a9c) */
/* WARNING: Removing unreachable block (ram,0x00113aa8) */
/* WARNING: Removing unreachable block (ram,0x00113ab8) */
/* WARNING: Removing unreachable block (ram,0x00113af8) */
/* WARNING: Removing unreachable block (ram,0x00113ac0) */
/* WARNING: Removing unreachable block (ram,0x00113ad0) */
/* WARNING: Removing unreachable block (ram,0x00113afc) */
/* WARNING: Removing unreachable block (ram,0x00113c24) */
/* WARNING: Removing unreachable block (ram,0x00113c30) */
/* WARNING: Removing unreachable block (ram,0x00113b10) */
/* WARNING: Removing unreachable block (ram,0x00113c68) */
/* WARNING: Removing unreachable block (ram,0x00113c88) */
/* WARNING: Removing unreachable block (ram,0x00113c94) */
/* WARNING: Removing unreachable block (ram,0x00113ca4) */
/* WARNING: Removing unreachable block (ram,0x00113cc8) */
/* WARNING: Removing unreachable block (ram,0x00113ce0) */
/* WARNING: Removing unreachable block (ram,0x00113ce8) */
/* WARNING: Removing unreachable block (ram,0x00113b1c) */
/* WARNING: Removing unreachable block (ram,0x00113b24) */
/* WARNING: Removing unreachable block (ram,0x00113b34) */
/* WARNING: Removing unreachable block (ram,0x00113b3c) */
/* WARNING: Removing unreachable block (ram,0x00113b5c) */
/* WARNING: Removing unreachable block (ram,0x00114534) */
/* WARNING: Removing unreachable block (ram,0x00113a78) */
/* WARNING: Removing unreachable block (ram,0x00113b6c) */
/* WARNING: Removing unreachable block (ram,0x00113a00) */
/* WARNING: Removing unreachable block (ram,0x00113b7c) */
/* WARNING: Removing unreachable block (ram,0x00114528) */
/* WARNING: Removing unreachable block (ram,0x00114538) */
/* WARNING: Removing unreachable block (ram,0x00113b94) */
/* WARNING: Removing unreachable block (ram,0x00113ba8) */
/* WARNING: Removing unreachable block (ram,0x00113bb8) */
/* WARNING: Removing unreachable block (ram,0x00113be4) */
/* WARNING: Removing unreachable block (ram,0x00113bc0) */
/* WARNING: Removing unreachable block (ram,0x0011450c) */
/* WARNING: Removing unreachable block (ram,0x00113bcc) */
/* WARNING: Removing unreachable block (ram,0x00113be8) */
/* WARNING: Removing unreachable block (ram,0x00113c34) */
/* WARNING: Removing unreachable block (ram,0x00113bfc) */
/* WARNING: Removing unreachable block (ram,0x00113cec) */
/* WARNING: Removing unreachable block (ram,0x00113d0c) */
/* WARNING: Removing unreachable block (ram,0x00113d18) */
/* WARNING: Removing unreachable block (ram,0x00113d28) */
/* WARNING: Removing unreachable block (ram,0x00113d4c) */
/* WARNING: Removing unreachable block (ram,0x00113d64) */
/* WARNING: Removing unreachable block (ram,0x00113d6c) */
/* WARNING: Removing unreachable block (ram,0x00113c08) */
/* WARNING: Removing unreachable block (ram,0x00113c10) */
/* WARNING: Removing unreachable block (ram,0x00113c20) */
/* WARNING: Removing unreachable block (ram,0x00113c38) */
/* WARNING: Removing unreachable block (ram,0x00113c44) */
/* WARNING: Removing unreachable block (ram,0x00113c4c) */
/* WARNING: Removing unreachable block (ram,0x00113d8c) */
/* WARNING: Removing unreachable block (ram,0x00113e7c) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* software_raw::develop(unsigned short const*, software_raw::Calibration const&, bool,
   std::__ndk1::vector<float, std::__ndk1::allocator<float> > const&, std::__ndk1::vector<float,
   std::__ndk1::allocator<float> > const&) */

void __thiscall
software_raw::develop
          (software_raw *this,ushort *param_1,Calibration *param_2,bool param_3,vector *param_4,
          vector *param_5)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  float *pfVar4;
  undefined (*pauVar5) [16];
  undefined4 *puVar6;
  uint uVar7;
  int iVar8;
  float *pfVar9;
  float *pfVar10;
  float *pfVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  int iVar15;
  int iVar16;
  uint uVar17;
  uint uVar18;
  undefined8 *puVar19;
  float *pfVar20;
  float *pfVar21;
  float *pfVar22;
  bool bVar23;
  void *pvVar24;
  void *pvVar25;
  void *pvVar26;
  undefined4 *puVar27;
  undefined4 *puVar28;
  runtime_error *prVar29;
  int iVar30;
  uint uVar31;
  uint uVar32;
  float *pfVar33;
  long lVar34;
  int iVar35;
  void **in_x8;
  ulong __n;
  ulong uVar36;
  void *pvVar37;
  undefined4 *puVar38;
  long lVar39;
  undefined4 *puVar40;
  float *pfVar41;
  uint uVar42;
  int iVar43;
  ulong uVar44;
  long lVar45;
  long lVar46;
  undefined4 *puVar47;
  int iVar48;
  int iVar49;
  undefined8 *puVar50;
  undefined8 *puVar51;
  long lVar52;
  int iVar53;
  long lVar54;
  ulong uVar55;
  long lVar56;
  int iVar57;
  ulong uVar58;
  long lVar59;
  uint *puVar60;
  ulong uVar61;
  long lVar62;
  undefined8 uVar63;
  undefined4 uVar64;
  undefined8 uVar65;
  float fVar66;
  undefined4 uVar67;
  undefined4 uVar68;
  undefined4 uVar69;
  float fVar70;
  int iVar71;
  int iVar72;
  int iVar73;
  int iVar74;
  undefined auVar75 [16];
  undefined auVar76 [16];
  undefined auVar77 [16];
  float fVar78;
  float fVar79;
  undefined4 uVar80;
  float fVar81;
  float fVar82;
  float fVar83;
  float fVar84;
  float fVar85;
  undefined8 uVar86;
  undefined4 uVar87;
  undefined4 uVar88;
  float fVar89;
  float fVar90;
  float fVar91;
  undefined4 uVar92;
  float fVar93;
  undefined4 uVar94;
  float fVar95;
  undefined4 uVar96;
  float fVar97;
  float fVar98;
  float fVar99;
  float fVar100;
  float fVar101;
  float fVar102;
  float fVar103;
  int iVar104;
  float fVar105;
  int iVar106;
  float fVar107;
  undefined8 uVar108;
  float fVar109;
  float fVar110;
  float fVar111;
  float fVar112;
  float fVar113;
  float fVar114;
  float fVar115;
  void *local_1110;
  float local_10d8 [256];
  float local_cd8 [256];
  float local_8d8 [256];
  float local_4d8 [4];
  undefined8 uStack_4c8;
  void *apvStack_4c0 [128];
  void *local_c0;
  void *local_b8;
  void *local_b0;
  
  uVar12 = *(uint *)param_1;
  uVar58 = (ulong)uVar12;
  if ((7 < (int)uVar12) && (uVar12 < 0x2001)) {
    uVar14 = *(uint *)(param_1 + 2);
    if ((0xffffe006 < uVar14 - 0x2001) && (uVar13 = *(uint *)(param_1 + 4), uVar13 < 4)) {
      iVar71 = *(int *)(param_1 + 6);
      iVar72 = iVar71 + -1;
      if (0 < iVar71) {
        iVar73 = *(int *)(param_1 + 8);
        iVar74 = iVar73 + -1;
        if (0 < iVar73) {
          pfVar41 = *(float **)(param_1 + 0x40);
          if ((ulong)(uint)(iVar71 * iVar73 * 4) ==
              (long)*(float **)(param_1 + 0x44) - (long)pfVar41 >> 2) {
            pfVar10 = *(float **)(param_1 + 0x4c);
            if ((long)*(float **)(param_1 + 0x50) - (long)pfVar10 == 0x3000) {
              if ((((ABS(*(float *)(param_1 + 0xc)) != INFINITY) &&
                   (fVar82 = *(float *)(param_1 + 10), ABS(fVar82) != INFINITY)) &&
                  (*(float *)(param_1 + 0xc) < fVar82)) &&
                 (((uVar31 = *(uint *)(param_1 + 0x14),
                   (uVar31 != 0xffffffff && (int)(uVar31 + 1) < 0 == SCARRY4(uVar31,1)) &&
                   (uVar31 & 0x7fffffff) - 0x800000 >> 0x18 < 0x7f || uVar31 - 1 < 0x7fffff &&
                   (ABS(*(float *)(param_1 + 0xe)) != INFINITY)) &&
                  (*(float *)(param_1 + 0xe) < fVar82)))) {
                uVar31 = *(uint *)(param_1 + 0x16);
                bVar23 = -1 < (int)uVar31;
                uVar42 = (uVar31 & 0x7fffffff) - 0x800000 >> 0x18;
                if (((((bVar23 && uVar42 < 0x7e || bVar23 && uVar42 == 0x7e) ||
                      uVar31 - 1 < 0x7ffffe) ||
                      ((!bVar23 || uVar42 >= 0x7e) && (!bVar23 || uVar42 != 0x7e)) &&
                      uVar31 - 1 == 0x7ffffe) && (ABS(*(float *)(param_1 + 0x10)) != INFINITY)) &&
                   (*(float *)(param_1 + 0x10) < fVar82)) {
                  uVar31 = *(uint *)(param_1 + 0x18);
                  bVar23 = -1 < (int)uVar31;
                  uVar42 = (uVar31 & 0x7fffffff) - 0x800000 >> 0x18;
                  if (((((bVar23 && uVar42 < 0x7e || bVar23 && uVar42 == 0x7e) ||
                        uVar31 - 1 < 0x7ffffe) ||
                        ((!bVar23 || uVar42 >= 0x7e) && (!bVar23 || uVar42 != 0x7e)) &&
                        uVar31 - 1 == 0x7ffffe) && (ABS(*(float *)(param_1 + 0x12)) != INFINITY)) &&
                     (*(float *)(param_1 + 0x12) < fVar82)) {
                    uVar31 = *(uint *)(param_1 + 0x1a);
                    bVar23 = -1 < (int)uVar31;
                    uVar42 = (uVar31 & 0x7fffffff) - 0x800000 >> 0x18;
                    if (((bVar23 && uVar42 < 0x7e || bVar23 && uVar42 == 0x7e) ||
                        uVar31 - 1 < 0x7ffffe) ||
                        ((!bVar23 || uVar42 >= 0x7e) && (!bVar23 || uVar42 != 0x7e)) &&
                        uVar31 - 1 == 0x7ffffe) {
                      puVar60 = (uint *)(param_1 + 0x2e);
                      uVar31 = *puVar60;
                      if ((((((uVar31 == 0xffffffff || (int)(uVar31 + 1) < 0 != SCARRY4(uVar31,1))
                             || 0x7e < (uVar31 & 0x7fffffff) - 0x800000 >> 0x18) &&
                            0x7ffffe < uVar31 - 1) && (uVar31 & 0x7fffffff) != 0) ||
                          (uVar31 = *(uint *)(param_1 + 0x30),
                          (((uVar31 == 0xffffffff || (int)(uVar31 + 1) < 0 != SCARRY4(uVar31,1)) ||
                           0x7e < (uVar31 & 0x7fffffff) - 0x800000 >> 0x18) && 0x7ffffe < uVar31 - 1
                          ) && (uVar31 & 0x7fffffff) != 0)) ||
                         ((((uVar31 = *(uint *)(param_1 + 0x32),
                            (((uVar31 == 0xffffffff || (int)(uVar31 + 1) < 0 != SCARRY4(uVar31,1))
                             || 0x7e < (uVar31 & 0x7fffffff) - 0x800000 >> 0x18) &&
                            0x7ffffe < uVar31 - 1) && (uVar31 & 0x7fffffff) != 0 ||
                            ((uVar31 = *(uint *)(param_1 + 0x34),
                             (((uVar31 == 0xffffffff || (int)(uVar31 + 1) < 0 != SCARRY4(uVar31,1))
                              || 0x7e < (uVar31 & 0x7fffffff) - 0x800000 >> 0x18) &&
                             0x7ffffe < uVar31 - 1) && (uVar31 & 0x7fffffff) != 0 ||
                             (uVar31 = *(uint *)(param_1 + 0x36),
                             (((uVar31 == 0xffffffff || (int)(uVar31 + 1) < 0 != SCARRY4(uVar31,1))
                              || 0x7e < (uVar31 & 0x7fffffff) - 0x800000 >> 0x18) &&
                             0x7ffffe < uVar31 - 1) && (uVar31 & 0x7fffffff) != 0)))) ||
                           (uVar31 = *(uint *)(param_1 + 0x38),
                           (((uVar31 == 0xffffffff || (int)(uVar31 + 1) < 0 != SCARRY4(uVar31,1)) ||
                            0x7e < (uVar31 & 0x7fffffff) - 0x800000 >> 0x18) &&
                           0x7ffffe < uVar31 - 1) && (uVar31 & 0x7fffffff) != 0)) ||
                          ((uVar31 = *(uint *)(param_1 + 0x3a),
                           (((uVar31 == 0xffffffff || (int)(uVar31 + 1) < 0 != SCARRY4(uVar31,1)) ||
                            0x7e < (uVar31 & 0x7fffffff) - 0x800000 >> 0x18) &&
                           0x7ffffe < uVar31 - 1) && (uVar31 & 0x7fffffff) != 0 ||
                           (uVar31 = *(uint *)(param_1 + 0x3c),
                           (((uVar31 == 0xffffffff || (int)(uVar31 + 1) < 0 != SCARRY4(uVar31,1)) ||
                            0x7e < (uVar31 & 0x7fffffff) - 0x800000 >> 0x18) &&
                           0x7ffffe < uVar31 - 1) && (uVar31 & 0x7fffffff) != 0)))))) {
                        prVar29 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0011449c to 001144a7 has its CatchHandler @ 00114678 */
                        std::runtime_error::runtime_error(prVar29,"Invalid noise model");
                        goto LAB_001144c4;
                      }
                      if ((((((ABS(*(float *)(param_1 + 0x1c)) == INFINITY) ||
                             (ABS(*(float *)(param_1 + 0x1e)) == INFINITY)) ||
                            (ABS(*(float *)(param_1 + 0x20)) == INFINITY)) ||
                           ((ABS(*(float *)(param_1 + 0x22)) == INFINITY ||
                            (ABS(*(float *)(param_1 + 0x24)) == INFINITY)))) ||
                          (ABS(*(float *)(param_1 + 0x26)) == INFINITY)) ||
                         (((ABS(*(float *)(param_1 + 0x28)) == INFINITY ||
                           (ABS(*(float *)(param_1 + 0x2a)) == INFINITY)) ||
                          (pfVar11 = pfVar41, ABS(*(float *)(param_1 + 0x2c)) == INFINITY)))) {
                        prVar29 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00114464 to 0011446f has its CatchHandler @ 001146d4 */
                        std::runtime_error::runtime_error(prVar29,"Invalid matrix");
                        goto LAB_001144c4;
                      }
                      for (; pfVar11 != *(float **)(param_1 + 0x44); pfVar11 = pfVar11 + 1) {
                        fVar66 = *pfVar11;
                        if ((32.0 < fVar66 || fVar66 < 1.0) ||
                           ((INFINITY <= ABS(fVar66) && (ABS(fVar66) <= INFINITY)))) {
                          prVar29 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0011442c to 00114437 has its CatchHandler @ 001146dc */
                          std::runtime_error::runtime_error(prVar29,"Invalid shading");
                          goto LAB_001144c4;
                        }
                      }
                      for (; pfVar10 != *(float **)(param_1 + 0x50); pfVar10 = pfVar10 + 1) {
                        fVar66 = *pfVar10;
                        uVar31 = (uint)fVar66 & 0x7fffffff;
                        if (((0x7f800000 < uVar31 ||
                             (uVar31 == 0x7f800000 || (int)fVar66 < 0 && uVar31 - 1 < 0x7fffff)) ||
                             (int)fVar66 < 0 && uVar31 - 0x800000 >> 0x18 < 0x7f) || (1.0 < fVar66))
                        {
                          prVar29 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00114448 to 00114453 has its CatchHandler @ 001146d8 */
                          std::runtime_error::runtime_error(prVar29,"Invalid curve");
                          goto LAB_001144c4;
                        }
                      }
                      uVar86 = NEON_fmov(0x3f800000,4);
                      uVar61 = (long)(int)uVar14 * uVar58;
                      local_c0 = (void *)0x0;
                      local_b8 = (void *)0x0;
                      local_b0 = (void *)0x0;
                      __n = uVar61 * 4;
                      if (uVar14 != 0) {
                        if (uVar61 >> 0x3e != 0) {
                          local_b0 = (void *)0x0;
                          local_b8 = (void *)0x0;
                    /* try { // try from 00114554 to 0011455b has its CatchHandler @ 00114624 */
                          local_c0 = (void *)0x0;
                          std::__ndk1::vector<float,std::__ndk1::allocator<float>>::
                          __throw_length_error_abi_ne180000_();
                          goto LAB_0011455c;
                        }
                    /* try { // try from 00112058 to 00112063 has its CatchHandler @ 00114624 */
                        pvVar24 = operator_new(__n);
                        local_b0 = (void *)((long)pvVar24 + uVar61 * 4);
                        local_c0 = pvVar24;
                        memset(pvVar24,0,__n);
                        local_b8 = (void *)((long)pvVar24 + __n);
                    /* try { // try from 0011208c to 00112093 has its CatchHandler @ 001145b4 */
                        pvVar25 = operator_new(__n);
                        memset(pvVar25,0,__n);
                    /* try { // try from 001120a4 to 001120ab has its CatchHandler @ 001145ac */
                        local_1110 = operator_new(__n);
                        memset(local_1110,0,__n);
                        if (0 < (int)uVar14) {
                          lVar34 = uVar58 * 4;
                          uVar44 = 0;
                          uVar31 = uVar12;
                          if (uVar12 - 1 == 0 || (int)uVar12 < 1) {
                            uVar31 = 1;
                          }
                          pvVar26 = pvVar24;
                          do {
                            uVar55 = 0;
                            fVar66 = ((float)iVar74 * (float)(int)uVar44) / (float)(uVar14 - 1);
                            iVar53 = (int)fVar66;
                            iVar73 = iVar74;
                            if (iVar53 + 1 <= iVar74) {
                              iVar73 = iVar53 + 1;
                            }
                            do {
                              uVar36 = uVar55 & 1 | (uVar44 & 1) << 1;
                              fVar89 = (float)NEON_ucvtf((uint)*(ushort *)(this + uVar55 * 2));
                              iVar48 = *(int *)(&channel(int,int,int)::layouts +
                                               uVar36 * 4 + (ulong)uVar13 * 0x10);
                              fVar79 = ((float)iVar72 * (float)(int)uVar55) / (float)(uVar12 - 1);
                              iVar30 = (int)fVar79;
                              iVar35 = iVar72;
                              if (iVar30 + 1 <= iVar72) {
                                iVar35 = iVar30 + 1;
                              }
                              fVar79 = fVar79 - (float)(int)fVar79;
                              fVar90 = (float)NEON_fmadd(pfVar41[iVar48 + (iVar73 * iVar71 + iVar30)
                                                                          * 4],1.0 - fVar79,
                                                         fVar79 * pfVar41[iVar48 + (iVar35 + iVar73 
                                                  * iVar71) * 4]);
                              uVar80 = NEON_fmadd(pfVar41[iVar48 + (iVar71 * iVar53 + iVar30) * 4],
                                                  1.0 - fVar79,
                                                  fVar79 * pfVar41[iVar48 + (iVar35 + iVar71 * 
                                                  iVar53) * 4]);
                              fVar89 = (float)NEON_fminnm((fVar89 - *(float *)(param_1 +
                                                                              uVar36 * 2 + 0xc)) /
                                                          (fVar82 - *(float *)(param_1 +
                                                                              uVar36 * 2 + 0xc)),
                                                          0x3f800000);
                              fVar79 = (float)NEON_fmadd(uVar80,1.0 - (fVar66 - (float)(int)fVar66),
                                                         (fVar66 - (float)(int)fVar66) * fVar90);
                              *(float *)((long)pvVar26 + uVar55 * 4) = fVar89 * fVar79;
                              uVar63 = DAT_00102f50;
                              uVar55 = uVar55 + 1;
                            } while (uVar31 != uVar55);
                            uVar44 = uVar44 + 1;
                            pvVar26 = (void *)((long)pvVar26 + lVar34);
                            this = this + uVar58 * 2;
                          } while (uVar44 != uVar14);
                          if (0 < (int)uVar14) {
                            iVar73 = uVar12 * 2 + -2;
                            iVar53 = uVar14 * 2 + -2;
                            uVar44 = 0;
                            uVar31 = uVar12;
                            if (uVar12 - 1 == 0 || (int)uVar12 < 1) {
                              uVar31 = 1;
                            }
                            pvVar26 = pvVar25;
                            pvVar37 = pvVar24;
                            do {
                              uVar42 = (uint)uVar44;
                              uVar55 = 0;
                              fVar82 = ((float)iVar74 * (float)uVar42) / (float)(uVar14 - 1);
                              iVar48 = (int)fVar82;
                              iVar35 = iVar74;
                              if (iVar48 + 1 <= iVar74) {
                                iVar35 = iVar48 + 1;
                              }
                              iVar30 = uVar42 - 2;
                              if ((int)(uVar42 - 2) < 0) {
                                iVar30 = 2 - uVar42;
                              }
                              if ((int)uVar14 <= iVar30) {
                                iVar30 = iVar53 - iVar30;
                              }
                              iVar57 = uVar42 + 2;
                              if ((int)(uVar42 + 2) < 0) {
                                iVar57 = -2 - uVar42;
                              }
                              lVar52 = (long)iVar30 * uVar58;
                              if ((int)uVar14 <= iVar57) {
                                iVar57 = iVar53 - iVar57;
                              }
                              lVar56 = (long)iVar57 * uVar58;
                              iVar30 = uVar12 * 2;
                              do {
                                uVar32 = (uint)uVar55;
                                uVar17 = uVar32 & 1 | (uVar42 & 1) << 1;
                                iVar15 = *(int *)(&channel(int,int,int)::layouts +
                                                 (ulong)uVar17 * 4 + (ulong)uVar13 * 0x10);
                                fVar66 = ((float)iVar72 * (float)uVar32) / (float)(uVar12 - 1);
                                iVar49 = (int)fVar66;
                                iVar57 = iVar72;
                                if (iVar49 + 1 <= iVar72) {
                                  iVar57 = iVar49 + 1;
                                }
                                fVar66 = fVar66 - (float)(int)fVar66;
                                lVar62 = uVar55 * 4;
                                fVar79 = (float)NEON_fmadd(pfVar41[iVar15 + (iVar35 * iVar71 +
                                                                            iVar49) * 4],
                                                           1.0 - fVar66,
                                                           fVar66 * pfVar41[iVar15 + (iVar57 + 
                                                  iVar35 * iVar71) * 4]);
                                uVar80 = NEON_fmadd(pfVar41[iVar15 + (iVar71 * iVar48 + iVar49) * 4]
                                                    ,1.0 - fVar66,
                                                    fVar66 * pfVar41[iVar15 + (iVar57 + iVar71 * 
                                                  iVar48) * 4]);
                                iVar57 = uVar32 - 2;
                                if ((int)(uVar32 - 2) < 0) {
                                  iVar57 = 2 - uVar32;
                                }
                                uVar18 = iVar30 - 2;
                                iVar30 = iVar30 + -1;
                                fVar79 = (float)NEON_fmadd(uVar80,1.0 - (fVar82 - (float)(int)fVar82
                                                                        ),
                                                           (fVar82 - (float)(int)fVar82) * fVar79);
                                fVar66 = *(float *)((long)pvVar37 + lVar62);
                                iVar49 = iVar57;
                                if ((int)uVar12 <= iVar57) {
                                  iVar49 = iVar73 - iVar57;
                                }
                                fVar89 = fVar66;
                                if (fVar66 <= 0.0) {
                                  fVar89 = 0.0;
                                }
                                uVar7 = uVar32;
                                if (uVar58 <= uVar55) {
                                  uVar7 = uVar18;
                                }
                                uVar36 = -(ulong)(uVar7 >> 0x1f) & 0xfffffffc00000000 |
                                         (ulong)uVar7 << 2;
                                fVar90 = *(float *)((long)pvVar24 + uVar36 + lVar56 * 4);
                                iVar104 = MP_INT_ABS(uVar32 + (int)uVar63);
                                iVar106 = MP_INT_ABS(uVar32 + (int)((ulong)uVar63 >> 0x20));
                                uVar108 = NEON_cmgt(CONCAT44(uVar12,uVar12),
                                                    CONCAT44(iVar106,iVar104),4);
                                fVar79 = (float)NEON_fmadd(fVar89 * (float)puVar60[uVar17 << 1],
                                                           fVar79,fVar79 * (float)puVar60[uVar17 << 
                                                  1 | 1] * fVar79);
                                fVar97 = *(float *)((long)pvVar24 + (long)iVar49 * 4 + lVar52 * 4);
                                fVar89 = *(float *)((long)pvVar24 + uVar36 + lVar52 * 4);
                                uVar108 = NEON_bit(CONCAT44(iVar73 - iVar106,iVar73 - iVar104),
                                                   CONCAT44(iVar106,iVar104),uVar108,1);
                                uVar55 = uVar55 + 1;
                                uVar17 = uVar32 + 2;
                                if ((int)(uVar32 + 2) < 0) {
                                  uVar17 = -uVar32 - 2;
                                }
                                if (fVar79 <= 1e-08) {
                                  fVar79 = 1e-08;
                                }
                                if ((int)uVar12 <= (int)uVar17) {
                                  uVar17 = iVar73 - uVar17;
                                }
                                uVar36 = -(ulong)(uVar17 >> 0x1f) & 0xfffffffc00000000 |
                                         (ulong)uVar17 << 2;
                                if ((int)uVar12 <= iVar57) {
                                  iVar57 = iVar73 - iVar57;
                                }
                                fVar105 = *(float *)((long)pvVar24 + uVar36 + lVar52 * 4);
                                fVar115 = *(float *)((long)pvVar24 + (long)iVar57 * 4 + lVar56 * 4);
                                fVar85 = *(float *)((long)pvVar24 + uVar36 + lVar56 * 4);
                                fVar107 = fVar97 - fVar66;
                                fVar109 = fVar89 - fVar66;
                                fVar79 = fVar79 * 4.0;
                                fVar103 = *(float *)((long)pvVar24 +
                                                    (long)(int)uVar108 * 4 +
                                                    (long)(int)uVar42 * uVar58 * 4);
                                fVar112 = *(float *)((long)pvVar24 +
                                                    (long)(int)((ulong)uVar108 >> 0x20) * 4 +
                                                    (long)(int)uVar42 * uVar58 * 4);
                                fVar110 = fVar105 - fVar66;
                                fVar111 = fVar103 - fVar66;
                                fVar83 = fVar112 - fVar66;
                                fVar84 = fVar115 - fVar66;
                                fVar101 = fVar90 - fVar66;
                                fVar102 = fVar85 - fVar66;
                                fVar98 = (float)uVar86;
                                fVar100 = (float)((ulong)uVar86 >> 0x20);
                                fVar113 = fVar98 / ((fVar107 * fVar107) / fVar79 + fVar98);
                                fVar114 = fVar100 / ((fVar109 * fVar109) / fVar79 + fVar100);
                                fVar66 = (float)NEON_fmadd(fVar97,fVar113,fVar66);
                                fVar107 = fVar98 / ((fVar110 * fVar110) / fVar79 + fVar98);
                                fVar109 = fVar100 / ((fVar111 * fVar111) / fVar79 + fVar100);
                                fVar97 = fVar98 / ((fVar83 * fVar83) / fVar79 + fVar98);
                                fVar83 = fVar100 / ((fVar84 * fVar84) / fVar79 + fVar100);
                                fVar66 = (float)NEON_fmadd(fVar105,fVar107,fVar66 + fVar89 * fVar114
                                                          );
                                fVar98 = fVar98 / ((fVar101 * fVar101) / fVar79 + fVar98);
                                fVar100 = fVar100 / ((fVar102 * fVar102) / fVar79 + fVar100);
                                fVar66 = (float)NEON_fmadd(fVar112,fVar97,fVar66 + fVar103 * fVar109
                                                          );
                                fVar66 = (float)NEON_fmadd(fVar90,fVar98,fVar66 + fVar115 * fVar83);
                                *(float *)((long)pvVar26 + lVar62) =
                                     ((fVar66 + fVar85 * fVar100) /
                                     (fVar113 + 1.0 + fVar114 + fVar107 + fVar109 + fVar97 + fVar83
                                      + fVar98 + fVar100)) *
                                     *(float *)(param_1 + (long)iVar15 * 2 + 0x14);
                              } while (uVar31 != uVar55);
                              uVar44 = uVar44 + 1;
                              pvVar26 = (void *)((long)pvVar26 + lVar34);
                              pvVar37 = (void *)((long)pvVar37 + lVar34);
                            } while (uVar44 != uVar14);
                          }
                        }
                        local_c0 = (void *)0x0;
                        local_b8 = (void *)0x0;
                        local_b0 = (void *)0x0;
                        operator_delete(pvVar24);
                        uVar12 = *(uint *)(param_1 + 2);
                        uVar58 = (ulong)uVar12;
                        bVar23 = 0 < (int)uVar12;
                        if ((int)uVar12 < 1) {
                          bVar23 = false;
                          if (uVar14 != 0) goto LAB_001127e0;
LAB_00112850:
                          pvVar24 = (void *)0x0;
                          pvVar26 = (void *)0x0;
                          if (bVar23) {
LAB_0011285c:
                            uVar13 = *(uint *)param_1;
                            iVar71 = *(int *)(param_1 + 4);
                            lVar34 = (long)(int)uVar13;
                            iVar72 = uVar12 * 2 + -2;
                            uVar44 = 0;
                            do {
                              while ((int)uVar13 < 1) {
                                uVar44 = uVar44 + 1;
                                if (uVar44 == uVar58) goto LAB_00112b60;
                              }
                              uVar31 = (uint)uVar44;
                              iVar73 = uVar31 - 1;
                              if ((int)(uVar31 - 1) < 0) {
                                iVar73 = 1 - uVar31;
                              }
                              uVar55 = uVar44 + 1;
                              if ((int)uVar12 <= iVar73) {
                                iVar73 = iVar72 - iVar73;
                              }
                              iVar74 = (int)uVar55;
                              if ((long)uVar58 <= (long)uVar55) {
                                iVar74 = iVar72 + ~uVar31;
                              }
                              lVar59 = lVar34 * 4 * uVar44;
                              lVar56 = 0;
                              lVar62 = uVar44 * lVar34 * 4;
                              lVar45 = (long)(int)uVar13 * (long)iVar73 * 4;
                              lVar52 = 0;
                              lVar54 = (long)(int)uVar13 * (long)iVar74 * 4;
                              uVar42 = uVar13 * 2 - 3;
                              do {
                                uVar32 = (uint)lVar52;
                                uVar17 = uVar32 - 1;
                                if ((int)(uVar32 - 1) < 0) {
                                  uVar17 = 1 - uVar32;
                                }
                                fVar82 = *(float *)((long)local_1110 + lVar56 + lVar62);
                                uVar18 = uVar32 & 1 | (uVar31 & 1) << 1;
                                uVar32 = *(uint *)(&channel(int,int,int)::layouts +
                                                  (ulong)uVar18 * 4 + (long)iVar71 * 0x10);
                                if ((int)uVar13 <= (int)uVar17) {
                                  uVar17 = (uVar13 * 2 - uVar17) - 2;
                                }
                                uVar7 = (uint)(lVar52 + 1);
                                if (lVar34 <= lVar52 + 1) {
                                  uVar7 = uVar42;
                                }
                                if (uVar32 == 0) {
                                  fVar66 = *(float *)((long)pvVar25 + lVar56 + lVar62);
LAB_00112b08:
                                  lVar39 = (long)(int)uVar17 * 4;
                                  lVar46 = (long)(int)uVar7 * 4;
                                  fVar79 = (float)NEON_fmadd((*(float *)((long)pvVar25 +
                                                                        lVar39 + lVar45) -
                                                             *(float *)((long)local_1110 +
                                                                       lVar39 + lVar45)) +
                                                             (*(float *)((long)pvVar25 +
                                                                        lVar46 + lVar45) -
                                                             *(float *)((long)local_1110 +
                                                                       lVar46 + lVar45)) +
                                                             (*(float *)((long)pvVar25 +
                                                                        lVar39 + lVar54) -
                                                             *(float *)((long)local_1110 +
                                                                       lVar39 + lVar54)) +
                                                             (*(float *)((long)pvVar25 +
                                                                        lVar46 + lVar54) -
                                                             *(float *)((long)local_1110 +
                                                                       lVar46 + lVar54)),0x3e800000,
                                                             fVar82);
                                }
                                else if (uVar32 < 3) {
                                  uVar36 = -(ulong)(uVar17 >> 0x1f) & 0xfffffffc00000000 |
                                           (ulong)uVar17 << 2;
                                  uVar44 = -(ulong)(uVar7 >> 0x1f) & 0xfffffffc00000000 |
                                           (ulong)uVar7 << 2;
                                  iVar73 = *(int *)(&channel(int,int,int)::layouts +
                                                   (ulong)(uVar18 ^ 1) * 4 + (long)iVar71 * 0x10);
                                  pfVar41 = (float *)((long)pvVar25 + lVar56 + lVar45);
                                  pfVar10 = (float *)((long)local_1110 + lVar56 + lVar45);
                                  pfVar11 = (float *)((long)pvVar25 + lVar56 + lVar54);
                                  pfVar1 = (float *)((long)local_1110 + lVar56 + lVar54);
                                  pfVar33 = (float *)((long)pvVar25 + uVar36 + lVar62);
                                  pfVar2 = (float *)((long)local_1110 + uVar36 + lVar62);
                                  pfVar3 = (float *)((long)pvVar25 + uVar44 + lVar62);
                                  pfVar4 = (float *)((long)local_1110 + uVar44 + lVar62);
                                  pfVar9 = pfVar4;
                                  pfVar20 = pfVar2;
                                  pfVar21 = pfVar33;
                                  pfVar22 = pfVar3;
                                  if (iVar73 != 0) {
                                    pfVar9 = pfVar1;
                                    pfVar20 = pfVar10;
                                    pfVar21 = pfVar41;
                                    pfVar22 = pfVar11;
                                  }
                                  if (iVar73 != 3) {
                                    pfVar2 = pfVar10;
                                    pfVar33 = pfVar41;
                                  }
                                  if (iVar73 != 3) {
                                    pfVar4 = pfVar1;
                                    pfVar3 = pfVar11;
                                  }
                                  fVar66 = (float)NEON_fmadd((*pfVar21 - *pfVar20) +
                                                             (*pfVar22 - *pfVar9),0x3f000000,fVar82)
                                  ;
                                  fVar79 = (float)NEON_fmadd((*pfVar33 - *pfVar2) +
                                                             (*pfVar3 - *pfVar4),0x3f000000,fVar82);
                                }
                                else {
                                  lVar39 = (long)(int)uVar17 * 4;
                                  lVar46 = (long)(int)uVar7 * 4;
                                  fVar66 = (float)NEON_fmadd((*(float *)((long)pvVar25 +
                                                                        lVar39 + lVar45) -
                                                             *(float *)((long)local_1110 +
                                                                       lVar39 + lVar45)) +
                                                             (*(float *)((long)pvVar25 +
                                                                        lVar46 + lVar45) -
                                                             *(float *)((long)local_1110 +
                                                                       lVar46 + lVar45)) +
                                                             (*(float *)((long)pvVar25 +
                                                                        lVar39 + lVar54) -
                                                             *(float *)((long)local_1110 +
                                                                       lVar39 + lVar54)) +
                                                             (*(float *)((long)pvVar25 +
                                                                        lVar46 + lVar54) -
                                                             *(float *)((long)local_1110 +
                                                                       lVar46 + lVar54)),0x3e800000,
                                                             fVar82);
                                  if (uVar32 != 3) goto LAB_00112b08;
                                  fVar79 = *(float *)((long)pvVar25 + lVar56 + lVar62);
                                }
                                uVar42 = uVar42 - 1;
                                lVar52 = lVar52 + 1;
                                *(float *)((long)pvVar24 + lVar56 + lVar59) = fVar66 - fVar82;
                                *(float *)((long)pvVar26 + lVar56 + lVar59) = fVar79 - fVar82;
                                lVar56 = lVar56 + 4;
                              } while ((ulong)uVar13 << 2 != lVar56);
                              uVar44 = uVar55;
                            } while (uVar55 != uVar58);
                          }
                        }
                        else {
                          uVar13 = *(uint *)param_1;
                          iVar71 = *(int *)(param_1 + 4);
                          iVar72 = uVar13 * 2;
                          iVar73 = uVar12 * 2;
                          uVar44 = 0;
                          do {
                            while ((int)uVar13 < 1) {
                              uVar44 = uVar44 + 1;
                              if (uVar44 == uVar58) goto LAB_001127d8;
                            }
                            iVar53 = (int)uVar44;
                            iVar74 = iVar53 + -1;
                            if (iVar53 + -1 < 0) {
                              iVar74 = 1 - iVar53;
                            }
                            lVar34 = uVar44 * (long)(int)uVar13;
                            uVar55 = uVar44 + 1;
                            if ((int)uVar12 <= iVar74) {
                              iVar74 = (iVar73 - iVar74) + -2;
                            }
                            iVar35 = (int)uVar55;
                            if ((long)uVar58 <= (long)uVar55) {
                              iVar35 = (iVar73 - iVar53) + -3;
                            }
                            iVar48 = iVar53 + -2;
                            if (iVar53 + -2 < 0) {
                              iVar48 = 2 - iVar53;
                            }
                            if ((int)uVar12 <= iVar48) {
                              iVar48 = (iVar73 - iVar48) + -2;
                            }
                            iVar30 = iVar53 + 2;
                            if ((int)uVar12 <= iVar53 + 2) {
                              iVar30 = (iVar73 - iVar53) + -4;
                            }
                            uVar36 = 0;
                            do {
                              lVar52 = lVar34 + uVar36;
                              if (*(int *)(&channel(int,int,int)::layouts +
                                          (uVar36 & 1 | (uVar44 & 1) << 1) * 4 + (long)iVar71 * 0x10
                                          ) - 1U < 2) {
                                fVar66 = *(float *)((long)pvVar25 + lVar52 * 4);
                              }
                              else {
                                iVar57 = (int)uVar36;
                                iVar53 = iVar57 + -1;
                                if (iVar57 + -1 < 0) {
                                  iVar53 = 1 - iVar57;
                                }
                                uVar80 = *(undefined4 *)((long)pvVar25 + lVar52 * 4);
                                if ((int)uVar13 <= iVar53) {
                                  iVar53 = (iVar72 - iVar53) + -2;
                                }
                                iVar15 = (int)(uVar36 + 1);
                                if ((long)(int)uVar13 <= (long)(uVar36 + 1)) {
                                  iVar15 = (iVar72 - iVar57) + -3;
                                }
                                iVar49 = iVar57 + -2;
                                if (iVar57 + -2 < 0) {
                                  iVar49 = 2 - iVar57;
                                }
                                lVar56 = uVar36 * 4;
                                fVar82 = *(float *)((long)pvVar25 + (long)iVar53 * 4 + lVar34 * 4);
                                fVar66 = *(float *)((long)pvVar25 + (long)iVar15 * 4 + lVar34 * 4);
                                if ((int)uVar13 <= iVar49) {
                                  iVar49 = (iVar72 - iVar49) + -2;
                                }
                                fVar89 = *(float *)((long)pvVar25 +
                                                   lVar56 + (long)(int)uVar13 * (long)iVar74 * 4);
                                fVar79 = (float)NEON_fnmsub(uVar80,0x40000000,
                                                            *(undefined4 *)
                                                             ((long)pvVar25 +
                                                             lVar56 + (long)(int)uVar13 *
                                                                      (long)iVar48 * 4));
                                iVar53 = iVar57 + 2;
                                if ((int)uVar13 <= iVar57 + 2) {
                                  iVar53 = (iVar72 - iVar57) + -4;
                                }
                                fVar84 = *(float *)((long)pvVar25 + (long)iVar53 * 4 + lVar34 * 4);
                                fVar98 = *(float *)((long)pvVar25 +
                                                   lVar56 + (long)(int)uVar13 * (long)iVar35 * 4);
                                fVar90 = (float)NEON_fnmsub(uVar80,0x40000000,
                                                            *(undefined4 *)
                                                             ((long)pvVar25 +
                                                             (long)iVar49 * 4 + lVar34 * 4));
                                fVar97 = *(float *)((long)pvVar25 +
                                                   lVar56 + (long)(int)uVar13 * (long)iVar30 * 4);
                                fVar83 = (float)NEON_fmadd(fVar89 + fVar98,0x3f000000,
                                                           (fVar79 - fVar97) * 0.25);
                                fVar85 = ABS(fVar82 - fVar66) + ABS(fVar90 - fVar84) + 1e-05;
                                uVar80 = NEON_fmadd(fVar82 + fVar66,0x3f000000,
                                                    (fVar90 - fVar84) * 0.25);
                                fVar82 = ABS(fVar89 - fVar98) + ABS(fVar79 - fVar97) + 1e-05;
                                fVar66 = (float)NEON_fmadd(uVar80,fVar82,fVar83 * fVar85);
                                fVar66 = fVar66 / (fVar85 + fVar82);
                              }
                              uVar36 = uVar36 + 1;
                              *(float *)((long)local_1110 + lVar52 * 4) = fVar66;
                            } while (uVar36 != uVar13);
                            uVar44 = uVar55;
                          } while (uVar55 != uVar58);
LAB_001127d8:
                          if (uVar14 == 0) goto LAB_00112850;
LAB_001127e0:
                    /* try { // try from 001127e0 to 001127eb has its CatchHandler @ 001145a4 */
                          pvVar24 = operator_new(__n);
                          memset(pvVar24,0,__n);
                    /* try { // try from 001127fc to 00112803 has its CatchHandler @ 0011459c */
                          pvVar26 = operator_new(__n);
                          memset(pvVar26,0,__n);
                          if (bVar23) goto LAB_0011285c;
                        }
LAB_00112b60:
                        operator_delete(pvVar25);
                        apvStack_4c0[125] = (void *)0x0;
                        apvStack_4c0[126] = (void *)0x0;
                        apvStack_4c0[127] = (void *)0x0;
                        if (uVar14 == 0) {
                          pvVar25 = (void *)0x0;
                          goto LAB_00112bd0;
                        }
                        if (uVar61 < 0x1555555555555556) {
                          uVar58 = uVar61 * 0xc;
                    /* try { // try from 00112b98 to 00112b9f has its CatchHandler @ 001145bc */
                          pvVar25 = operator_new(uVar58);
                          apvStack_4c0[127] = (void *)((long)pvVar25 + uVar61 * 0xc);
                          apvStack_4c0[125] = pvVar25;
                          memset(pvVar25,0,uVar58);
                          apvStack_4c0[126] = (void *)((long)pvVar25 + uVar58);
                          goto LAB_00112bd0;
                        }
                    /* try { // try from 00114564 to 0011456b has its CatchHandler @ 001145bc */
                        std::__ndk1::vector<float,std::__ndk1::allocator<float>>::
                        __throw_length_error_abi_ne180000_();
LAB_0011456c:
                    /* try { // try from 0011456c to 00114573 has its CatchHandler @ 00114598 */
                        std::__ndk1::vector<float,std::__ndk1::allocator<float>>::
                        __throw_length_error_abi_ne180000_();
LAB_00114574:
                    /* try { // try from 00114574 to 0011457b has its CatchHandler @ 00114594 */
                        std::__ndk1::vector<float,std::__ndk1::allocator<float>>::
                        __throw_length_error_abi_ne180000_();
LAB_0011457c:
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 0011457c to 0011457f has its CatchHandler @ 00114598 */
                        std::__throw_bad_array_new_length_abi_ne180000_();
                      }
                      pvVar24 = (void *)0x0;
                      pvVar26 = (void *)0x0;
                      local_1110 = (void *)0x0;
                      pvVar25 = (void *)0x0;
                      local_c0 = (void *)0x0;
                      local_b8 = (void *)0x0;
                      local_b0 = (void *)0x0;
                      apvStack_4c0[125] = (void *)0x0;
                      apvStack_4c0[126] = (void *)0x0;
                      apvStack_4c0[127] = (void *)0x0;
LAB_00112bd0:
                      uVar12 = *(uint *)(param_1 + 2);
                      if (0 < (int)uVar12) {
                        uVar58 = 0;
                        uVar13 = *(uint *)param_1;
                        lVar52 = *(long *)(param_1 + 0x4c);
                        iVar71 = *(int *)(param_1 + 4);
                        iVar72 = *(int *)(param_1 + 6);
                        iVar73 = *(int *)(param_1 + 8) + -1;
                        iVar74 = iVar72 + -1;
                        uVar87 = *(undefined4 *)(param_1 + 0x1c);
                        fVar82 = *(float *)(param_1 + 0x1e);
                        uVar67 = *(undefined4 *)(param_1 + 0x20);
                        uVar69 = *(undefined4 *)(param_1 + 0x22);
                        lVar34 = (long)iVar71 * 0x10;
                        lVar56 = *(long *)(param_1 + 0x40);
                        fVar83 = *(float *)(param_1 + 0x30);
                        fVar84 = *(float *)(param_1 + 0x32);
                        fVar97 = *(float *)(param_1 + 0x3c);
                        fVar66 = *(float *)(param_1 + 0x24);
                        uVar68 = *(undefined4 *)(param_1 + 0x26);
                        fVar85 = *(float *)(param_1 + 0x34);
                        fVar98 = *(float *)(param_1 + 0x36);
                        uVar64 = *(undefined4 *)(param_1 + 0x28);
                        fVar89 = *(float *)(param_1 + 0x2a);
                        fVar100 = *(float *)(param_1 + 0x38);
                        fVar90 = *(float *)(param_1 + 0x3a);
                        uVar80 = *(undefined4 *)(param_1 + 0x2c);
                        fVar79 = *(float *)(param_1 + 0x2e);
                        do {
                          if (0 < (int)uVar13) {
                            uVar44 = 0;
                            fVar101 = ((float)(int)uVar58 * (float)iVar73) / (float)(uVar12 - 1);
                            iVar35 = (int)fVar101;
                            iVar53 = iVar73;
                            if (iVar35 + 1 <= iVar73) {
                              iVar53 = iVar35 + 1;
                            }
                            fVar101 = fVar101 - (float)(int)fVar101;
                            iVar48 = *(int *)(&channel(int,int,int)::layouts + lVar34);
                            iVar57 = *(int *)(&DAT_00103c94 + lVar34);
                            iVar30 = *(int *)(&DAT_00103c94 + lVar34);
                            iVar15 = *(int *)(&DAT_00103c9c + lVar34);
                            fVar109 = 1.0 - fVar101;
                            fVar102 = *(float *)(param_1 + (long)iVar48 * 2 + 0x14);
                            fVar103 = *(float *)(param_1 + (long)iVar57 * 2 + 0x14);
                            fVar105 = *(float *)(param_1 + (long)iVar30 * 2 + 0x14);
                            fVar107 = *(float *)(param_1 + (long)iVar15 * 2 + 0x14);
                            do {
                              lVar62 = (uVar58 * (long)(int)uVar13 + uVar44) * 4;
                              fVar112 = *(float *)((long)pvVar24 + lVar62);
                              fVar113 = ((float)(int)uVar44 * (float)iVar74) / (float)(uVar13 - 1);
                              fVar111 = *(float *)((long)pvVar26 + lVar62);
                              fVar110 = fVar111;
                              if (iVar71 != 3) {
                                fVar110 = -0.0;
                              }
                              fVar114 = fVar111;
                              if (iVar71 != 2) {
                                fVar114 = -0.0;
                              }
                              fVar115 = fVar112;
                              if (iVar71 != 1) {
                                fVar115 = fVar114;
                              }
                              fVar78 = fVar112;
                              fVar114 = fVar111;
                              if (iVar71 != 0) {
                                fVar114 = -0.0;
                                fVar78 = fVar110;
                              }
                              fVar110 = fVar112;
                              if (iVar71 != 3) {
                                fVar110 = fVar114;
                              }
                              iVar49 = (int)fVar113;
                              fVar114 = fVar111;
                              if (iVar71 != 1) {
                                fVar114 = -0.0;
                              }
                              fVar81 = fVar112;
                              if (iVar71 != 2) {
                                fVar81 = fVar114;
                              }
                              iVar104 = iVar74;
                              if (iVar49 + 1 <= iVar74) {
                                iVar104 = iVar49 + 1;
                              }
                              iVar106 = (iVar53 * iVar72 + iVar49) * 4;
                              iVar49 = (iVar72 * iVar35 + iVar49) * 4;
                              iVar43 = (iVar72 * iVar35 + iVar104) * 4;
                              iVar104 = (iVar53 * iVar72 + iVar104) * 4;
                              fVar113 = fVar113 - (float)(int)fVar113;
                              fVar99 = 1.0 - fVar113;
                              fVar114 = (float)NEON_fmadd(*(undefined4 *)
                                                           (lVar56 + (long)(iVar106 + iVar48) * 4),
                                                          fVar99,*(float *)(lVar56 + (long)(iVar104 
                                                  + iVar48) * 4) * fVar113);
                              fVar93 = (float)NEON_fmadd(*(undefined4 *)
                                                          (lVar56 + (long)(iVar106 + iVar57) * 4),
                                                         fVar99,*(float *)(lVar56 + (long)(iVar104 +
                                                                                          iVar57) *
                                                                                    4) * fVar113);
                              fVar91 = (float)NEON_fmadd(*(undefined4 *)
                                                          (lVar56 + (long)(iVar106 + iVar30) * 4),
                                                         fVar99,*(float *)(lVar56 + (long)(iVar104 +
                                                                                          iVar30) *
                                                                                    4) * fVar113);
                              fVar70 = (float)NEON_fmadd(*(undefined4 *)
                                                          (lVar56 + (long)(iVar106 + iVar15) * 4),
                                                         fVar99,*(float *)(lVar56 + (long)(iVar104 +
                                                                                          iVar15) *
                                                                                    4) * fVar113);
                              uVar88 = NEON_fmadd(*(undefined4 *)
                                                   (lVar56 + (long)(iVar49 + iVar48) * 4),fVar99,
                                                  *(float *)(lVar56 + (long)(iVar43 + iVar48) * 4) *
                                                  fVar113);
                              uVar92 = NEON_fmadd(*(undefined4 *)
                                                   (lVar56 + (long)(iVar49 + iVar57) * 4),fVar99,
                                                  *(float *)(lVar56 + (long)(iVar43 + iVar57) * 4) *
                                                  fVar113);
                              uVar94 = NEON_fmadd(*(undefined4 *)
                                                   (lVar56 + (long)(iVar49 + iVar30) * 4),fVar99,
                                                  *(float *)(lVar56 + (long)(iVar43 + iVar30) * 4) *
                                                  fVar113);
                              uVar96 = NEON_fmadd(*(undefined4 *)
                                                   (lVar56 + (long)(iVar49 + iVar15) * 4),fVar99,
                                                  *(float *)(lVar56 + (long)(iVar43 + iVar15) * 4) *
                                                  fVar113);
                              fVar99 = (float)NEON_fmadd(uVar88,fVar109,fVar101 * fVar114);
                              fVar113 = *(float *)((long)local_1110 + lVar62);
                              fVar93 = (float)NEON_fmadd(uVar92,fVar109,fVar101 * fVar93);
                              fVar91 = (float)NEON_fmadd(uVar94,fVar109,fVar101 * fVar91);
                              fVar78 = fVar113 + fVar78;
                              fVar70 = (float)NEON_fmadd(uVar96,fVar109,fVar101 * fVar70);
                              fVar114 = 0.0;
                              fVar115 = fVar113 + fVar115;
                              fVar99 = fVar102 * fVar99;
                              fVar81 = fVar113 + fVar81;
                              fVar110 = fVar113 + fVar110;
                              fVar93 = fVar103 * fVar93;
                              if (fVar78 <= 0.0) {
                                fVar78 = 0.0;
                              }
                              if (fVar115 <= 0.0) {
                                fVar115 = 0.0;
                              }
                              fVar91 = fVar105 * fVar91;
                              if (fVar81 <= 0.0) {
                                fVar81 = 0.0;
                              }
                              if (fVar110 <= 0.0) {
                                fVar110 = 0.0;
                              }
                              fVar70 = fVar107 * fVar70;
                              fVar78 = (float)NEON_fmadd(fVar78 * fVar79,fVar99,
                                                         fVar99 * fVar83 * fVar99);
                              fVar115 = (float)NEON_fmadd(fVar115 * fVar84,fVar93,
                                                          fVar93 * fVar85 * fVar93);
                              fVar81 = (float)NEON_fmadd(fVar81 * fVar98,fVar91,
                                                         fVar91 * fVar100 * fVar91);
                              local_4d8[iVar48] = fVar78;
                              fVar110 = (float)NEON_fmadd(fVar110 * fVar90,fVar70,
                                                          fVar70 * fVar97 * fVar70);
                              local_4d8[iVar57] = fVar115;
                              local_4d8[iVar30] = fVar81;
                              local_4d8[iVar15] = fVar110;
                              fVar110 = (local_4d8[1] + local_4d8[2]) * 0.5;
                              pfVar41 = (float *)((long)pvVar25 +
                                                 ((long)(int)uVar13 + (long)(int)uVar13 * 2) * 4 *
                                                 uVar58 + uVar44 * 0xc);
                              iVar49 = -2;
                              fVar115 = (float)NEON_fmadd(fVar110,0x40000000,
                                                          local_4d8[0] + local_4d8[3]);
                              fVar78 = (float)NEON_fminnm((int)(SQRT(fVar115) / fVar113 +
                                                               SQRT(fVar115) / fVar113),0x40400000);
                              if (fVar78 <= 1.0) {
                                fVar78 = 1.0;
                              }
                              iVar104 = (int)fVar78;
                              fVar110 = (float)NEON_fmadd(fVar110,0x41000000,0x38d1b717);
                              fVar115 = (float)NEON_fmadd(fVar115,0x41000000,0x3951b717);
                              fVar78 = 0.0;
                              fVar81 = 0.0;
                              do {
                                iVar16 = (int)uVar58 + iVar49 * iVar104;
                                iVar106 = -2;
                                iVar43 = -iVar16;
                                if (-1 < iVar16) {
                                  iVar43 = iVar16;
                                }
                                if ((int)uVar12 <= iVar43) {
                                  iVar43 = (uVar12 * 2 + -2) - iVar43;
                                }
                                lVar62 = (long)(int)uVar13 * (long)iVar43 * 4;
                                uVar31 = (int)uVar44 + iVar104 * -2;
                                do {
                                  uVar42 = -uVar31;
                                  if (-1 < (int)uVar31) {
                                    uVar42 = uVar31;
                                  }
                                  uVar31 = uVar31 + iVar104;
                                  if ((int)uVar13 <= (int)uVar42) {
                                    uVar42 = (uVar13 * 2 + -2) - uVar42;
                                  }
                                  uVar55 = -(ulong)(uVar42 >> 0x1f) & 0xfffffffc00000000 |
                                           (ulong)uVar42 << 2;
                                  fVar99 = *(float *)((long)pvVar26 + uVar55 + lVar62);
                                  fVar93 = *(float *)((long)pvVar24 + uVar55 + lVar62);
                                  iVar43 = iVar106 * iVar106;
                                  iVar106 = iVar106 + 1;
                                  fVar70 = *(float *)((long)local_1110 + uVar55 + lVar62) - fVar113;
                                  fVar91 = fVar99 - fVar111;
                                  fVar95 = fVar93 - fVar112;
                                  fVar91 = (float)NEON_fmadd(fVar95,fVar95,fVar91 * fVar91);
                                  fVar95 = (float)NEON_fmadd((float)(iVar49 * iVar49 + iVar43),
                                                             0x3eb33333,0x3f800000);
                                  fVar70 = 1.0 / (fVar95 * ((fVar70 * fVar70) / fVar110 + 1.0) *
                                                 (fVar91 / fVar115 + 1.0));
                                  fVar114 = (float)NEON_fmadd(fVar70,fVar93,fVar114);
                                  fVar78 = (float)NEON_fmadd(fVar70,fVar99,fVar78);
                                  fVar81 = fVar81 + fVar70;
                                } while (iVar106 != 3);
                                iVar49 = iVar49 + 1;
                              } while (iVar49 != 3);
                              fVar110 = fVar113 + fVar114 / fVar81;
                              fVar111 = fVar113 + fVar78 / fVar81;
                              uVar92 = NEON_fmadd(uVar87,fVar110,fVar113 * fVar82);
                              uVar94 = NEON_fmadd(uVar69,fVar110,fVar113 * fVar66);
                              uVar88 = NEON_fmadd(uVar64,fVar110,fVar113 * fVar89);
                              uVar92 = NEON_fmadd(uVar67,fVar111,uVar92);
                              uVar94 = NEON_fmadd(uVar68,fVar111,uVar94);
                              uVar88 = NEON_fmadd(uVar80,fVar111,uVar88);
                              fVar111 = (float)NEON_fminnm(uVar92,0x3f800000);
                              fVar112 = (float)NEON_fminnm(uVar94,0x3f800000);
                              fVar110 = (float)NEON_fminnm(uVar88,0x3f800000);
                              if (fVar111 <= 0.0) {
                                fVar111 = 0.0;
                              }
                              if (fVar112 <= 0.0) {
                                fVar112 = 0.0;
                              }
                              if (fVar110 <= 0.0) {
                                fVar110 = 0.0;
                              }
                              fVar111 = fVar111 * 1023.0;
                              fVar112 = fVar112 * 1023.0;
                              fVar110 = fVar110 * 1023.0;
                              iVar104 = (int)fVar111;
                              iVar106 = (int)fVar112;
                              iVar43 = (int)fVar110;
                              iVar49 = iVar104;
                              if (0x3fd < iVar104) {
                                iVar49 = 0x3fe;
                              }
                              iVar16 = iVar106;
                              if (0x3fd < iVar106) {
                                iVar16 = 0x3fe;
                              }
                              iVar8 = iVar43;
                              if (0x3fd < iVar43) {
                                iVar8 = 0x3fe;
                              }
                              fVar111 = (float)NEON_fmadd(*(undefined4 *)
                                                           (lVar52 + (long)iVar104 * 4),
                                                          1.0 - (fVar111 - (float)(int)fVar111),
                                                          *(float *)(lVar52 + 4 + (long)iVar49 * 4)
                                                          * (fVar111 - (float)(int)fVar111));
                              fVar112 = (float)NEON_fmadd(*(undefined4 *)
                                                           (lVar52 + 0x1000 + (long)iVar106 * 4),
                                                          1.0 - (fVar112 - (float)(int)fVar112),
                                                          *(float *)(lVar52 + 0x1004 +
                                                                    (long)iVar16 * 4) *
                                                          (fVar112 - (float)(int)fVar112));
                              fVar110 = (float)NEON_fmadd(*(undefined4 *)
                                                           (lVar52 + 0x2000 + (long)iVar43 * 4),
                                                          1.0 - (fVar110 - (float)(int)fVar110),
                                                          *(float *)(lVar52 + 0x2004 +
                                                                    (long)iVar8 * 4) *
                                                          (fVar110 - (float)(int)fVar110));
                              if (((ulong)param_2 & 1) != 0) {
                                fVar113 = (float)NEON_fminnm(fVar111,0x3f800000);
                                if (fVar113 <= 0.0) {
                                  fVar113 = 0.0;
                                }
                                if (fVar113 <= 0.04045) {
                                  fVar113 = fVar113 / 12.92;
                                }
                                else {
                                  fVar113 = powf((fVar113 + 0.055) / 1.055,2.4);
                                }
                                fVar114 = (float)NEON_fminnm(fVar112,0x3f800000);
                                if (fVar114 <= 0.0) {
                                  fVar114 = 0.0;
                                }
                                if (fVar114 <= 0.04045) {
                                  fVar114 = fVar114 / 12.92;
                                }
                                else {
                                  fVar114 = powf((fVar114 + 0.055) / 1.055,2.4);
                                }
                                fVar110 = (float)NEON_fminnm(fVar110,0x3f800000);
                                if (fVar110 <= 0.0) {
                                  fVar110 = 0.0;
                                }
                                if (fVar110 <= 0.04045) {
                                  fVar110 = fVar110 / 12.92;
                                }
                                else {
                                  fVar110 = powf((fVar110 + 0.055) / 1.055,2.4);
                                }
                                uVar88 = NEON_fmadd(fVar113,0x3f528cde,fVar114 * 0.177538);
                                fVar111 = (float)NEON_fminnm(uVar88,0x3f800000);
                                if (fVar111 <= 0.0) {
                                  fVar111 = 0.0;
                                }
                                if (fVar111 <= 0.0031308) {
                                  fVar111 = fVar111 * 12.92;
                                }
                                else {
                                  fVar111 = powf(fVar111,0.4166667);
                                  fVar111 = (float)NEON_fmadd(fVar111,0x3f870a3d,0xbd6147ae);
                                }
                                uVar88 = NEON_fmadd(fVar113,0x3d07f6a4,fVar114 * 0.9668058);
                                fVar112 = (float)NEON_fminnm(uVar88,0x3f800000);
                                if (fVar112 <= 0.0) {
                                  fVar112 = 0.0;
                                }
                                if (fVar112 <= 0.0031308) {
                                  fVar112 = fVar112 * 12.92;
                                }
                                else {
                                  fVar112 = powf(fVar112,0.4166667);
                                  fVar112 = (float)NEON_fmadd(fVar112,0x3f870a3d,0xbd6147ae);
                                }
                                uVar88 = NEON_fmadd(fVar113,0x3c8bf0e0,fVar114 * 0.07239744);
                                uVar88 = NEON_fmadd(fVar110,0x3f6917d6,uVar88);
                                fVar110 = (float)NEON_fminnm(uVar88,0x3f800000);
                                if (fVar110 <= 0.0) {
                                  fVar110 = 0.0;
                                }
                                if (0.0031308 < fVar110) {
                                  fVar110 = powf(fVar110,0.4166667);
                                  fVar110 = (float)NEON_fmadd(fVar110,0x3f870a3d,0xbd6147ae);
                                }
                                else {
                                  fVar110 = fVar110 * 12.92;
                                }
                              }
                              uVar44 = uVar44 + 1;
                              *pfVar41 = fVar111;
                              pfVar41[1] = fVar112;
                              pfVar41[2] = fVar110;
                            } while (uVar44 != uVar13);
                          }
                          uVar58 = uVar58 + 1;
                        } while (uVar58 != uVar12);
                      }
                      if (pvVar24 != (void *)0x0) {
                        operator_delete(pvVar24);
                      }
                      if (pvVar26 != (void *)0x0) {
                        operator_delete(pvVar26);
                      }
                      if (local_1110 != (void *)0x0) {
                        operator_delete(local_1110);
                      }
                      iVar73 = (int)_UNK_00102e68;
                      iVar74 = (int)((ulong)_UNK_00102e68 >> 0x20);
                      iVar71 = (int)_DAT_00102e60;
                      iVar72 = (int)((ulong)_DAT_00102e60 >> 0x20);
                      lVar34 = 0;
                      do {
                        auVar76._0_4_ = iVar71 + 4;
                        auVar76._4_4_ = iVar72 + 4;
                        auVar76._8_4_ = iVar73 + 4;
                        auVar76._12_4_ = iVar74 + 4;
                        auVar75._4_4_ = iVar72;
                        auVar75._0_4_ = iVar71;
                        auVar75._8_4_ = iVar73;
                        auVar75._12_4_ = iVar74;
                        auVar75 = NEON_scvtf(auVar75,4);
                        iVar71 = iVar71 + 8;
                        iVar72 = iVar72 + 8;
                        iVar73 = iVar73 + 8;
                        iVar74 = iVar74 + 8;
                        lVar52 = lVar34 + 0x20;
                        auVar76 = NEON_scvtf(auVar76,4);
                        auVar77._0_8_ = CONCAT44(auVar76._4_4_ / 255.0,auVar76._0_4_ / 255.0);
                        auVar77._8_4_ = auVar76._8_4_ / 255.0;
                        auVar77._12_4_ = auVar76._12_4_ / 255.0;
                        *(float *)((long)apvStack_4c0 + lVar34 + -8) = auVar75._8_4_ / 255.0;
                        *(float *)((long)apvStack_4c0 + lVar34 + -4) = auVar75._12_4_ / 255.0;
                        *(float *)((long)local_4d8 + lVar34) = auVar75._0_4_ / 255.0;
                        *(float *)((long)local_4d8 + lVar34 + 4) = auVar75._4_4_ / 255.0;
                        *(long *)((long)apvStack_4c0 + lVar34) = auVar77._8_8_;
                        *(undefined8 *)((long)apvStack_4c0 + lVar34 + -8) = auVar77._0_8_;
                        lVar34 = lVar52;
                      } while (lVar52 != 0x400);
                      pfVar41 = *(float **)(ulong)param_3;
                      pfVar10 = ((float **)(ulong)param_3)[1];
                      lVar52 = (long)pfVar10 - (long)pfVar41;
                      lVar34 = lVar52 >> 2;
                      if (((lVar34 == 0x103) || (lVar34 == 0x100)) &&
                         (pfVar11 = *(float **)param_4,
                         *(long *)(param_4 + 8) - (long)pfVar11 == 0x10)) {
                        memset(local_8d8,0,0x400);
                        iVar72 = *(int *)param_1;
                        uVar12 = (int)pfVar11[1] & ((int)pfVar11[1] >> 0x1f ^ 0xffffffffU);
                        uVar58 = (ulong)uVar12;
                        iVar71 = iVar72;
                        if ((int)pfVar11[2] <= iVar72) {
                          iVar71 = (int)pfVar11[2];
                        }
                        iVar73 = *(int *)(param_1 + 2);
                        if ((int)pfVar11[3] <= *(int *)(param_1 + 2)) {
                          iVar73 = (int)pfVar11[3];
                        }
                        pfVar1 = pfVar41;
                        if ((int)uVar12 < iVar73) {
                          uVar86 = 0;
                          fVar66 = 0.0;
                          fVar82 = 0.0;
                          uVar13 = (int)*pfVar11 & ((int)*pfVar11 >> 0x1f ^ 0xffffffffU);
                          uVar55 = (ulong)uVar13;
                          pfVar11 = (float *)((long)apvStack_4c0[125] +
                                             (uVar55 + (long)iVar72 * uVar58) * 0xc + 4);
                          uVar44 = uVar55;
                          uVar12 = uVar13;
                          pfVar33 = pfVar11;
                          do {
                            while ((int)uVar12 < iVar71) {
                              fVar90 = pfVar11[-1];
                              fVar89 = *pfVar11;
                              fVar79 = pfVar11[1];
                              if (((ulong)param_2 & 1) == 0) {
                                uVar64 = NEON_fmadd(fVar90,0x3e59b3d0,fVar89 * 0.7152);
                                uVar80 = 0x3d93dd98;
                              }
                              else {
                                uVar64 = NEON_fmadd(fVar90,0x3e6a786c,fVar89 * 0.691739);
                                uVar80 = 0x3da26139;
                              }
                              uVar80 = NEON_fmadd(fVar79,uVar80,uVar64);
                              fVar97 = fVar89;
                              if (fVar90 <= fVar89) {
                                fVar97 = fVar90;
                              }
                              fVar83 = (float)NEON_fminnm(uVar80,0x3f800000);
                              if (fVar83 <= 0.0) {
                                fVar83 = 0.0;
                              }
                              fVar84 = fVar79;
                              if (fVar97 <= fVar79) {
                                fVar84 = fVar97;
                              }
                              fVar97 = fVar89;
                              if (fVar89 <= fVar90) {
                                fVar97 = fVar90;
                              }
                              fVar85 = fVar79;
                              if (fVar79 <= fVar97) {
                                fVar85 = fVar97;
                              }
                              uVar36 = -(ulong)((uint)(int)(fVar83 * 255.0) >> 0x1f) &
                                       0xfffffffc00000000 | (ulong)(uint)(int)(fVar83 * 255.0) << 2;
                              bVar23 = 0.1 <= fVar84;
                              *(float *)((long)local_8d8 + uVar36) =
                                   *(float *)((long)local_8d8 + uVar36) + 1.0;
                              if ((bVar23 && fVar85 == 0.9 || bVar23 && fVar85 < 0.9) &&
                                  fVar85 - fVar84 == 0.2 ||
                                  (bVar23 && fVar85 == 0.9 || bVar23 && fVar85 < 0.9) &&
                                  fVar85 - fVar84 < 0.2) {
                                fVar66 = fVar66 + 1.0;
                                uVar86 = CONCAT44(fVar90 / fVar89 + (float)((ulong)uVar86 >> 0x20),
                                                  fVar79 / fVar89 + (float)uVar86);
                              }
                              fVar82 = fVar82 + 1.0;
                              uVar12 = (int)uVar44 + 8;
                              pfVar11 = pfVar11 + 0x18;
                              uVar44 = (ulong)uVar12;
                            }
                            uVar58 = uVar58 + 8;
                            pfVar11 = pfVar33 + (long)iVar72 * 0x18;
                            uVar44 = uVar55;
                            uVar12 = uVar13;
                            pfVar33 = pfVar11;
                          } while ((int)uVar58 < iVar73);
                          uVar86 = NEON_rev64(uVar86,4);
                          fVar79 = (float)uVar86;
                          fVar89 = (float)((ulong)uVar86 >> 0x20);
                        }
                        else {
                          fVar79 = 0.0;
                          fVar89 = 0.0;
                          fVar66 = 0.0;
                          fVar82 = 0.0;
                        }
                        for (; pfVar1 != pfVar10; pfVar1 = pfVar1 + 1) {
                          fVar90 = *pfVar1;
                          if ((((fVar90 == -NAN ||
                                (int)((int)fVar90 + 1U) < 0 != SCARRY4((int)fVar90,1)) ||
                               0x7e < ((uint)fVar90 & 0x7fffffff) - 0x800000 >> 0x18) &&
                              0x7ffffe < (int)fVar90 - 1U) && ((uint)fVar90 & 0x7fffffff) != 0) {
                            prVar29 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 001144e8 to 001144f3 has its CatchHandler @ 00114664 */
                            std::runtime_error::runtime_error(prVar29,"Invalid tone reference");
                    /* try { // try from 001144f4 to 0011450b has its CatchHandler @ 0011465c */
                    /* WARNING: Subroutine does not return */
                            __cxa_throw(prVar29,PTR_typeinfo_00120dd0,PTR__runtime_error_00120dd8);
                          }
                        }
                        fVar90 = 0.0;
                        lVar34 = 0;
                        do {
                          pauVar5 = (undefined (*) [16])((long)pfVar41 + lVar34);
                          lVar34 = lVar34 + 0x20;
                          auVar75 = *pauVar5;
                          auVar76 = pauVar5[1];
                          fVar90 = fVar90 + auVar75._0_4_ + auVar75._4_4_ + auVar75._8_4_ +
                                   auVar75._12_4_ + auVar76._0_4_ + auVar76._4_4_ + auVar76._8_4_ +
                                   auVar76._12_4_;
                        } while (lVar34 != 0x400);
                        uVar86 = NEON_fmov(0x3f800000,4);
                        if (((lVar52 == 0x40c) && (fVar97 = pfVar41[0x102], 16.0 <= fVar97)) &&
                           (16.0 <= fVar66)) {
                          uVar86 = NEON_fminnm(CONCAT44(((float)((ulong)*(undefined8 *)
                                                                         (pfVar41 + 0x100) >> 0x20)
                                                        / fVar97) / (fVar89 / fVar66),
                                                        ((float)*(undefined8 *)(pfVar41 + 0x100) /
                                                        fVar97) / (fVar79 / fVar66)),
                                               0x3f970a3d3f970a3d,4);
                          uVar86 = NEON_fmaxnm(uVar86,0x3f59999a3f59999a,4);
                        }
                        if ((0.0 < fVar82) && (0.0 < fVar90)) {
                          lVar34 = 4;
                          fVar66 = local_8d8[0] / fVar82 + 0.0;
                          local_cd8[0] = fVar66;
                          fVar79 = *pfVar41 / fVar90 + 0.0;
                          local_10d8[0] = fVar79;
                          do {
                            fVar89 = *(float *)((long)pfVar41 + lVar34);
                            fVar66 = *(float *)((long)local_8d8 + lVar34) / fVar82 + fVar66;
                            *(float *)((long)local_cd8 + lVar34) = fVar66;
                            fVar79 = fVar79 + fVar89 / fVar90;
                            *(float *)((long)local_10d8 + lVar34) = fVar79;
                            lVar34 = lVar34 + 4;
                          } while (lVar34 != 0x400);
                    /* try { // try from 00113980 to 00113987 has its CatchHandler @ 0011458c */
                          puVar27 = (undefined4 *)operator_new(4);
                          puVar47 = puVar27 + 1;
                          *puVar27 = 0;
                    /* try { // try from 001139a0 to 001139a7 has its CatchHandler @ 00114584 */
                          puVar28 = (undefined4 *)operator_new(4);
                          lVar34 = 0;
                          puVar38 = puVar28 + 1;
                          *puVar28 = 0;
                          do {
                            lVar52 = 0;
                            do {
                              if (*(float *)((long)&DAT_00102ff0 + lVar34) <= local_cd8[lVar52])
                              break;
                              lVar52 = lVar52 + 1;
                            } while (lVar52 != 0xff);
                            lVar52 = 0;
                            do {
                              if (*(float *)((long)&DAT_00102ff0 + lVar34) <= local_10d8[lVar52])
                              break;
                              lVar52 = lVar52 + 1;
                            } while (lVar52 != 0xff);
                            lVar34 = lVar34 + 4;
                          } while (lVar34 != 0x38);
                          lVar34 = (long)puVar47 - (long)puVar27 >> 2;
                          uVar58 = lVar34 + 1;
                          if (uVar58 >> 0x3e != 0) goto LAB_0011456c;
                          uVar44 = (long)puVar47 - (long)puVar27 >> 1;
                          if (uVar44 <= uVar58) {
                            uVar44 = uVar58;
                          }
                          if (0x7ffffffffffffffb < (ulong)((long)puVar47 - (long)puVar27)) {
                            uVar44 = 0x3fffffffffffffff;
                          }
                          if (uVar44 == 0) {
                            pvVar24 = (void *)0x0;
                          }
                          else {
                            if (uVar44 >> 0x3e != 0) goto LAB_0011457c;
                    /* try { // try from 00113dec to 00113def has its CatchHandler @ 00114598 */
                            pvVar24 = operator_new(uVar44 << 2);
                          }
                          puVar6 = (undefined4 *)((long)pvVar24 + lVar34 * 4);
                          *puVar6 = 0x3f800000;
                          puVar40 = puVar6;
                          if ((long)puVar47 - (long)puVar27 != 0) {
                            uVar58 = ((long)puVar47 - (long)puVar27) - 4;
                            if ((0x2b < uVar58) &&
                               (0x1f < (ulong)((long)puVar47 +
                                              (-((long)puVar47 - (long)puVar27) - (long)pvVar24))))
                            {
                              puVar51 = (undefined8 *)(puVar27 + -3);
                              uVar58 = (uVar58 >> 2) + 1;
                              uVar55 = uVar58 & 0x7ffffffffffffff8;
                              puVar47 = puVar47 + -uVar55;
                              puVar40 = puVar6 + -uVar55;
                              puVar50 = (undefined8 *)(puVar6 + -4);
                              uVar44 = uVar55;
                              do {
                                puVar19 = puVar51 + -1;
                                uVar65 = puVar51[-2];
                                uVar108 = puVar51[1];
                                uVar63 = *puVar51;
                                uVar44 = uVar44 - 8;
                                puVar51 = puVar51 + -4;
                                puVar50[-1] = *puVar19;
                                puVar50[-2] = uVar65;
                                puVar50[1] = uVar108;
                                *puVar50 = uVar63;
                                puVar50 = puVar50 + -4;
                              } while (uVar44 != 0);
                              if (uVar58 == uVar55) goto LAB_00113e54;
                            }
                            do {
                              puVar47 = puVar47 + -1;
                              puVar40 = puVar40 + -1;
                              *puVar40 = *puVar47;
                            } while (puVar47 != puVar27);
                          }
LAB_00113e54:
                          if (puVar27 != (undefined4 *)0x0) {
                            operator_delete(puVar27);
                          }
                          lVar34 = (long)puVar38 - (long)puVar28 >> 2;
                          uVar58 = lVar34 + 1;
                          if (uVar58 >> 0x3e != 0) goto LAB_00114574;
                          uVar44 = (long)puVar38 - (long)puVar28 >> 1;
                          if (uVar44 <= uVar58) {
                            uVar44 = uVar58;
                          }
                          if (0x7ffffffffffffffb < (ulong)((long)puVar38 - (long)puVar28)) {
                            uVar44 = 0x3fffffffffffffff;
                          }
                          if (uVar44 == 0) {
                            pvVar24 = (void *)0x0;
                          }
                          else {
                            if (uVar44 >> 0x3e != 0) {
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00114580 to 00114583 has its CatchHandler @ 00114594 */
                              std::__throw_bad_array_new_length_abi_ne180000_();
                            }
                    /* try { // try from 00113ed8 to 00113edb has its CatchHandler @ 00114594 */
                            pvVar24 = operator_new(uVar44 << 2);
                          }
                          puVar27 = (undefined4 *)((long)pvVar24 + lVar34 * 4);
                          *puVar27 = 0x3f800000;
                          puVar47 = puVar27;
                          if ((long)puVar38 - (long)puVar28 != 0) {
                            uVar58 = ((long)puVar38 - (long)puVar28) - 4;
                            if ((0x2b < uVar58) &&
                               (0x1f < (ulong)((long)puVar38 +
                                              (-((long)puVar38 - (long)puVar28) - (long)pvVar24))))
                            {
                              uVar58 = (uVar58 >> 2) + 1;
                              uVar55 = uVar58 & 0x7ffffffffffffff8;
                              puVar38 = puVar38 + -uVar55;
                              puVar47 = puVar27 + -uVar55;
                              puVar50 = (undefined8 *)(puVar27 + -4);
                              puVar51 = (undefined8 *)(puVar28 + -3);
                              uVar44 = uVar55;
                              do {
                                puVar19 = puVar51 + -1;
                                uVar65 = puVar51[-2];
                                uVar108 = puVar51[1];
                                uVar63 = *puVar51;
                                uVar44 = uVar44 - 8;
                                puVar51 = puVar51 + -4;
                                puVar50[-1] = *puVar19;
                                puVar50[-2] = uVar65;
                                puVar50[1] = uVar108;
                                *puVar50 = uVar63;
                                puVar50 = puVar50 + -4;
                              } while (uVar44 != 0);
                              puVar27 = puVar47;
                              if (uVar58 == uVar55) goto joined_r0x00114388;
                            }
                            do {
                              puVar38 = puVar38 + -1;
                              puVar47 = puVar27 + -1;
                              *puVar47 = *puVar38;
                              puVar27 = puVar47;
                            } while (puVar38 != puVar28);
                          }
joined_r0x00114388:
                          if (puVar28 != (undefined4 *)0x0) {
                            operator_delete(puVar28);
                          }
                          uVar58 = (long)puVar6 + (4 - (long)puVar40) >> 2;
                          lVar34 = 0;
                          lVar52 = 0;
                          do {
                            uVar44 = uVar58;
                            if (uVar58 <= lVar52 + 2U) {
                              uVar44 = lVar52 + 2U;
                            }
                            fVar82 = (float)(int)lVar34 / 255.0;
                            lVar56 = lVar52;
                            do {
                              lVar52 = lVar56;
                              if (uVar58 <= lVar52 + 2U) {
                                lVar56 = uVar44 - 1;
                                fVar66 = (float)puVar40[lVar56];
                                lVar52 = uVar44 - 2;
                                break;
                              }
                              fVar66 = (float)puVar40[lVar52 + 1];
                              lVar56 = lVar52 + 1;
                            } while (fVar66 < fVar82);
                            fVar66 = (fVar82 - (float)puVar40[lVar52]) /
                                     (fVar66 - (float)puVar40[lVar52]);
                            fVar66 = (float)NEON_fmadd(puVar47[lVar52],1.0 - fVar66,
                                                       fVar66 * (float)puVar47[lVar56]);
                            fVar79 = (float)NEON_fminnm(fVar82 * 2.2,0x3f800000);
                            fVar66 = (float)NEON_fmadd(fVar66 - fVar82,0x3f59999a,fVar82);
                            if (fVar79 <= fVar66) {
                              fVar66 = fVar79;
                            }
                            if (fVar66 <= fVar82 * 0.65) {
                              fVar66 = fVar82 * 0.65;
                            }
                            local_4d8[lVar34] = fVar66;
                            lVar34 = lVar34 + 1;
                          } while (lVar34 != 0x100);
                          operator_delete(puVar47);
                          operator_delete(puVar40);
                        }
                      }
                      *in_x8 = (void *)0x0;
                      in_x8[1] = (void *)0x0;
                      in_x8[2] = (void *)0x0;
                      if (__n == 0) {
                        pvVar24 = (void *)0x0;
                      }
                      else {
                        if ((long)__n < 0) {
LAB_0011455c:
                    /* try { // try from 0011455c to 00114563 has its CatchHandler @ 00114608 */
                    /* WARNING: Subroutine does not return */
                          std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>::
                          __throw_length_error_abi_ne180000_();
                        }
                    /* try { // try from 00114060 to 00114067 has its CatchHandler @ 00114608 */
                        pvVar24 = operator_new(__n);
                        *in_x8 = pvVar24;
                        in_x8[2] = (void *)((long)pvVar24 + __n);
                        memset(pvVar24,0,__n);
                        in_x8[1] = (void *)((long)pvVar24 + __n);
                      }
                      if (uVar14 != 0) {
                        if (uVar61 < 2) {
                          uVar61 = 1;
                        }
                        lVar34 = 0;
                        pfVar41 = (float *)((long)apvStack_4c0[125] + 8);
                        do {
                          fVar66 = pfVar41[-2];
                          fVar82 = pfVar41[-1];
                          if (((ulong)param_2 & 1) == 0) {
                            uVar64 = NEON_fmadd(fVar66,0x3e59b3d0,fVar82 * 0.7152);
                            uVar80 = 0x3d93dd98;
                          }
                          else {
                            uVar64 = NEON_fmadd(fVar66,0x3e6a786c,fVar82 * 0.691739);
                            uVar80 = 0x3da26139;
                          }
                          uVar80 = NEON_fmadd(*pfVar41,uVar80,uVar64);
                          fVar79 = (float)NEON_fminnm(uVar80,0x3f800000);
                          fVar66 = (float)uVar86 * fVar66;
                          fVar89 = (float)((ulong)uVar86 >> 0x20) * *pfVar41;
                          if (fVar79 <= 0.0) {
                            fVar79 = 0.0;
                          }
                          pfVar41[-2] = fVar66;
                          pfVar41[-1] = fVar82;
                          *pfVar41 = fVar89;
                          iVar72 = (int)(fVar79 * 255.0);
                          iVar71 = iVar72;
                          if (0xfd < iVar72) {
                            iVar71 = 0xfe;
                          }
                          if (((ulong)param_2 & 1) == 0) {
                            uVar64 = NEON_fmadd(fVar66,0x3e59b3d0,fVar82 * 0.7152);
                            uVar80 = 0x3d93dd98;
                          }
                          else {
                            uVar64 = NEON_fmadd(fVar66,0x3e6a786c,fVar82 * 0.691739);
                            uVar80 = 0x3da26139;
                          }
                          fVar90 = (float)NEON_fmadd(fVar89,uVar80,uVar64);
                          if (1e-08 < fVar90) {
                            fVar90 = fVar79 / fVar90;
                            fVar82 = fVar90 * fVar82;
                            fVar66 = fVar66 * fVar90;
                            fVar89 = fVar89 * fVar90;
                            pfVar41[-2] = fVar66;
                            pfVar41[-1] = fVar82;
                            *pfVar41 = fVar89;
                          }
                          fVar90 = fVar79 * 255.0 - (float)iVar72;
                          fVar83 = 1.0 - fVar90;
                          fVar90 = fVar90 * local_4d8[(long)iVar71 + 1];
                          fVar97 = (float)NEON_fmadd(local_4d8[iVar72],fVar83,fVar90);
                          fVar84 = (float)NEON_fnmadd(local_4d8[iVar72],fVar83,-fVar90);
                          fVar83 = fVar97 / fVar79;
                          fVar90 = 1.0 - fVar97;
                          if (fVar79 <= 1e-05) {
                            fVar83 = 1.0;
                          }
                          fVar85 = fVar83 * (fVar66 - fVar79);
                          fVar66 = fVar90;
                          if ((0.0 < fVar85) || (fVar98 = 1.0, fVar66 = fVar84, fVar85 < 0.0)) {
                            fVar98 = (float)NEON_fminnm(fVar66 / fVar85,0x3f800000);
                          }
                          fVar66 = fVar83 * (fVar82 - fVar79);
                          fVar82 = fVar90;
                          if (((0.0 < fVar66) || (fVar100 = fVar98, fVar82 = fVar84, fVar66 < 0.0))
                             && (fVar100 = fVar82 / fVar66, fVar98 <= fVar82 / fVar66)) {
                            fVar100 = fVar98;
                          }
                          fVar82 = fVar83 * (fVar89 - fVar79);
                          if (((0.0 < fVar82) || (fVar66 = fVar100, fVar90 = fVar84, fVar82 < 0.0))
                             && (fVar66 = fVar90 / fVar82, fVar100 <= fVar90 / fVar82)) {
                            fVar66 = fVar100;
                          }
                          uVar80 = NEON_fmadd(fVar85,fVar66,fVar97);
                          uVar61 = uVar61 - 1;
                          fVar82 = (float)NEON_fminnm(uVar80,0x3f800000);
                          if (fVar82 <= 0.0) {
                            fVar82 = 0.0;
                          }
                          fVar82 = (float)NEON_fmadd(fVar82,0x437f0000,0x3f000000);
                          *(char *)((long)pvVar24 + lVar34) = (char)(int)fVar82;
                          pvVar24 = *in_x8;
                          uVar80 = NEON_fmadd(fVar83 * (pfVar41[-1] - fVar79),fVar66,fVar97);
                          fVar82 = (float)NEON_fminnm(uVar80,0x3f800000);
                          if (fVar82 <= 0.0) {
                            fVar82 = 0.0;
                          }
                          fVar82 = (float)NEON_fmadd(fVar82,0x437f0000,0x3f000000);
                          *(char *)((long)pvVar24 + lVar34 + 1) = (char)(int)fVar82;
                          fVar82 = *pfVar41;
                          *(undefined *)((long)pvVar24 + lVar34 + 3) = 0xff;
                          uVar80 = NEON_fmadd(fVar83 * (fVar82 - fVar79),fVar66,fVar97);
                          fVar82 = (float)NEON_fminnm(uVar80,0x3f800000);
                          if (fVar82 <= 0.0) {
                            fVar82 = 0.0;
                          }
                          fVar82 = (float)NEON_fmadd(fVar82,0x437f0000,0x3f000000);
                          *(char *)((long)pvVar24 + lVar34 + 2) = (char)(int)fVar82;
                          lVar34 = lVar34 + 4;
                          pfVar41 = pfVar41 + 3;
                        } while (uVar61 != 0);
                      }
                      if (apvStack_4c0[125] != (void *)0x0) {
                        apvStack_4c0[126] = apvStack_4c0[125];
                        operator_delete(apvStack_4c0[125]);
                      }
                      if (local_c0 == (void *)0x0) {
                        return;
                      }
                      operator_delete(local_c0);
                      return;
                    }
                  }
                }
              }
              prVar29 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00114480 to 0011448b has its CatchHandler @ 0011467c */
              std::runtime_error::runtime_error(prVar29,"Invalid levels/gains");
              goto LAB_001144c4;
            }
          }
        }
      }
    }
  }
  prVar29 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 001144b8 to 001144c3 has its CatchHandler @ 00114674 */
  std::runtime_error::runtime_error(prVar29,"Invalid RAW calibration");
LAB_001144c4:
                    /* WARNING: Subroutine does not return */
  __cxa_throw(prVar29,PTR_typeinfo_00120dd0,PTR__runtime_error_00120dd8);
}



/* 001146f0 ~Calibration */

/* software_raw::Calibration::~Calibration() */

void __thiscall software_raw::Calibration::~Calibration(Calibration *this)

{
  void *pvVar1;
  
  pvVar1 = *(void **)(this + 0x98);
  if (pvVar1 != (void *)0x0) {
    *(void **)(this + 0xa0) = pvVar1;
    operator_delete(pvVar1);
  }
  pvVar1 = *(void **)(this + 0x80);
  if (pvVar1 != (void *)0x0) {
    *(void **)(this + 0x88) = pvVar1;
    operator_delete(pvVar1);
    return;
  }
  return;
}



/* 00114734 fuse */

/* raw_fusion::fuse(std::__ndk1::vector<unsigned short const*, std::__ndk1::allocator<unsigned short
   const*> > const&, std::__ndk1::vector<std::__ndk1::array<float, 14ul>,
   std::__ndk1::allocator<std::__ndk1::array<float, 14ul> > > const&, int, int, raw_fusion::Stats&)
    */

void __thiscall
raw_fusion::fuse(raw_fusion *this,vector *param_1,vector *param_2,int param_3,int param_4,
                Stats *param_5)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  float *pfVar7;
  ushort *puVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  raw_fusion **pprVar13;
  float *pfVar14;
  int iVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  int iVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  double dVar28;
  bool bVar29;
  bool bVar30;
  undefined4 *puVar31;
  long lVar32;
  void *pvVar33;
  runtime_error *this_00;
  uint uVar34;
  ulong uVar35;
  uint uVar36;
  int *piVar37;
  float *pfVar38;
  int *piVar39;
  int *piVar40;
  int iVar41;
  int *piVar42;
  int iVar43;
  void **in_x8;
  undefined4 *puVar44;
  ulong uVar46;
  ulong uVar47;
  int iVar48;
  uint uVar49;
  ulong uVar50;
  int iVar51;
  ulong uVar52;
  long lVar53;
  undefined8 *puVar54;
  ulong __n;
  long lVar55;
  long *plVar56;
  int iVar57;
  raw_fusion *prVar58;
  int *piVar59;
  void *pvVar60;
  ulong uVar61;
  ulong uVar62;
  long lVar63;
  int iVar64;
  ulong uVar65;
  int *piVar66;
  int *piVar67;
  ulong uVar68;
  float fVar69;
  undefined auVar70 [16];
  float fVar71;
  float fVar72;
  float fVar73;
  float fVar74;
  float fVar75;
  float fVar76;
  undefined4 uVar77;
  float fVar78;
  float fVar79;
  float fVar80;
  undefined8 uVar81;
  float fVar82;
  float fVar83;
  float fVar84;
  float fVar85;
  float fVar86;
  float fVar87;
  undefined4 uVar88;
  float fVar89;
  float fVar90;
  float fVar91;
  float fVar92;
  double local_228;
  double local_1a0;
  uint local_194;
  ulong local_190;
  void *local_108;
  void *local_f0;
  void *local_d8;
  void *local_c0;
  undefined4 *puVar45;
  
  piVar39 = (int *)(ulong)(uint)param_4;
  uVar36 = (uint)param_2;
  if (((0x1fe0 < uVar36 - 0x20) || (0x1fe0 < param_3 - 0x20U)) || (((param_3 | uVar36) & 3) != 0)) {
LAB_00115c98:
    this_00 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00115ca4 to 00115caf has its CatchHandler @ 00115d10 */
    std::runtime_error::runtime_error(this_00,"Invalid RAW burst geometry");
LAB_00115c40:
                    /* WARNING: Subroutine does not return */
    __cxa_throw(this_00,PTR_typeinfo_00120dd0,PTR__runtime_error_00120dd8);
  }
  pprVar13 = *(raw_fusion ***)this;
  if ((pprVar13 == *(raw_fusion ***)(this + 8)) ||
     (uVar50 = (long)*(raw_fusion ***)(this + 8) - (long)pprVar13 >> 3, 5 < uVar50))
  goto LAB_00115c98;
  pfVar14 = *(float **)param_1;
  pfVar38 = pfVar14;
  if (uVar50 != ((long)*(float **)(param_1 + 8) - (long)pfVar14 >> 3) * 0x6db6db6db6db6db7)
  goto LAB_00115c98;
  for (; pfVar38 != *(float **)(param_1 + 8); pfVar38 = pfVar38 + 0xe) {
    fVar71 = *pfVar38;
    if ((((ABS(fVar71) == INFINITY) || (ABS(pfVar38[1]) == INFINITY)) ||
        ((ABS(pfVar38[2]) == INFINITY ||
         (((ABS(pfVar38[3]) == INFINITY || (ABS(pfVar38[4]) == INFINITY)) ||
          (ABS(pfVar38[5]) == INFINITY)))))) ||
       (((ABS(pfVar38[6]) == INFINITY || (ABS(pfVar38[7]) == INFINITY)) ||
        ((ABS(pfVar38[8]) == INFINITY ||
         (((ABS(pfVar38[9]) == INFINITY || (ABS(pfVar38[10]) == INFINITY)) ||
          ((ABS(pfVar38[0xb]) == INFINITY ||
           ((ABS(pfVar38[0xc]) == INFINITY || (ABS(pfVar38[0xd]) == INFINITY)))))))))))) {
      this_00 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00115c34 to 00115c3f has its CatchHandler @ 00115d88 */
      std::runtime_error::runtime_error(this_00,"Invalid burst metadata");
      goto LAB_00115c40;
    }
    if (pfVar38[5] <= 0.0) {
      this_00 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00115c64 to 00115c6f has its CatchHandler @ 00115d84 */
      std::runtime_error::runtime_error(this_00,"Invalid burst exposure");
      goto LAB_00115c40;
    }
    if (((((((fVar71 <= pfVar38[1]) || (pfVar38[6] < 0.0)) || (pfVar38[7] < 0.0)) ||
          ((fVar71 <= pfVar38[2] || (pfVar38[8] < 0.0)))) || (pfVar38[9] < 0.0)) ||
        ((fVar71 <= pfVar38[3] || (pfVar38[10] < 0.0)))) ||
       ((pfVar38[0xb] < 0.0 ||
        (((fVar71 <= pfVar38[4] || (pfVar38[0xc] < 0.0)) || (pfVar38[0xd] < 0.0)))))) {
      this_00 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00115c80 to 00115c8b has its CatchHandler @ 00115d80 */
      std::runtime_error::runtime_error(this_00,"Invalid burst levels");
      goto LAB_00115c40;
    }
  }
  lVar63 = (long)(int)uVar36;
  local_c0 = (void *)0x0;
  uVar50 = (ulong)(uint)param_3;
  uVar68 = uVar50 * lVar63;
  piVar40 = piVar39;
  if (uVar68 == 0) {
    puVar31 = (undefined4 *)0x0;
  }
  else {
    if (uVar68 >> 0x3e != 0) {
                    /* try { // try from 00115cb4 to 00115cbb has its CatchHandler @ 00115cf8 */
      std::__ndk1::vector<float,std::__ndk1::allocator<float>>::__throw_length_error_abi_ne180000_()
      ;
      goto LAB_00115cbc;
    }
    uVar65 = uVar68 * 4;
                    /* try { // try from 001149c0 to 001149c7 has its CatchHandler @ 00115cf8 */
    local_c0 = operator_new(uVar65);
    memset(local_c0,0,uVar65);
                    /* try { // try from 001149ec to 001149f3 has its CatchHandler @ 00115cc4 */
    puVar31 = (undefined4 *)operator_new(uVar65);
    uVar65 = lVar63 * uVar50 - 1 & 0x3fffffffffffffff;
    puVar44 = puVar31;
    if (6 < uVar65) {
      uVar65 = uVar65 + 1;
      auVar70 = NEON_fmov(0x3f800000,4);
      puVar54 = (undefined8 *)(puVar31 + 4);
      uVar52 = uVar65 & 0x7ffffffffffffff8;
      puVar44 = puVar31 + uVar52;
      uVar46 = uVar52;
      do {
        puVar54[-1] = auVar70._8_8_;
        puVar54[-2] = auVar70._0_8_;
        puVar54[1] = auVar70._8_8_;
        *puVar54 = auVar70._0_8_;
        uVar46 = uVar46 - 8;
        puVar54 = puVar54 + 4;
      } while (uVar46 != 0);
      if (uVar65 == uVar52) goto LAB_00114a68;
    }
    do {
      puVar45 = puVar44 + 1;
      *puVar44 = 0x3f800000;
      puVar44 = puVar45;
    } while (puVar45 != puVar31 + uVar68);
  }
LAB_00114a68:
  if (0 < param_3) {
    uVar46 = 0;
    uVar65 = 0;
    do {
      if (0 < (int)uVar36) {
        prVar58 = *pprVar13;
        uVar52 = 0;
        do {
          fVar71 = (float)NEON_ucvtf((uint)*(ushort *)(prVar58 + uVar52 * 2 + uVar46 * 2));
          *(float *)((long)local_c0 + uVar52 * 4 + uVar46 * 4) =
               (fVar71 - pfVar14[((uVar65 & 1) << 1 | 1) + (uVar52 & 1)]) /
               (*pfVar14 - pfVar14[((uVar65 & 1) << 1 | 1) + (uVar52 & 1)]);
          uVar52 = uVar52 + 1;
        } while (((ulong)param_2 & 0xffffffff) != uVar52);
      }
      uVar65 = uVar65 + 1;
      uVar46 = (ulong)((int)uVar46 + uVar36);
    } while (uVar65 != uVar50);
  }
  uVar9 = uVar36 + 3;
  if (-1 < (int)uVar36) {
    uVar9 = uVar36;
  }
                    /* try { // try from 00114b04 to 00114b17 has its CatchHandler @ 00115ccc */
  guide(*pprVar13,(ushort *)((ulong)param_2 & 0xffffffff),param_3,(int)pfVar14,(array *)piVar40,1.0)
  ;
  dVar28 = DAT_00102f18;
  lVar53 = *(long *)this;
  lVar55 = *(long *)(this + 8);
  uVar65 = lVar55 - lVar53 >> 3;
  if (uVar65 < 2) {
    local_228 = 0.0;
  }
  else {
    iVar15 = uVar36 + 0xfe;
    if ((int)(uVar36 + 0x7f) < 0 == SCARRY4(uVar36,0x7f)) {
      iVar15 = uVar36 + 0x7f;
    }
    uVar9 = (int)uVar9 >> 2;
    uVar46 = (ulong)uVar9;
    uVar10 = iVar15 >> 7;
    uVar16 = param_3 + 0x7fU >> 7;
    uVar17 = (uint)param_3 >> 2;
    piVar67 = (int *)(ulong)uVar17;
    uVar18 = uVar16 * uVar10;
    uVar12 = uVar10;
    if ((int)uVar10 < 2) {
      uVar12 = 1;
    }
    if (uVar16 < 2) {
      uVar16 = 1;
    }
    piVar66 = (int *)(long)(int)uVar9;
    __n = -(ulong)(uVar18 >> 0x1f) & 0xfffffff800000000 | (ulong)uVar18 << 3;
    uVar62 = -(ulong)(uVar9 >> 0x1f) & 0xfffffff800000000 | uVar46 << 3;
    iVar15 = uVar9 * 2;
    fVar71 = 0.0025;
    local_228 = 0.0;
    uVar52 = 1;
    do {
      pfVar38 = (float *)(*(long *)param_1 + uVar52 * 0x38);
      fVar84 = pfVar14[5] / pfVar38[5];
      if (ABS(fVar84 + -1.0) <= 0.06) {
                    /* try { // try from 00114cc8 to 00114cdf has its CatchHandler @ 00115d48 */
        guide(*(raw_fusion **)(lVar53 + uVar52 * 8),(ushort *)((ulong)param_2 & 0xffffffff),param_3,
              (int)pfVar38,(array *)piVar40,fVar84);
        iVar64 = 0;
        lVar53 = -0xc;
        fVar76 = 1e+09;
        iVar4 = 0;
        uVar65 = (ulong)(uVar9 * -0xc - 0xc);
        do {
          lVar55 = -0xc;
          uVar35 = uVar65;
          iVar43 = iVar64;
          fVar72 = fVar76;
          iVar41 = iVar4;
          do {
            if (param_3 == 0) {
LAB_00114d28:
              fVar76 = 1e+09;
            }
            else {
              fVar76 = 0.0;
              piVar59 = (int *)0x0;
              iVar64 = 0;
              pvVar60 = local_d8;
              uVar47 = uVar35;
              do {
                if (3 < (int)uVar36) {
                  lVar32 = 0;
                  do {
                    if (((int *)(lVar55 + lVar32) < piVar66) &&
                       ((int *)((long)piVar59 + lVar53) < piVar67)) {
                      iVar64 = iVar64 + 1;
                      fVar73 = *(float *)((long)pvVar60 + lVar32 * 4) -
                               *(float *)((long)local_f0 + (long)((int)uVar47 + (int)lVar32) * 4);
                      fVar73 = fVar73 * fVar73;
                      fVar74 = fVar71;
                      if (fVar73 <= 0.0025) {
                        fVar74 = fVar73;
                      }
                      fVar76 = fVar76 + fVar74;
                    }
                    lVar32 = lVar32 + 8;
                  } while (lVar32 < (long)piVar66);
                }
                piVar59 = piVar59 + 2;
                uVar47 = uVar47 + (uVar9 << 3);
                pvVar60 = (void *)((long)pvVar60 +
                                  (-(ulong)(uVar9 >> 0x1f) & 0xffffffe000000000 | uVar46 << 5));
              } while (piVar59 < piVar67);
              if (iVar64 == 0) goto LAB_00114d28;
              fVar76 = fVar76 / (float)iVar64;
            }
            bVar29 = fVar72 <= fVar76;
            uVar35 = uVar35 + 1;
            if (bVar29) {
              fVar76 = fVar72;
            }
            iVar64 = (int)lVar55;
            if (bVar29) {
              iVar64 = iVar43;
            }
            lVar55 = lVar55 + 1;
            iVar4 = (int)lVar53;
            if (bVar29) {
              iVar4 = iVar41;
            }
            iVar43 = iVar64;
            fVar72 = fVar76;
            iVar41 = iVar4;
          } while (lVar55 != 0xd);
          lVar53 = lVar53 + 1;
          uVar65 = uVar65 + uVar46;
        } while (lVar53 != 0xd);
        local_108 = (void *)0x0;
        if (uVar18 != 0) {
          if ((int)uVar18 < 0) {
                    /* try { // try from 00115c90 to 00115c97 has its CatchHandler @ 00115d14 */
            std::__ndk1::
            vector<std::__ndk1::array<float,2ul>,std::__ndk1::allocator<std::__ndk1::array<float,2ul>>>
            ::__throw_length_error_abi_ne180000_();
            goto LAB_00115c98;
          }
                    /* try { // try from 00114e1c to 00114e27 has its CatchHandler @ 00115d30 */
          local_108 = operator_new(__n);
          memset(local_108,0,__n);
        }
        local_1a0 = 0.0;
        if (param_3 != 0) {
          local_190 = 0;
          local_194 = 0xfffffff8;
          do {
            if (0 < (int)uVar36) {
              uVar65 = 0;
              uVar49 = local_194 & ((int)local_194 >> 0x1f ^ 0xffffffffU);
              pvVar60 = (void *)((long)local_d8 +
                                (-(ulong)(uVar9 >> 0x1f) & 0xfffffffc00000000 | uVar46 << 2) *
                                (ulong)uVar49);
              iVar41 = (int)local_190 * 0x20;
              uVar1 = iVar41 + 0x28;
              uVar19 = iVar41 - 8;
              uVar19 = uVar19 & ((int)uVar19 >> 0x1f ^ 0xffffffffU);
              piVar59 = (int *)(ulong)uVar19;
              if ((int)uVar17 <= (int)uVar1) {
                uVar1 = uVar17;
              }
              piVar42 = (int *)(ulong)uVar1;
              uVar34 = 0xfffffff8;
              do {
                uVar11 = uVar34 & ((int)uVar34 >> 0x1f ^ 0xffffffffU);
                iVar41 = (int)uVar65 * 0x20;
                fVar76 = 1e+09;
                uVar2 = iVar41 + 0x28;
                uVar20 = iVar41 - 8;
                iVar41 = iVar64 + -3 + uVar9 * (iVar4 + -3 + uVar49) + uVar11;
                uVar20 = uVar20 & ((int)uVar20 >> 0x1f ^ 0xffffffffU);
                uVar35 = (ulong)uVar20;
                if ((int)uVar9 <= (int)uVar2) {
                  uVar2 = uVar9;
                }
                uVar47 = (ulong)uVar2;
                lVar53 = (long)(iVar4 + -3);
                iVar51 = iVar4;
                iVar43 = iVar64;
                do {
                  iVar21 = (int)lVar53 - iVar4;
                  lVar55 = (long)(iVar64 + -3);
                  iVar57 = iVar41;
                  iVar48 = iVar43;
                  do {
                    if (uVar19 < uVar1) {
                      fVar72 = 0.0;
                      iVar43 = 0;
                      pvVar33 = pvVar60;
                      piVar40 = piVar59;
                      iVar5 = iVar57;
                      do {
                        if ((int)uVar20 < (int)uVar2) {
                          uVar61 = uVar35;
                          iVar3 = iVar5;
                          do {
                            if (((int *)(lVar55 + uVar61) < piVar66) &&
                               ((int *)((long)piVar40 + lVar53) < piVar67)) {
                              iVar43 = iVar43 + 1;
                              fVar73 = *(float *)((long)pvVar33 + uVar61 * 4) -
                                       *(float *)((long)local_f0 + (long)iVar3 * 4);
                              fVar73 = fVar73 * fVar73;
                              fVar74 = fVar71;
                              if (fVar73 <= 0.0025) {
                                fVar74 = fVar73;
                              }
                              fVar72 = fVar72 + fVar74;
                            }
                            uVar61 = uVar61 + 2;
                            iVar3 = iVar3 + 2;
                          } while (uVar61 < uVar47);
                        }
                        piVar40 = (int *)((long)piVar40 + 2);
                        iVar5 = iVar5 + iVar15;
                        pvVar33 = (void *)((long)pvVar33 + uVar62);
                      } while (piVar40 < piVar42);
                      if (iVar43 == 0) goto LAB_00115064;
                      fVar72 = fVar72 / (float)iVar43;
                    }
                    else {
LAB_00115064:
                      fVar72 = 1e+09;
                    }
                    iVar43 = (int)lVar55 - iVar64;
                    iVar57 = iVar57 + 1;
                    fVar72 = (float)NEON_fmadd((float)(iVar21 * iVar21 + iVar43 * iVar43),0x32abcc77
                                               ,fVar72);
                    iVar43 = (int)lVar55;
                    iVar5 = (int)lVar53;
                    if (fVar76 <= fVar72) {
                      iVar43 = iVar48;
                      iVar5 = iVar51;
                      fVar72 = fVar76;
                    }
                    fVar76 = fVar72;
                    iVar51 = iVar5;
                    bVar29 = lVar55 < iVar64 + 3;
                    lVar55 = lVar55 + 1;
                    iVar48 = iVar43;
                  } while (bVar29);
                  iVar41 = iVar41 + uVar9;
                  bVar29 = lVar53 < iVar4 + 3;
                  lVar53 = lVar53 + 1;
                } while (bVar29);
                if (uVar19 < uVar1) {
                  auVar70 = ZEXT816(0);
                  lVar53 = (long)iVar43;
                  iVar41 = 0;
                  iVar57 = iVar43 + uVar9 * (uVar49 + iVar51);
                  lVar55 = (long)iVar51;
                  pvVar33 = pvVar60;
                  piVar37 = piVar59;
                  do {
                    if ((int)uVar20 < (int)uVar2) {
                      uVar61 = uVar35;
                      do {
                        piVar40 = (int *)(lVar53 + uVar61);
                        if ((piVar40 < piVar66) && ((int *)((long)piVar37 + lVar55) < piVar67)) {
                          uVar6 = iVar57 + (int)uVar61;
                          piVar40 = (int *)(ulong)uVar6;
                          iVar41 = iVar41 + 1;
                          fVar72 = *(float *)((long)pvVar33 + uVar61 * 4) -
                                   *(float *)((long)local_f0 + (long)(int)uVar6 * 4);
                          fVar72 = fVar72 * fVar72;
                          fVar76 = fVar71;
                          if (fVar72 <= 0.0025) {
                            fVar76 = fVar72;
                          }
                          auVar70._0_8_ = auVar70._0_8_ + (double)fVar76;
                          auVar70._8_8_ = 0;
                        }
                        uVar61 = uVar61 + 2;
                      } while (uVar61 < uVar47);
                    }
                    piVar37 = (int *)((long)piVar37 + 2);
                    iVar57 = iVar57 + iVar15;
                    pvVar33 = (void *)((long)pvVar33 + uVar62);
                  } while (piVar37 < piVar42);
                  if (iVar41 == 0) {
                    fVar72 = 1e+09;
                  }
                  else {
                    fVar72 = (float)(auVar70._0_8_ / (double)iVar41);
                  }
                  fVar76 = 0.0;
                  iVar41 = 0;
                  iVar57 = iVar43 + -1 + uVar11 + uVar9 * (uVar49 + iVar51);
                  pvVar33 = pvVar60;
                  piVar37 = piVar59;
                  do {
                    if ((int)uVar20 < (int)uVar2) {
                      piVar40 = (int *)((long)piVar37 + lVar55);
                      uVar61 = uVar35;
                      iVar21 = iVar57;
                      do {
                        if (((int *)((long)(iVar43 + -1) + uVar61) < piVar66) && (piVar40 < piVar67)
                           ) {
                          iVar41 = iVar41 + 1;
                          fVar73 = *(float *)((long)pvVar33 + uVar61 * 4) -
                                   *(float *)((long)local_f0 + (long)iVar21 * 4);
                          fVar73 = fVar73 * fVar73;
                          fVar74 = fVar71;
                          if (fVar73 <= 0.0025) {
                            fVar74 = fVar73;
                          }
                          fVar76 = fVar76 + fVar74;
                        }
                        uVar61 = uVar61 + 2;
                        iVar21 = iVar21 + 2;
                      } while (uVar61 < uVar47);
                    }
                    piVar37 = (int *)((long)piVar37 + 2);
                    iVar57 = iVar57 + iVar15;
                    pvVar33 = (void *)((long)pvVar33 + uVar62);
                  } while (piVar37 < piVar42);
                  if (iVar41 == 0) {
                    fVar76 = 1e+09;
                  }
                  else {
                    fVar76 = fVar76 / (float)iVar41;
                  }
                  fVar74 = 0.0;
                  iVar41 = 0;
                  iVar57 = iVar43 + 1 + uVar11 + uVar9 * (uVar49 + iVar51);
                  pvVar33 = pvVar60;
                  piVar37 = piVar59;
                  do {
                    if ((int)uVar20 < (int)uVar2) {
                      piVar40 = (int *)((long)piVar37 + lVar55);
                      uVar61 = uVar35;
                      iVar21 = iVar57;
                      do {
                        if (((int *)((long)(iVar43 + 1) + uVar61) < piVar66) && (piVar40 < piVar67))
                        {
                          iVar41 = iVar41 + 1;
                          fVar75 = *(float *)((long)pvVar33 + uVar61 * 4) -
                                   *(float *)((long)local_f0 + (long)iVar21 * 4);
                          fVar75 = fVar75 * fVar75;
                          fVar73 = fVar71;
                          if (fVar75 <= 0.0025) {
                            fVar73 = fVar75;
                          }
                          fVar74 = fVar74 + fVar73;
                        }
                        uVar61 = uVar61 + 2;
                        iVar21 = iVar21 + 2;
                      } while (uVar61 < uVar47);
                    }
                    piVar37 = (int *)((long)piVar37 + 2);
                    iVar57 = iVar57 + iVar15;
                    pvVar33 = (void *)((long)pvVar33 + uVar62);
                  } while (piVar37 < piVar42);
                  if (iVar41 == 0) {
                    fVar74 = 1e+09;
                  }
                  else {
                    fVar74 = fVar74 / (float)iVar41;
                  }
                  fVar73 = 0.0;
                  iVar41 = 0;
                  iVar57 = iVar43 + uVar9 * ((uVar49 - 1) + iVar51);
                  pvVar33 = pvVar60;
                  piVar37 = piVar59;
                  do {
                    if ((int)uVar20 < (int)uVar2) {
                      uVar61 = uVar35;
                      do {
                        piVar40 = (int *)(lVar53 + uVar61);
                        if ((piVar40 < piVar66) &&
                           ((int *)((long)piVar37 + (long)(iVar51 + -1)) < piVar67)) {
                          uVar11 = iVar57 + (int)uVar61;
                          piVar40 = (int *)(ulong)uVar11;
                          iVar41 = iVar41 + 1;
                          fVar78 = *(float *)((long)pvVar33 + uVar61 * 4) -
                                   *(float *)((long)local_f0 + (long)(int)uVar11 * 4);
                          fVar78 = fVar78 * fVar78;
                          fVar75 = fVar71;
                          if (fVar78 <= 0.0025) {
                            fVar75 = fVar78;
                          }
                          fVar73 = fVar73 + fVar75;
                        }
                        uVar61 = uVar61 + 2;
                      } while (uVar61 < uVar47);
                    }
                    piVar37 = (int *)((long)piVar37 + 2);
                    iVar57 = iVar57 + iVar15;
                    pvVar33 = (void *)((long)pvVar33 + uVar62);
                  } while (piVar37 < piVar42);
                  if (iVar41 == 0) {
                    fVar73 = 1e+09;
                  }
                  else {
                    fVar73 = fVar73 / (float)iVar41;
                  }
                  fVar75 = 0.0;
                  iVar41 = 0;
                  iVar57 = iVar43 + uVar9 * (uVar49 + 1 + iVar51);
                  pvVar33 = pvVar60;
                  piVar37 = piVar59;
                  do {
                    if ((int)uVar20 < (int)uVar2) {
                      uVar61 = uVar35;
                      do {
                        piVar40 = (int *)(lVar53 + uVar61);
                        if ((piVar40 < piVar66) &&
                           ((int *)((long)piVar37 + (long)(iVar51 + 1)) < piVar67)) {
                          uVar11 = iVar57 + (int)uVar61;
                          piVar40 = (int *)(ulong)uVar11;
                          iVar41 = iVar41 + 1;
                          fVar79 = *(float *)((long)pvVar33 + uVar61 * 4) -
                                   *(float *)((long)local_f0 + (long)(int)uVar11 * 4);
                          fVar79 = fVar79 * fVar79;
                          fVar78 = fVar71;
                          if (fVar79 <= 0.0025) {
                            fVar78 = fVar79;
                          }
                          fVar75 = fVar75 + fVar78;
                        }
                        uVar61 = uVar61 + 2;
                      } while (uVar61 < uVar47);
                    }
                    piVar37 = (int *)((long)piVar37 + 2);
                    iVar57 = iVar57 + iVar15;
                    pvVar33 = (void *)((long)pvVar33 + uVar62);
                  } while (piVar37 < piVar42);
                  if (iVar41 == 0) {
                    fVar75 = 1e+09;
                  }
                  else {
                    fVar75 = fVar75 / (float)iVar41;
                  }
                  uVar81 = 0;
                  if (1e-12 <= fVar72) goto LAB_00114f74;
                }
                else {
                  fVar76 = 1e+09;
                  fVar73 = 1e+09;
                  fVar72 = 1e+09;
                  fVar75 = 1e+09;
                  fVar74 = fVar76;
LAB_00114f74:
                  uVar81 = NEON_fmaxnm(CONCAT44(fVar75 + fVar73 + fVar72 * -2.0,
                                                fVar74 + fVar76 + fVar72 * -2.0),0x2b8cbccc2b8cbccc,
                                       4);
                  uVar81 = NEON_fminnm(CONCAT44(((fVar73 - fVar75) * 0.5) /
                                                (float)((ulong)uVar81 >> 0x20),
                                                ((fVar76 - fVar74) * 0.5) / (float)uVar81),
                                       0x3f0000003f000000,4);
                  uVar81 = NEON_fmaxnm(uVar81,0xbf000000bf000000,4);
                }
                lVar53 = uVar65 + uVar10 * (int)local_190;
                uVar65 = uVar65 + 1;
                pfVar7 = (float *)((long)local_108 + lVar53 * 8);
                uVar34 = uVar34 + 0x20;
                *pfVar7 = ((float)uVar81 + (float)iVar43) * 4.0;
                pfVar7[1] = ((float)((ulong)uVar81 >> 0x20) + (float)iVar51) * 4.0;
              } while (uVar65 != uVar12);
            }
            local_190 = local_190 + 1;
            local_194 = local_194 + 0x20;
          } while (local_190 != uVar16);
          if (8 < param_3) {
            uVar65 = 4;
            local_1a0 = 0.0;
            iVar64 = uVar36 * 2 + 4;
            do {
              if (8 < (int)uVar36) {
                uVar49 = (uint)uVar65;
                uVar1 = uVar49 & 1;
                plVar56 = *(long **)this;
                uVar35 = 4;
                iVar4 = iVar64;
                do {
                  uVar34 = (uint)uVar35;
                  uVar19 = uVar34 & 1;
                  piVar40 = (int *)(ulong)uVar19;
                  pfVar7 = (float *)((long)local_108 +
                                    (ulong)(((uint)(uVar65 >> 7) & 0x1ffffff) * uVar10 +
                                           (uVar34 >> 7)) * 8);
                  fVar72 = *pfVar7 + (float)uVar34;
                  fVar76 = pfVar7[1] + (float)uVar49;
                  iVar43 = (int)((fVar72 - (float)uVar19) * 0.5);
                  iVar41 = (int)((fVar76 - (float)uVar1) * 0.5);
                  uVar34 = uVar34 & 1 | iVar43 << 1;
                  uVar2 = uVar1 | iVar41 << 1;
                  bVar29 = true;
                  if (3 < (int)uVar34) {
                    bVar29 = (int)(uVar2 - 4) < 0;
                  }
                  bVar29 = bVar29 == (3 < (int)uVar34 && SBORROW4(uVar2,4));
                  bVar30 = false;
                  if (bVar29) {
                    bVar30 = (int)((uVar34 + 6) - uVar36) < 0;
                  }
                  bVar29 = bVar30 != (bVar29 && SBORROW4(uVar34 + 6,uVar36));
                  bVar30 = false;
                  if (bVar29) {
                    bVar30 = (int)((uVar2 + 6) - param_3) < 0;
                  }
                  if (bVar30 != (bVar29 && SBORROW4(uVar2 + 6,param_3))) {
                    lVar32 = plVar56[uVar52];
                    fVar82 = pfVar38[(uVar19 | uVar1 << 1) + 1];
                    fVar75 = (float)NEON_ucvtf((uint)*(ushort *)
                                                      (lVar32 + (long)(int)(uVar2 * uVar36 +
                                                                           uVar34 + 2) * 2));
                    iVar51 = (uVar2 + 2) * uVar36;
                    uVar6 = ((uVar49 & 1) << 1 | 1) + uVar19;
                    fVar74 = *pfVar38 - fVar82;
                    fVar73 = (float)NEON_ucvtf((uint)*(ushort *)
                                                      (lVar32 + (long)(int)(iVar51 + uVar34) * 2));
                    uVar20 = uVar1 << 2 | uVar19 << 1;
                    fVar78 = (float)NEON_ucvtf((uint)*(ushort *)
                                                      (lVar32 + (long)(int)(iVar51 + uVar34 + 2) * 2
                                                      ));
                    uVar11 = uVar20 + 6;
                    uVar20 = uVar20 + 7;
                    uVar47 = (ulong)((uVar49 & 1) + iVar41 * 2);
                    fVar79 = (float)NEON_ucvtf((uint)*(ushort *)
                                                      (lVar32 + (long)(int)(uVar2 * uVar36 + uVar34)
                                                                * 2));
                    lVar55 = *plVar56;
                    lVar53 = uVar35 + uVar49 * uVar36;
                    fVar80 = (fVar72 - (float)uVar34) * 0.5;
                    fVar83 = 1.0 - fVar80;
                    fVar87 = (float)NEON_ucvtf((uint)*(ushort *)(lVar55 + lVar53 * 2));
                    fVar76 = (fVar76 - (float)uVar2) * 0.5;
                    fVar73 = (float)NEON_fmadd((fVar73 - fVar82) / fVar74,fVar83,
                                               fVar80 * ((fVar78 - fVar82) / fVar74));
                    fVar72 = pfVar14[uVar6];
                    fVar86 = *pfVar14 - fVar72;
                    uVar77 = NEON_fmadd((fVar79 - fVar82) / fVar74,fVar83,
                                        fVar80 * ((fVar75 - fVar82) / fVar74));
                    fVar74 = 1.0 - fVar76;
                    fVar78 = (fVar87 - fVar72) / fVar86;
                    fVar79 = 0.0;
                    fVar75 = (float)NEON_fmadd(uVar77,fVar74,fVar76 * fVar73);
                    fVar75 = fVar84 * fVar75;
                    fVar73 = fVar78;
                    if (fVar78 <= 0.0) {
                      fVar73 = 0.0;
                    }
                    uVar77 = NEON_fmadd(pfVar14[uVar11],fVar73,pfVar14[uVar20]);
                    fVar82 = pfVar38[uVar6];
                    fVar87 = *pfVar38 - fVar82;
                    piVar40 = (int *)(lVar32 + (ulong)(iVar43 * 2 + uVar19) * 2);
                    lVar32 = -4;
                    fVar73 = fVar75 / fVar84;
                    if (fVar75 / fVar84 <= 0.0) {
                      fVar73 = 0.0;
                    }
                    uVar88 = NEON_fmadd(pfVar38[uVar11],fVar73,pfVar38[uVar20]);
                    fVar73 = (float)NEON_fmadd(fVar84 * fVar84,uVar88,uVar77);
                    iVar41 = iVar4;
                    do {
                      puVar8 = (ushort *)((long)piVar40 + lVar63 * 2 * uVar47 + 4);
                      piVar59 = (int *)((long)piVar40 + lVar63 * 2 * (uVar47 - 2));
                      iVar51 = iVar41 + -2;
                      fVar23 = (float)NEON_ucvtf((uint)puVar8[-4]);
                      fVar25 = (float)NEON_ucvtf((uint)*puVar8);
                      fVar90 = (float)NEON_ucvtf((uint)*(ushort *)piVar59);
                      fVar69 = (float)NEON_ucvtf((uint)*(ushort *)(piVar59 + 1));
                      fVar22 = (float)NEON_ucvtf((uint)*(ushort *)(piVar59 + -1));
                      fVar27 = (float)NEON_ucvtf((uint)puVar8[2]);
                      lVar32 = lVar32 + 2;
                      piVar40 = piVar40 + lVar63;
                      fVar26 = (float)NEON_ucvtf((uint)*(ushort *)(piVar59 + 2));
                      fVar85 = (float)NEON_ucvtf((uint)*(ushort *)(lVar55 + (long)iVar41 * 2));
                      iVar43 = iVar41 + 2;
                      iVar41 = iVar41 + uVar36 * 2;
                      fVar24 = (float)NEON_ucvtf((uint)puVar8[-2]);
                      fVar91 = (fVar24 - fVar82) / fVar87;
                      fVar24 = (float)NEON_ucvtf((uint)*(ushort *)(lVar55 + (long)iVar51 * 2));
                      fVar25 = (fVar25 - fVar82) / fVar87;
                      fVar89 = (float)NEON_fmadd((fVar23 - fVar82) / fVar87,fVar83,fVar80 * fVar91);
                      fVar90 = (fVar90 - fVar82) / fVar87;
                      fVar92 = (float)NEON_fmadd(fVar91,fVar83,fVar80 * fVar25);
                      fVar91 = (float)NEON_ucvtf((uint)*(ushort *)(lVar55 + (long)iVar43 * 2));
                      fVar23 = (fVar69 - fVar82) / fVar87;
                      uVar77 = NEON_fmadd(fVar90,fVar83,fVar80 * fVar23);
                      fVar69 = (float)NEON_fmadd(uVar77,fVar74,fVar76 * fVar92);
                      uVar77 = NEON_fmadd((fVar22 - fVar82) / fVar87,fVar83,fVar80 * fVar90);
                      fVar22 = (float)NEON_fmadd(uVar77,fVar74,fVar76 * fVar89);
                      fVar90 = (float)NEON_fmadd(fVar25,fVar83,fVar80 * ((fVar27 - fVar82) / fVar87)
                                                );
                      uVar77 = NEON_fmadd(fVar23,fVar83,fVar80 * ((fVar26 - fVar82) / fVar87));
                      fVar90 = (float)NEON_fmadd(uVar77,fVar74,fVar76 * fVar90);
                      fVar79 = fVar79 + (fVar84 * fVar22 - (fVar24 - fVar72) / fVar86) +
                               (fVar84 * fVar69 - (fVar85 - fVar72) / fVar86) +
                               (fVar84 * fVar90 - (fVar91 - fVar72) / fVar86);
                    } while (lVar32 < 1);
                    if (fVar75 < 0.995) {
                      if (fVar73 <= 1e-09) {
                        fVar73 = 1e-09;
                      }
                      fVar76 = ((fVar79 / 9.0) * (fVar79 / 9.0)) / (fVar73 / 9.0 + 1e-06);
                      if (((fVar76 <= 9.0) &&
                          (fVar72 = ((fVar75 - fVar78) * (fVar75 - fVar78)) / (fVar73 + 4e-06),
                          fVar72 <= 16.0)) && (fVar78 < 0.995)) {
                        fVar72 = fVar72 * -0.0625 + 1.0;
                        fVar76 = fVar76 / -9.0 + 1.0;
                        if (fVar76 <= 0.0) {
                          fVar76 = 0.0;
                        }
                        if (fVar72 <= 0.0) {
                          fVar72 = 0.0;
                        }
                        fVar72 = fVar72 * fVar76;
                        uVar77 = NEON_fmadd(fVar75,fVar72,
                                            *(undefined4 *)((long)local_c0 + lVar53 * 4));
                        *(undefined4 *)((long)local_c0 + lVar53 * 4) = uVar77;
                        local_1a0 = local_1a0 + (double)fVar72;
                        puVar31[lVar53] = fVar72 + (float)puVar31[lVar53];
                      }
                    }
                  }
                  uVar35 = uVar35 + 1;
                  iVar4 = iVar4 + 1;
                } while (uVar35 != uVar36 - 4);
              }
              uVar65 = uVar65 + 1;
              iVar64 = iVar64 + uVar36;
            } while (uVar65 != param_3 - 4);
          }
        }
        if (dVar28 < local_1a0 / (double)(unkuint9)uVar68) {
          *piVar39 = *piVar39 + 1;
        }
        if (local_108 != (void *)0x0) {
          operator_delete(local_108);
        }
        if (local_f0 != (void *)0x0) {
          operator_delete(local_f0);
        }
        local_228 = local_228 + local_1a0;
        lVar53 = *(long *)this;
        lVar55 = *(long *)(this + 8);
      }
      uVar52 = uVar52 + 1;
      uVar65 = lVar55 - lVar53 >> 3;
    } while (uVar52 < uVar65);
  }
  uVar65 = uVar65 - 1;
  in_x8[1] = (void *)0x0;
  in_x8[2] = (void *)0x0;
  *in_x8 = (void *)0x0;
  if (uVar65 < 2) {
    uVar65 = 1;
  }
  *(double *)(piVar39 + 2) = local_228 / (double)(unkuint9)(uVar65 * uVar68);
  if (uVar68 == 0) {
    pvVar60 = (void *)0x0;
  }
  else {
    if ((long)uVar68 < 0) {
LAB_00115cbc:
                    /* try { // try from 00115cbc to 00115cc3 has its CatchHandler @ 00115cd8 */
      uVar81 = std::__ndk1::vector<unsigned_short,std::__ndk1::allocator<unsigned_short>>::
               __throw_length_error_abi_ne180000_();
                    /* catch() { ... } // from try @ 001149ec with catch @ 00115cc4 */
      if (local_c0 != (void *)0x0) {
        operator_delete(local_c0);
      }
                    /* WARNING: Subroutine does not return */
      _Unwind_Resume(uVar81);
    }
    uVar65 = uVar68 * 2;
                    /* try { // try from 00115ae4 to 00115aeb has its CatchHandler @ 00115cd8 */
    pvVar60 = operator_new(uVar65);
    *in_x8 = pvVar60;
    in_x8[2] = (void *)((long)pvVar60 + uVar68 * 2);
    memset(pvVar60,0,uVar65);
    in_x8[1] = (void *)((long)pvVar60 + uVar65);
  }
  if (0 < param_3) {
    uVar65 = 0;
    uVar68 = 0;
    do {
      if (0 < (int)uVar36) {
        fVar71 = *pfVar14;
        uVar46 = 0;
        do {
          fVar84 = (float)NEON_fmadd(*(float *)((long)local_c0 + uVar46 * 4 + uVar65 * 4) /
                                     (float)puVar31[uVar65 + uVar46],
                                     fVar71 - pfVar14[((uVar68 & 1) << 1 | 1) + (uVar46 & 1)],
                                     pfVar14[((uVar68 & 1) << 1 | 1) + (uVar46 & 1)]);
          fVar84 = (float)NEON_fminnm(fVar84 + 0.5,0x477fff00);
          if (fVar84 <= 0.0) {
            fVar84 = 0.0;
          }
          *(short *)((long)pvVar60 + uVar46 * 2 + uVar65 * 2) = (short)(int)fVar84;
          uVar46 = uVar46 + 1;
        } while (((ulong)param_2 & 0xffffffff) != uVar46);
      }
      uVar68 = uVar68 + 1;
      uVar65 = (ulong)((int)uVar65 + uVar36);
    } while (uVar68 != uVar50);
  }
  if (local_d8 != (void *)0x0) {
    operator_delete(local_d8);
  }
  if (puVar31 != (undefined4 *)0x0) {
    operator_delete(puVar31);
  }
  if (local_c0 != (void *)0x0) {
    operator_delete(local_c0);
  }
  return;
}



/* 00115d9c ~vector[abi:ne180000] */

/* std::__ndk1::vector<std::__ndk1::vector<unsigned short, std::__ndk1::allocator<unsigned short> >,
   std::__ndk1::allocator<std::__ndk1::vector<unsigned short, std::__ndk1::allocator<unsigned short>
   > > >::~vector[abi:ne180000]() */

void __thiscall
std::__ndk1::
vector<std::__ndk1::vector<unsigned_short,std::__ndk1::allocator<unsigned_short>>,std::__ndk1::allocator<std::__ndk1::vector<unsigned_short,std::__ndk1::allocator<unsigned_short>>>>
::~vector_abi_ne180000_
          (vector<std::__ndk1::vector<unsigned_short,std::__ndk1::allocator<unsigned_short>>,std::__ndk1::allocator<std::__ndk1::vector<unsigned_short,std::__ndk1::allocator<unsigned_short>>>>
           *this)

{
  void *pvVar1;
  void **ppvVar2;
  void **ppvVar3;
  void **ppvVar4;
  
  ppvVar4 = *(void ***)this;
  if (ppvVar4 == (void **)0x0) {
    return;
  }
  ppvVar3 = *(void ***)(this + 8);
  ppvVar2 = ppvVar4;
  if (ppvVar3 != ppvVar4) {
    do {
      ppvVar2 = ppvVar3 + -3;
      pvVar1 = *ppvVar2;
      if (pvVar1 != (void *)0x0) {
        ppvVar3[-2] = pvVar1;
        operator_delete(pvVar1);
      }
      ppvVar3 = ppvVar2;
    } while (ppvVar2 != ppvVar4);
    ppvVar2 = *(void ***)this;
  }
  *(void ***)(this + 8) = ppvVar4;
  operator_delete(ppvVar2);
  return;
}



/* 00115e18 basic_ifstream */

/* std::__ndk1::basic_ifstream<char, std::__ndk1::char_traits<char> >::basic_ifstream(char const*,
   unsigned int) */

void std::__ndk1::basic_ifstream<char,std::__ndk1::char_traits<char>>::basic_ifstream
               (char *param_1,uint param_2)

{
  undefined *puVar1;
  char *pcVar2;
  undefined8 uVar3;
  undefined *puVar4;
  long lVar5;
  
  puVar4 = PTR_vtable_00120de0;
  lVar5 = *(long *)(PTR_VTT_00120dc0 + 8);
  uVar3 = *(undefined8 *)(PTR_VTT_00120dc0 + 0x10);
  puVar1 = PTR_vtable_00120de0 + 0x40;
  *(undefined **)(param_1 + 0xb8) = puVar1;
  *(long *)param_1 = lVar5;
  lVar5 = *(long *)(lVar5 + -0x18);
  *(undefined8 *)(param_1 + 8) = 0;
  *(undefined8 *)(param_1 + lVar5) = uVar3;
  pcVar2 = param_1 + *(long *)(*(long *)param_1 + -0x18);
                    /* try { // try from 00115e78 to 00115e83 has its CatchHandler @ 00115ef0 */
  std::__ndk1::ios_base::init(pcVar2);
  *(undefined8 *)(pcVar2 + 0x88) = 0;
  *(undefined4 *)(pcVar2 + 0x90) = 0xffffffff;
  *(undefined **)param_1 = puVar4 + 0x18;
  *(undefined **)(param_1 + 0xb8) = puVar1;
                    /* try { // try from 00115e9c to 00115ea3 has its CatchHandler @ 00115ee8 */
  std::__ndk1::basic_filebuf<char,std::__ndk1::char_traits<char>>::basic_filebuf();
                    /* try { // try from 00115ea4 to 00115ecf has its CatchHandler @ 00115ef8 */
  lVar5 = std::__ndk1::basic_filebuf<char,std::__ndk1::char_traits<char>>::open
                    (param_1 + 0x10,param_2);
  if (lVar5 == 0) {
    std::__ndk1::ios_base::clear((int)param_1 + (int)*(undefined8 *)(*(long *)param_1 + -0x18));
  }
  return;
}



/* 00115f20 ~basic_ifstream */

/* std::__ndk1::basic_ifstream<char, std::__ndk1::char_traits<char> >::~basic_ifstream() */

void __thiscall
std::__ndk1::basic_ifstream<char,std::__ndk1::char_traits<char>>::~basic_ifstream
          (basic_ifstream<char,std::__ndk1::char_traits<char>> *this)

{
  long lVar1;
  undefined8 uVar2;
  
  lVar1 = *(long *)PTR_VTT_00120dc0;
  uVar2 = *(undefined8 *)(PTR_VTT_00120dc0 + 0x18);
  *(long *)this = lVar1;
  *(undefined8 *)(this + *(long *)(lVar1 + -0x18)) = uVar2;
  std::__ndk1::basic_filebuf<char,std::__ndk1::char_traits<char>>::~basic_filebuf
            ((basic_filebuf<char,std::__ndk1::char_traits<char>> *)(this + 0x10));
  std::__ndk1::basic_istream<char,std::__ndk1::char_traits<char>>::~basic_istream
            ((basic_istream<char,std::__ndk1::char_traits<char>> *)this);
  std::__ndk1::basic_ios<char,std::__ndk1::char_traits<char>>::~basic_ios
            ((basic_ios<char,std::__ndk1::char_traits<char>> *)(this + 0xb8));
  return;
}



/* 00115f70 __init_with_sentinel[abi:ne180000]<std::__ndk1::istreambuf_iterator<char,std::__ndk1::char_traits<char>>,std::__ndk1::istreambuf_iterator<char,std::__ndk1::char_traits<char>>> */

/* void std::__ndk1::vector<unsigned char, std::__ndk1::allocator<unsigned char>
   >::__init_with_sentinel[abi:ne180000]<std::__ndk1::istreambuf_iterator<char,
   std::__ndk1::char_traits<char> >, std::__ndk1::istreambuf_iterator<char,
   std::__ndk1::char_traits<char> > >(std::__ndk1::istreambuf_iterator<char,
   std::__ndk1::char_traits<char> >, std::__ndk1::istreambuf_iterator<char,
   std::__ndk1::char_traits<char> >) */

void __thiscall
std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>::
__init_with_sentinel_abi_ne180000_<std::__ndk1::istreambuf_iterator<char,std::__ndk1::char_traits<char>>,std::__ndk1::istreambuf_iterator<char,std::__ndk1::char_traits<char>>>
          (vector<unsigned_char,std::__ndk1::allocator<unsigned_char>> *this,
          istreambuf_iterator param_1,istreambuf_iterator param_2)

{
  long lVar1;
  undefined8 *puVar2;
  long *plVar3;
  bool bVar4;
  undefined uVar5;
  int iVar6;
  undefined *puVar7;
  long *plVar8;
  ulong uVar9;
  undefined *puVar10;
  long lVar11;
  ulong uVar12;
  undefined8 *puVar13;
  ulong uVar14;
  undefined8 *puVar15;
  long *plVar16;
  undefined *puVar17;
  undefined *puVar18;
  ulong uVar19;
  undefined *puVar20;
  undefined8 uVar21;
  undefined8 uVar22;
  undefined8 uVar23;
  
  plVar16 = (long *)(ulong)param_2;
  plVar8 = (long *)(ulong)param_1;
  do {
    if (plVar8 == (long *)0x0) {
      bVar4 = true;
      plVar3 = plVar8;
joined_r0x00115fc8:
      plVar8 = plVar3;
      if (plVar16 == (long *)0x0) goto LAB_0011601c;
LAB_00115ff0:
      if ((plVar16[3] == plVar16[4]) &&
         (iVar6 = (**(code **)(*plVar16 + 0x48))(plVar16), iVar6 == -1)) goto LAB_0011601c;
      if (!bVar4) {
        return;
      }
    }
    else {
      if (plVar8[3] == plVar8[4]) {
                    /* try { // try from 00115fd8 to 0011600b has its CatchHandler @ 001161e4 */
        iVar6 = (**(code **)(*plVar8 + 0x48))(plVar8);
        bVar4 = iVar6 == -1;
        plVar3 = (long *)0x0;
        if (!bVar4) {
          plVar3 = plVar8;
        }
        goto joined_r0x00115fc8;
      }
      bVar4 = false;
      if (plVar16 != (long *)0x0) goto LAB_00115ff0;
LAB_0011601c:
      if (bVar4) {
        return;
      }
      plVar16 = (long *)0x0;
    }
    if ((undefined *)plVar8[3] == (undefined *)plVar8[4]) {
                    /* try { // try from 00116040 to 0011609b has its CatchHandler @ 001161e0 */
      uVar5 = (**(code **)(*plVar8 + 0x48))(plVar8);
    }
    else {
      uVar5 = *(undefined *)plVar8[3];
    }
    puVar18 = *(undefined **)(this + 8);
    if (puVar18 < *(undefined **)(this + 0x10)) {
      puVar17 = puVar18 + 1;
      *puVar18 = uVar5;
    }
    else {
      puVar20 = *(undefined **)this;
      uVar19 = (long)puVar18 - (long)puVar20;
      uVar14 = uVar19 + 1;
      if ((long)uVar14 < 0) {
                    /* try { // try from 001161d4 to 001161db has its CatchHandler @ 001161dc */
                    /* WARNING: Subroutine does not return */
        __throw_length_error_abi_ne180000_();
      }
      uVar9 = (long)*(undefined **)(this + 0x10) - (long)puVar20;
      uVar12 = uVar9 * 2;
      if (uVar12 < uVar14 || uVar12 - uVar14 == 0) {
        uVar12 = uVar14;
      }
      if (0x3ffffffffffffffe < uVar9) {
        uVar12 = 0x7fffffffffffffff;
      }
      if (uVar12 == 0) {
        puVar7 = (undefined *)0x0;
      }
      else {
        puVar7 = (undefined *)operator_new(uVar12);
      }
      puVar10 = puVar7 + uVar19;
      puVar17 = puVar10 + 1;
      *puVar10 = uVar5;
      if (puVar18 != puVar20) {
        if ((uVar19 < 8) || ((ulong)((long)puVar20 - (long)puVar7) < 0x20)) {
LAB_00116164:
          do {
            puVar10 = puVar10 + -1;
            puVar18 = puVar18 + -1;
            *puVar10 = *puVar18;
          } while (puVar18 != puVar20);
        }
        else if (uVar19 < 0x20) {
          uVar9 = 0;
LAB_00116118:
          puVar15 = (undefined8 *)(puVar18 + -uVar9);
          uVar14 = uVar19 & 0xfffffffffffffff8;
          puVar18 = puVar18 + -uVar14;
          puVar10 = puVar10 + -uVar14;
          puVar13 = (undefined8 *)(puVar7 + ((long)puVar15 - (long)puVar20));
          lVar11 = uVar9 - uVar14;
          do {
            puVar15 = puVar15 + -1;
            puVar13 = puVar13 + -1;
            lVar11 = lVar11 + 8;
            *puVar13 = *puVar15;
          } while (lVar11 != 0);
          if (uVar19 != uVar14) goto LAB_00116164;
        }
        else {
          uVar9 = uVar19 & 0xffffffffffffffe0;
          puVar15 = (undefined8 *)(puVar18 + -0x10);
          puVar13 = (undefined8 *)(puVar7 + (uVar19 - 0x10));
          uVar14 = uVar9;
          do {
            puVar2 = puVar15 + -1;
            uVar23 = puVar15[-2];
            uVar22 = puVar15[1];
            uVar21 = *puVar15;
            uVar14 = uVar14 - 0x20;
            puVar15 = puVar15 + -4;
            puVar13[-1] = *puVar2;
            puVar13[-2] = uVar23;
            puVar13[1] = uVar22;
            *puVar13 = uVar21;
            puVar13 = puVar13 + -4;
          } while (uVar14 != 0);
          if (uVar19 != uVar9) {
            if ((uVar19 & 0x18) == 0) {
              puVar10 = puVar10 + -uVar9;
              puVar18 = puVar18 + -uVar9;
              goto LAB_00116164;
            }
            goto LAB_00116118;
          }
        }
        puVar18 = *(undefined **)this;
        puVar10 = puVar7;
      }
      *(undefined **)this = puVar10;
      *(undefined **)(this + 8) = puVar17;
      *(undefined **)(this + 0x10) = puVar7 + uVar12;
      if (puVar18 != (undefined *)0x0) {
        operator_delete(puVar18);
      }
    }
    lVar11 = plVar8[3];
    lVar1 = plVar8[4];
    *(undefined **)(this + 8) = puVar17;
    if (lVar11 == lVar1) {
                    /* try { // try from 001161ac to 001161b3 has its CatchHandler @ 001161e4 */
      (**(code **)(*plVar8 + 0x50))(plVar8);
    }
    else {
      plVar8[3] = lVar11 + 1;
    }
  } while( true );
}



/* 00116200 __throw_length_error[abi:ne180000] */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* std::__ndk1::vector<unsigned char, std::__ndk1::allocator<unsigned char>
   >::__throw_length_error[abi:ne180000]() const */

void std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>::
     __throw_length_error_abi_ne180000_(void)

{
                    /* WARNING: Subroutine does not return */
  __ndk1::__throw_length_error_abi_ne180000_("vector");
}



/* 00116214 __throw_length_error[abi:ne180000] */

/* std::__ndk1::__throw_length_error[abi:ne180000](char const*) */

void std::__ndk1::__throw_length_error_abi_ne180000_(char *param_1)

{
  length_error *this;
  
  this = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00116230 to 00116237 has its CatchHandler @ 00116250 */
  length_error::length_error_abi_ne180000_(this,param_1);
                    /* WARNING: Subroutine does not return */
  __cxa_throw(this,PTR_typeinfo_00120de8,PTR__length_error_00120df0);
}



/* 00116264 length_error[abi:ne180000] */

/* std::length_error::length_error[abi:ne180000](char const*) */

void __thiscall std::length_error::length_error_abi_ne180000_(length_error *this,char *param_1)

{
  std::logic_error::logic_error((logic_error *)this,param_1);
  *(undefined **)this = PTR_vtable_00120df8 + 0x10;
  return;
}



/* 00116294 __throw_bad_array_new_length[abi:ne180000] */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* std::__throw_bad_array_new_length[abi:ne180000]() */

void std::__throw_bad_array_new_length_abi_ne180000_(void)

{
  bad_array_new_length *this;
  
  this = (bad_array_new_length *)__cxa_allocate_exception(8);
  std::bad_array_new_length::bad_array_new_length(this);
                    /* WARNING: Subroutine does not return */
  __cxa_throw(this,PTR_typeinfo_00120e00,PTR__bad_array_new_length_00120e08);
}



/* 001162c8 resize */

/* std::__ndk1::vector<unsigned char, std::__ndk1::allocator<unsigned char> >::resize(unsigned long)
    */

void __thiscall
std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>::resize
          (vector<unsigned_char,std::__ndk1::allocator<unsigned_char>> *this,ulong param_1)

{
  ulong uVar1;
  
  uVar1 = *(long *)(this + 8) - *(long *)this;
  if (param_1 >= uVar1 && param_1 - uVar1 != 0) {
    __append(this,param_1 - uVar1);
    return;
  }
  if (param_1 < uVar1) {
    *(ulong *)(this + 8) = *(long *)this + param_1;
  }
  return;
}



/* 001162f0 __append */

/* std::__ndk1::vector<unsigned char, std::__ndk1::allocator<unsigned char> >::__append(unsigned
   long) */

void __thiscall
std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>::__append
          (vector<unsigned_char,std::__ndk1::allocator<unsigned_char>> *this,ulong param_1)

{
  undefined *puVar1;
  undefined8 *puVar2;
  undefined *puVar3;
  ulong uVar4;
  long lVar5;
  undefined8 *puVar6;
  ulong uVar7;
  ulong uVar8;
  undefined8 *puVar9;
  undefined *__s;
  undefined *__s_00;
  undefined *puVar10;
  ulong uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  
  __s = *(undefined **)(this + 8);
  if (param_1 <= (ulong)(*(long *)(this + 0x10) - (long)__s)) {
    puVar10 = __s;
    if (param_1 != 0) {
      puVar10 = __s + param_1;
      memset(__s,0,param_1);
    }
    *(undefined **)(this + 8) = puVar10;
    return;
  }
  puVar10 = *(undefined **)this;
  uVar11 = (long)__s - (long)puVar10;
  uVar7 = uVar11 + param_1;
  if ((long)uVar7 < 0) {
                    /* WARNING: Subroutine does not return */
    __throw_length_error_abi_ne180000_();
  }
  uVar4 = *(long *)(this + 0x10) - (long)puVar10;
  uVar8 = uVar4 * 2;
  if (uVar8 < uVar7 || uVar8 - uVar7 == 0) {
    uVar8 = uVar7;
  }
  if (0x3ffffffffffffffe < uVar4) {
    uVar8 = 0x7fffffffffffffff;
  }
  if (uVar8 == 0) {
    puVar3 = (undefined *)0x0;
  }
  else {
    puVar3 = (undefined *)operator_new(uVar8);
  }
  __s_00 = puVar3 + uVar11;
  puVar1 = __s_00 + param_1;
  memset(__s_00,0,param_1);
  if (__s == puVar10) goto LAB_0011647c;
  if ((uVar11 < 8) || ((ulong)((long)puVar10 - (long)puVar3) < 0x20)) {
LAB_00116468:
    do {
      __s_00 = __s_00 + -1;
      __s = __s + -1;
      *__s_00 = *__s;
    } while (__s != puVar10);
  }
  else if (uVar11 < 0x20) {
    uVar4 = 0;
LAB_00116420:
    uVar7 = uVar11 & 0xfffffffffffffff8;
    puVar9 = (undefined8 *)(__s + (-8 - uVar4));
    __s = __s + -uVar7;
    __s_00 = __s_00 + -uVar7;
    lVar5 = uVar4 - uVar7;
    puVar6 = (undefined8 *)(puVar3 + ((long)puVar9 - (long)puVar10));
    do {
      lVar5 = lVar5 + 8;
      *puVar6 = *puVar9;
      puVar9 = puVar9 + -1;
      puVar6 = puVar6 + -1;
    } while (lVar5 != 0);
    if (uVar11 != uVar7) goto LAB_00116468;
  }
  else {
    puVar6 = (undefined8 *)(__s + -0x10);
    uVar4 = uVar11 & 0xffffffffffffffe0;
    puVar9 = (undefined8 *)(puVar3 + ((long)puVar6 - (long)puVar10));
    uVar7 = uVar4;
    do {
      puVar2 = puVar6 + -1;
      uVar14 = puVar6[-2];
      uVar13 = puVar6[1];
      uVar12 = *puVar6;
      uVar7 = uVar7 - 0x20;
      puVar6 = puVar6 + -4;
      puVar9[-1] = *puVar2;
      puVar9[-2] = uVar14;
      puVar9[1] = uVar13;
      *puVar9 = uVar12;
      puVar9 = puVar9 + -4;
    } while (uVar7 != 0);
    if (uVar11 != uVar4) {
      if ((uVar11 & 0x18) == 0) {
        __s_00 = __s_00 + -uVar4;
        __s = __s + -uVar4;
        goto LAB_00116468;
      }
      goto LAB_00116420;
    }
  }
  __s = *(undefined **)this;
  __s_00 = puVar3;
LAB_0011647c:
  *(undefined **)this = __s_00;
  *(undefined **)(this + 8) = puVar1;
  *(undefined **)(this + 0x10) = puVar3 + uVar8;
  if (__s == (undefined *)0x0) {
    return;
  }
  operator_delete(__s);
  return;
}



/* 001164cc _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2B8ne180000ILi0EEEPKc */

void _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2B8ne180000ILi0EEEPKc
               (long *param_1,char *param_2)

{
  undefined *puVar1;
  undefined8 uVar2;
  undefined *puVar3;
  size_t __n;
  long *plVar4;
  long lVar5;
  uint uVar6;
  void *pvVar7;
  undefined auVar8 [16];
  
  __n = strlen(param_2);
  if (0xffffffffffffffef < __n) {
    auVar8 = std::__ndk1::
             basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>::
             __throw_length_error_abi_ne180000_();
    puVar3 = PTR_vtable_00120e10;
    plVar4 = auVar8._0_8_;
    lVar5 = *(long *)(PTR_VTT_00120dc8 + 8);
    uVar2 = *(undefined8 *)(PTR_VTT_00120dc8 + 0x10);
    puVar1 = PTR_vtable_00120e10 + 0x40;
    plVar4[0x16] = (long)puVar1;
    *plVar4 = lVar5;
    *(undefined8 *)((long)plVar4 + *(long *)(lVar5 + -0x18)) = uVar2;
    pvVar7 = (void *)((long)plVar4 + *(long *)(*plVar4 + -0x18));
    std::__ndk1::ios_base::init(pvVar7);
    *(undefined8 *)((long)pvVar7 + 0x88) = 0;
    *(undefined4 *)((long)pvVar7 + 0x90) = 0xffffffff;
    *plVar4 = (long)(puVar3 + 0x18);
    plVar4[0x16] = (long)puVar1;
    std::__ndk1::basic_filebuf<char,std::__ndk1::char_traits<char>>::basic_filebuf();
    uVar6 = (uint)*(undefined8 *)(auVar8._8_8_ + 0x10);
    if ((*auVar8._8_8_ & 1) == 0) {
      uVar6 = auVar8._8_4_ + 1;
    }
    lVar5 = std::__ndk1::basic_filebuf<char,std::__ndk1::char_traits<char>>::open
                      ((char *)(plVar4 + 1),uVar6);
    if (lVar5 == 0) {
      std::__ndk1::ios_base::clear(auVar8._0_4_ + (int)*(undefined8 *)(*plVar4 + -0x18));
    }
    return;
  }
  if (__n < 0x17) {
    pvVar7 = (void *)((long)param_1 + 1);
    *(char *)param_1 = (char)((int)__n << 1);
    if (__n == 0) goto LAB_0011653c;
  }
  else {
    pvVar7 = operator_new((__n | 0xf) + 1);
    param_1[1] = __n;
    param_1[2] = (long)pvVar7;
    *param_1 = (__n | 0xf) + 2;
  }
  memmove(pvVar7,param_2,__n);
LAB_0011653c:
  *(undefined *)((long)pvVar7 + __n) = 0;
  return;
}



/* 00116558 basic_ofstream */

/* std::__ndk1::basic_ofstream<char, std::__ndk1::char_traits<char>
   >::basic_ofstream(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>,
   std::__ndk1::allocator<char> > const&, unsigned int) */

void std::__ndk1::basic_ofstream<char,std::__ndk1::char_traits<char>>::basic_ofstream
               (basic_string *param_1,uint param_2)

{
  undefined *puVar1;
  basic_string *pbVar2;
  undefined8 uVar3;
  undefined *puVar4;
  long lVar5;
  uint uVar6;
  
  puVar4 = PTR_vtable_00120e10;
  lVar5 = *(long *)(PTR_VTT_00120dc8 + 8);
  uVar3 = *(undefined8 *)(PTR_VTT_00120dc8 + 0x10);
  puVar1 = PTR_vtable_00120e10 + 0x40;
  *(undefined **)(param_1 + 0xb0) = puVar1;
  *(long *)param_1 = lVar5;
  *(undefined8 *)(param_1 + *(long *)(lVar5 + -0x18)) = uVar3;
  pbVar2 = param_1 + *(long *)(*(long *)param_1 + -0x18);
                    /* try { // try from 001165b4 to 001165bf has its CatchHandler @ 00116638 */
  std::__ndk1::ios_base::init(pbVar2);
  *(undefined8 *)(pbVar2 + 0x88) = 0;
  *(undefined4 *)(pbVar2 + 0x90) = 0xffffffff;
  *(undefined **)param_1 = puVar4 + 0x18;
  *(undefined **)(param_1 + 0xb0) = puVar1;
                    /* try { // try from 001165d8 to 001165df has its CatchHandler @ 00116630 */
  std::__ndk1::basic_filebuf<char,std::__ndk1::char_traits<char>>::basic_filebuf();
  uVar6 = (uint)*(undefined8 *)((byte *)(ulong)param_2 + 0x10);
  if ((*(byte *)(ulong)param_2 & 1) == 0) {
    uVar6 = param_2 + 1;
  }
                    /* try { // try from 001165f0 to 00116617 has its CatchHandler @ 00116640 */
  lVar5 = std::__ndk1::basic_filebuf<char,std::__ndk1::char_traits<char>>::open
                    ((char *)(param_1 + 8),uVar6);
  if (lVar5 == 0) {
    std::__ndk1::ios_base::clear((int)param_1 + (int)*(undefined8 *)(*(long *)param_1 + -0x18));
  }
  return;
}



/* 00116668 ~basic_ofstream */

/* std::__ndk1::basic_ofstream<char, std::__ndk1::char_traits<char> >::~basic_ofstream() */

void __thiscall
std::__ndk1::basic_ofstream<char,std::__ndk1::char_traits<char>>::~basic_ofstream
          (basic_ofstream<char,std::__ndk1::char_traits<char>> *this)

{
  long lVar1;
  undefined8 uVar2;
  
  lVar1 = *(long *)PTR_VTT_00120dc8;
  uVar2 = *(undefined8 *)(PTR_VTT_00120dc8 + 0x18);
  *(long *)this = lVar1;
  *(undefined8 *)(this + *(long *)(lVar1 + -0x18)) = uVar2;
  std::__ndk1::basic_filebuf<char,std::__ndk1::char_traits<char>>::~basic_filebuf
            ((basic_filebuf<char,std::__ndk1::char_traits<char>> *)(this + 8));
  std::__ndk1::basic_ostream<char,std::__ndk1::char_traits<char>>::~basic_ostream
            ((basic_ostream<char,std::__ndk1::char_traits<char>> *)this);
  std::__ndk1::basic_ios<char,std::__ndk1::char_traits<char>>::~basic_ios
            ((basic_ios<char,std::__ndk1::char_traits<char>> *)(this + 0xb0));
  return;
}



/* 001166b8 operator+[abi:ne180000]<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>> */

/* std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >
   std::__ndk1::operator+[abi:ne180000]<char, std::__ndk1::char_traits<char>,
   std::__ndk1::allocator<char> >(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>,
   std::__ndk1::allocator<char> > const&, char const*) */

void __thiscall
std::__ndk1::
operator+[abi_ne180000_<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>
          (long *param_1_00,__ndk1 *this,char *param_1)

{
  undefined *puVar1;
  ulong uVar2;
  size_t __n;
  undefined8 uVar3;
  __ndk1 _Var4;
  undefined *puVar5;
  size_t __n_00;
  void *pvVar6;
  long *plVar7;
  uint uVar8;
  __ndk1 *__src;
  long lVar9;
  undefined auVar10 [16];
  
  _Var4 = *this;
  __n = (ulong)((byte)_Var4 >> 1);
  if (((byte)_Var4 & 1) != 0) {
    __n = *(size_t *)(this + 8);
  }
  __n_00 = strlen(param_1);
  uVar2 = __n + __n_00;
  if (uVar2 < 0xfffffffffffffff0) {
    if (uVar2 < 0x17) {
      pvVar6 = (void *)0x0;
      *param_1_00 = 0;
      param_1_00[1] = 0;
      uVar8 = ((uint)uVar2 & 0xff) << 1;
      param_1_00[2] = 0;
      *(char *)param_1_00 = (char)uVar8;
    }
    else {
      pvVar6 = operator_new((uVar2 | 0xf) + 1);
      lVar9 = (uVar2 | 0xf) + 2;
      param_1_00[1] = uVar2;
      param_1_00[2] = (long)pvVar6;
      *param_1_00 = lVar9;
      uVar8 = (uint)lVar9 & 0xff;
    }
    if ((uVar8 & 1) == 0) {
      pvVar6 = (void *)((long)param_1_00 + 1);
    }
    if (__n != 0) {
      __src = *(__ndk1 **)(this + 0x10);
      if (((byte)_Var4 & 1) == 0) {
        __src = this + 1;
      }
      memmove(pvVar6,__src,__n);
    }
    if (__n_00 != 0) {
      memmove((void *)((long)pvVar6 + __n),param_1,__n_00);
    }
    *(undefined *)((long)(void *)((long)pvVar6 + __n) + __n_00) = 0;
    return;
  }
  auVar10 = basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>::
            __throw_length_error_abi_ne180000_();
  puVar5 = PTR_vtable_00120de0;
  plVar7 = auVar10._0_8_;
  lVar9 = *(long *)(PTR_VTT_00120dc0 + 8);
  uVar3 = *(undefined8 *)(PTR_VTT_00120dc0 + 0x10);
  puVar1 = PTR_vtable_00120de0 + 0x40;
  plVar7[0x17] = (long)puVar1;
  *plVar7 = lVar9;
  lVar9 = *(long *)(lVar9 + -0x18);
  plVar7[1] = 0;
  *(undefined8 *)((long)plVar7 + lVar9) = uVar3;
  pvVar6 = (void *)((long)plVar7 + *(long *)(*plVar7 + -0x18));
  std::__ndk1::ios_base::init(pvVar6);
  *(undefined8 *)((long)pvVar6 + 0x88) = 0;
  *(undefined4 *)((long)pvVar6 + 0x90) = 0xffffffff;
  *plVar7 = (long)(puVar5 + 0x18);
  plVar7[0x17] = (long)puVar1;
  std::__ndk1::basic_filebuf<char,std::__ndk1::char_traits<char>>::basic_filebuf();
  uVar8 = (uint)*(undefined8 *)(auVar10._8_8_ + 0x10);
  if ((*auVar10._8_8_ & 1) == 0) {
    uVar8 = auVar10._8_4_ + 1;
  }
  lVar9 = std::__ndk1::basic_filebuf<char,std::__ndk1::char_traits<char>>::open
                    ((char *)(plVar7 + 2),uVar8);
  if (lVar9 == 0) {
    std::__ndk1::ios_base::clear(auVar10._0_4_ + (int)*(undefined8 *)(*plVar7 + -0x18));
  }
  return;
}



/* 001167a8 basic_ifstream */

/* std::__ndk1::basic_ifstream<char, std::__ndk1::char_traits<char>
   >::basic_ifstream(std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>,
   std::__ndk1::allocator<char> > const&, unsigned int) */

void std::__ndk1::basic_ifstream<char,std::__ndk1::char_traits<char>>::basic_ifstream
               (basic_string *param_1,uint param_2)

{
  undefined *puVar1;
  basic_string *pbVar2;
  undefined8 uVar3;
  undefined *puVar4;
  long lVar5;
  uint uVar6;
  
  puVar4 = PTR_vtable_00120de0;
  lVar5 = *(long *)(PTR_VTT_00120dc0 + 8);
  uVar3 = *(undefined8 *)(PTR_VTT_00120dc0 + 0x10);
  puVar1 = PTR_vtable_00120de0 + 0x40;
  *(undefined **)(param_1 + 0xb8) = puVar1;
  *(long *)param_1 = lVar5;
  lVar5 = *(long *)(lVar5 + -0x18);
  *(undefined8 *)(param_1 + 8) = 0;
  *(undefined8 *)(param_1 + lVar5) = uVar3;
  pbVar2 = param_1 + *(long *)(*(long *)param_1 + -0x18);
                    /* try { // try from 00116808 to 00116813 has its CatchHandler @ 0011688c */
  std::__ndk1::ios_base::init(pbVar2);
  *(undefined8 *)(pbVar2 + 0x88) = 0;
  *(undefined4 *)(pbVar2 + 0x90) = 0xffffffff;
  *(undefined **)param_1 = puVar4 + 0x18;
  *(undefined **)(param_1 + 0xb8) = puVar1;
                    /* try { // try from 0011682c to 00116833 has its CatchHandler @ 00116884 */
  std::__ndk1::basic_filebuf<char,std::__ndk1::char_traits<char>>::basic_filebuf();
  uVar6 = (uint)*(undefined8 *)((byte *)(ulong)param_2 + 0x10);
  if ((*(byte *)(ulong)param_2 & 1) == 0) {
    uVar6 = param_2 + 1;
  }
                    /* try { // try from 00116844 to 0011686b has its CatchHandler @ 00116894 */
  lVar5 = std::__ndk1::basic_filebuf<char,std::__ndk1::char_traits<char>>::open
                    ((char *)(param_1 + 0x10),uVar6);
  if (lVar5 == 0) {
    std::__ndk1::ios_base::clear((int)param_1 + (int)*(undefined8 *)(*(long *)param_1 + -0x18));
  }
  return;
}



/* 001168bc __throw_length_error[abi:ne180000] */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char>
   >::__throw_length_error[abi:ne180000]() const */

void std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>::
     __throw_length_error_abi_ne180000_(void)

{
                    /* WARNING: Subroutine does not return */
  __ndk1::__throw_length_error_abi_ne180000_("basic_string");
}



/* 001168d0 vector */

/* std::__ndk1::vector<float, std::__ndk1::allocator<float> >::vector(unsigned long, float const&)
    */

void __thiscall
std::__ndk1::vector<float,std::__ndk1::allocator<float>>::vector
          (vector<float,std::__ndk1::allocator<float>> *this,ulong param_1,float *param_2)

{
  float *pfVar1;
  float *pfVar2;
  undefined8 uVar3;
  void *pvVar4;
  float *pfVar5;
  ulong uVar6;
  ulong uVar7;
  undefined8 *puVar8;
  ulong uVar9;
  float fVar10;
  
  *(undefined8 *)this = 0;
  *(undefined8 *)(this + 8) = 0;
  *(undefined8 *)(this + 0x10) = 0;
  if (param_1 == 0) {
    return;
  }
  if (param_1 >> 0x3e != 0) {
    uVar3 = __throw_length_error_abi_ne180000_();
                    /* catch() { ... } // from try @ 00116904 with catch @ 00116984 */
    pvVar4 = *(void **)this;
    if (pvVar4 != (void *)0x0) {
      *(void **)(this + 8) = pvVar4;
      operator_delete(pvVar4);
    }
                    /* WARNING: Subroutine does not return */
    _Unwind_Resume(uVar3);
  }
                    /* try { // try from 00116904 to 00116983 has its CatchHandler @ 00116984 */
  pfVar2 = (float *)operator_new(param_1 << 2);
  pfVar1 = pfVar2 + param_1;
  fVar10 = *param_2;
  uVar6 = param_1 - 1 & 0x3fffffffffffffff;
  *(float **)this = pfVar2;
  *(float **)(this + 8) = pfVar2;
  *(float **)(this + 0x10) = pfVar1;
  if (6 < uVar6) {
    uVar6 = uVar6 + 1;
    puVar8 = (undefined8 *)(pfVar2 + 4);
    uVar7 = uVar6 & 0x7ffffffffffffff8;
    uVar9 = uVar7;
    do {
      puVar8[-1] = CONCAT44(fVar10,fVar10);
      puVar8[-2] = CONCAT44(fVar10,fVar10);
      puVar8[1] = CONCAT44(fVar10,fVar10);
      *puVar8 = CONCAT44(fVar10,fVar10);
      uVar9 = uVar9 - 8;
      puVar8 = puVar8 + 4;
    } while (uVar9 != 0);
    pfVar2 = pfVar2 + uVar7;
    if (uVar6 == uVar7) goto LAB_00116968;
  }
  do {
    pfVar5 = pfVar2 + 1;
    *pfVar2 = fVar10;
    pfVar2 = pfVar5;
  } while (pfVar5 != pfVar1);
LAB_00116968:
  *(float **)(this + 8) = pfVar1;
  return;
}



/* 001169a4 ~vector[abi:ne180000] */

/* std::__ndk1::vector<LeicaRange, std::__ndk1::allocator<LeicaRange> >::~vector[abi:ne180000]() */

void __thiscall
std::__ndk1::vector<LeicaRange,std::__ndk1::allocator<LeicaRange>>::~vector_abi_ne180000_
          (vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *this)

{
  if (*(LeicaRange **)this != (LeicaRange *)0x0) {
    __base_destruct_at_end_abi_ne180000_(this,*(LeicaRange **)this);
    operator_delete(*(void **)this);
    return;
  }
  return;
}



/* 001169d4 ~LeicaRange */

/* LeicaRange::~LeicaRange() */

void __thiscall LeicaRange::~LeicaRange(LeicaRange *this)

{
  LeicaRange **this_00;
  
  this_00 = (LeicaRange **)(this + 0x10);
  if (*this_00 != (LeicaRange *)0x0) {
    std::__ndk1::vector<LeicaRange,std::__ndk1::allocator<LeicaRange>>::
    __base_destruct_at_end_abi_ne180000_
              ((vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *)this_00,*this_00);
    operator_delete(*this_00);
    return;
  }
  return;
}



/* 00116a04 __push_back_slow_path<LeicaRange_const&> */

/* LeicaRange* std::__ndk1::vector<LeicaRange, std::__ndk1::allocator<LeicaRange>
   >::__push_back_slow_path<LeicaRange const&>(LeicaRange const&) */

LeicaRange * __thiscall
std::__ndk1::vector<LeicaRange,std::__ndk1::allocator<LeicaRange>>::
__push_back_slow_path<LeicaRange_const&>
          (vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *this,LeicaRange *param_1)

{
  ulong uVar1;
  LeicaRange **ppLVar2;
  LeicaRange *pLVar3;
  undefined4 uVar4;
  void *pvVar5;
  LeicaRange **ppLVar6;
  long lVar7;
  LeicaRange **ppLVar8;
  LeicaRange **ppLVar9;
  long lVar10;
  ulong uVar11;
  LeicaRange **ppLVar12;
  LeicaRange **ppLVar13;
  LeicaRange *pLVar14;
  
  lVar7 = *(long *)(this + 8) - *(long *)this >> 3;
  uVar1 = lVar7 * -0x3333333333333333 + 1;
  if (0x666666666666666 < uVar1) {
    __throw_length_error_abi_ne180000_();
LAB_00116bbc:
                    /* WARNING: Subroutine does not return */
    __throw_bad_array_new_length_abi_ne180000_();
  }
  lVar10 = *(long *)(this + 0x10) - *(long *)this >> 3;
  uVar11 = lVar10 * -0x6666666666666666;
  if (uVar11 < uVar1 || uVar11 - uVar1 == 0) {
    uVar11 = uVar1;
  }
  if (0x333333333333332 < (ulong)(lVar10 * -0x3333333333333333)) {
    uVar11 = 0x666666666666666;
  }
  if (uVar11 == 0) {
    pvVar5 = (void *)0x0;
  }
  else {
    if (0x666666666666666 < uVar11) goto LAB_00116bbc;
    pvVar5 = operator_new(uVar11 * 0x28);
  }
  pLVar14 = *(LeicaRange **)(param_1 + 0x10);
  pLVar3 = *(LeicaRange **)(param_1 + 0x18);
  ppLVar8 = (LeicaRange **)((long)pvVar5 + lVar7 * 8);
  *ppLVar8 = *(LeicaRange **)param_1;
  *(undefined4 *)(ppLVar8 + 1) = *(undefined4 *)(param_1 + 8);
  ppLVar8[3] = (LeicaRange *)0x0;
  ppLVar8[4] = (LeicaRange *)0x0;
  ppLVar8[2] = (LeicaRange *)0x0;
                    /* try { // try from 00116ae8 to 00116aef has its CatchHandler @ 00116bc0 */
  __init_with_size_abi_ne180000_<LeicaRange*,LeicaRange*>
            ((vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *)(ppLVar8 + 2),pLVar14,pLVar3,
             ((long)pLVar3 - (long)pLVar14 >> 3) * -0x3333333333333333);
  ppLVar12 = *(LeicaRange ***)this;
  ppLVar6 = *(LeicaRange ***)(this + 8);
  ppLVar2 = ppLVar8 + 5;
  ppLVar9 = ppLVar8;
  ppLVar13 = ppLVar6;
  if (ppLVar6 != ppLVar12) {
    do {
      ppLVar13 = ppLVar6 + -5;
      uVar4 = *(undefined4 *)(ppLVar6 + -4);
      ppLVar8 = ppLVar9 + -5;
      *ppLVar8 = *ppLVar13;
      *(undefined4 *)(ppLVar9 + -4) = uVar4;
      ppLVar9[-2] = (LeicaRange *)0x0;
      ppLVar9[-1] = (LeicaRange *)0x0;
      ppLVar9[-3] = (LeicaRange *)0x0;
      pLVar14 = ppLVar6[-3];
      ppLVar9[-2] = ppLVar6[-2];
      ppLVar9[-3] = pLVar14;
      ppLVar9[-1] = ppLVar6[-1];
      ppLVar6[-3] = (LeicaRange *)0x0;
      ppLVar6[-2] = (LeicaRange *)0x0;
      ppLVar6[-1] = (LeicaRange *)0x0;
      ppLVar6 = ppLVar13;
      ppLVar9 = ppLVar8;
    } while (ppLVar13 != ppLVar12);
    ppLVar6 = *(LeicaRange ***)(this + 8);
    ppLVar13 = *(LeicaRange ***)this;
  }
  *(LeicaRange ***)this = ppLVar8;
  *(LeicaRange ***)(this + 8) = ppLVar2;
  *(void **)(this + 0x10) = (void *)((long)pvVar5 + uVar11 * 0x28);
  if (ppLVar6 != ppLVar13) {
    ppLVar12 = ppLVar6 + -3;
    do {
      if (*ppLVar12 != (LeicaRange *)0x0) {
        __base_destruct_at_end_abi_ne180000_
                  ((vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *)ppLVar12,*ppLVar12);
        operator_delete(*ppLVar12);
      }
      ppLVar9 = ppLVar12 + -2;
      ppLVar12 = ppLVar12 + -5;
      ppLVar6 = ppLVar13;
    } while (ppLVar9 != ppLVar13);
  }
  if (ppLVar6 != (LeicaRange **)0x0) {
    operator_delete(ppLVar6);
  }
  return (LeicaRange *)ppLVar2;
}



/* 00116bd4 __init_with_size[abi:ne180000]<LeicaRange*,LeicaRange*> */

/* void std::__ndk1::vector<LeicaRange, std::__ndk1::allocator<LeicaRange>
   >::__init_with_size[abi:ne180000]<LeicaRange*, LeicaRange*>(LeicaRange*, LeicaRange*, unsigned
   long) */

void __thiscall
std::__ndk1::vector<LeicaRange,std::__ndk1::allocator<LeicaRange>>::
__init_with_size_abi_ne180000_<LeicaRange*,LeicaRange*>
          (vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *this,LeicaRange *param_1,
          LeicaRange *param_2,ulong param_3)

{
  undefined4 uVar1;
  undefined8 uVar2;
  vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *local_78;
  undefined local_70;
  void **local_68;
  undefined8 **ppuStack_60;
  undefined8 **local_58;
  undefined local_50;
  undefined8 *local_48;
  undefined8 *local_28;
  
  local_70 = 0;
  if (param_3 != 0) {
    local_78 = this;
    if (0x666666666666666 < param_3) {
                    /* try { // try from 00116ccc to 00116cd3 has its CatchHandler @ 00116cd4 */
      uVar2 = __throw_length_error_abi_ne180000_();
                    /* catch() { ... } // from try @ 00116c24 with catch @ 00116cd4
                       catch() { ... } // from try @ 00116ccc with catch @ 00116cd4 */
      __exception_guard_exceptions<std::__ndk1::vector<LeicaRange,std::__ndk1::allocator<LeicaRange>>::__destroy_vector>
      ::~__exception_guard_exceptions_abi_ne180000_
                ((__exception_guard_exceptions<std::__ndk1::vector<LeicaRange,std::__ndk1::allocator<LeicaRange>>::__destroy_vector>
                  *)&local_78);
                    /* WARNING: Subroutine does not return */
      _Unwind_Resume(uVar2);
    }
                    /* try { // try from 00116c24 to 00116c27 has its CatchHandler @ 00116cd4 */
    local_28 = (undefined8 *)operator_new(param_3 * 0x28);
    *(undefined8 **)this = local_28;
    *(undefined8 **)(this + 8) = local_28;
    local_50 = 0;
    local_68 = (void **)(this + 0x10);
    *local_68 = local_28 + param_3 * 5;
    ppuStack_60 = &local_48;
    local_58 = &local_28;
    local_48 = local_28;
    if (param_1 != param_2) {
      do {
        uVar1 = *(undefined4 *)((long)param_1 + 8);
        uVar2 = *(undefined8 *)param_1;
        local_28[3] = 0;
        local_28[4] = 0;
        *(undefined4 *)(local_28 + 1) = uVar1;
        *local_28 = uVar2;
        local_28[2] = 0;
                    /* try { // try from 00116c94 to 00116c97 has its CatchHandler @ 00116cdc */
        __init_with_size_abi_ne180000_<LeicaRange*,LeicaRange*>
                  ((vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *)(local_28 + 2),
                   *(LeicaRange **)((long)param_1 + 0x10),*(LeicaRange **)((long)param_1 + 0x18),
                   ((long)*(LeicaRange **)((long)param_1 + 0x18) -
                    (long)*(LeicaRange **)((long)param_1 + 0x10) >> 3) * -0x3333333333333333);
        param_1 = (LeicaRange *)((long)param_1 + 0x28);
        local_28 = local_28 + 5;
      } while (param_1 != param_2);
    }
    *(undefined8 **)(this + 8) = local_28;
  }
  return;
}



/* 00116cfc ~__exception_guard_exceptions[abi:ne180000] */

/* std::__ndk1::__exception_guard_exceptions<std::__ndk1::vector<LeicaRange,
   std::__ndk1::allocator<LeicaRange>
   >::__destroy_vector>::~__exception_guard_exceptions[abi:ne180000]() */

void __thiscall
std::__ndk1::
__exception_guard_exceptions<std::__ndk1::vector<LeicaRange,std::__ndk1::allocator<LeicaRange>>::__destroy_vector>
::~__exception_guard_exceptions_abi_ne180000_
          (__exception_guard_exceptions<std::__ndk1::vector<LeicaRange,std::__ndk1::allocator<LeicaRange>>::__destroy_vector>
           *this)

{
  LeicaRange *pLVar1;
  
  if (this[8] ==
      (__exception_guard_exceptions<std::__ndk1::vector<LeicaRange,std::__ndk1::allocator<LeicaRange>>::__destroy_vector>
       )0x0) {
    pLVar1 = **(LeicaRange ***)this;
    if (pLVar1 != (LeicaRange *)0x0) {
      vector<LeicaRange,std::__ndk1::allocator<LeicaRange>>::__base_destruct_at_end_abi_ne180000_
                ((vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *)*(LeicaRange ***)this,
                 pLVar1);
      operator_delete(**(void ***)this);
      return;
    }
  }
  return;
}



/* 00116d40 __throw_length_error[abi:ne180000] */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* std::__ndk1::vector<LeicaRange, std::__ndk1::allocator<LeicaRange>
   >::__throw_length_error[abi:ne180000]() const */

void std::__ndk1::vector<LeicaRange,std::__ndk1::allocator<LeicaRange>>::
     __throw_length_error_abi_ne180000_(void)

{
                    /* WARNING: Subroutine does not return */
  __ndk1::__throw_length_error_abi_ne180000_("vector");
}



/* 00116d54 ~__exception_guard_exceptions[abi:ne180000] */

/* std::__ndk1::__exception_guard_exceptions<std::__ndk1::_AllocatorDestroyRangeReverse<std::__ndk1::allocator<LeicaRange>,
   LeicaRange*> >::~__exception_guard_exceptions[abi:ne180000]() */

void __thiscall
std::__ndk1::
__exception_guard_exceptions<std::__ndk1::_AllocatorDestroyRangeReverse<std::__ndk1::allocator<LeicaRange>,LeicaRange*>>
::~__exception_guard_exceptions_abi_ne180000_
          (__exception_guard_exceptions<std::__ndk1::_AllocatorDestroyRangeReverse<std::__ndk1::allocator<LeicaRange>,LeicaRange*>>
           *this)

{
  LeicaRange **ppLVar1;
  LeicaRange **this_00;
  LeicaRange **ppLVar2;
  
  if (this[0x18] !=
      (__exception_guard_exceptions<std::__ndk1::_AllocatorDestroyRangeReverse<std::__ndk1::allocator<LeicaRange>,LeicaRange*>>
       )0x0) {
    return;
  }
  ppLVar2 = (LeicaRange **)**(undefined8 **)(this + 8);
  if ((LeicaRange **)**(undefined8 **)(this + 0x10) != ppLVar2) {
    this_00 = (LeicaRange **)**(undefined8 **)(this + 0x10) + -3;
    do {
      if (*this_00 != (LeicaRange *)0x0) {
        vector<LeicaRange,std::__ndk1::allocator<LeicaRange>>::__base_destruct_at_end_abi_ne180000_
                  ((vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *)this_00,*this_00);
        operator_delete(*this_00);
      }
      ppLVar1 = this_00 + -2;
      this_00 = this_00 + -5;
    } while (ppLVar1 != ppLVar2);
  }
  return;
}



/* 00116dc0 __base_destruct_at_end[abi:ne180000] */

/* std::__ndk1::vector<LeicaRange, std::__ndk1::allocator<LeicaRange>
   >::__base_destruct_at_end[abi:ne180000](LeicaRange*) */

void __thiscall
std::__ndk1::vector<LeicaRange,std::__ndk1::allocator<LeicaRange>>::
__base_destruct_at_end_abi_ne180000_
          (vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *this,LeicaRange *param_1)

{
  LeicaRange **ppLVar1;
  LeicaRange **this_00;
  
  if (*(LeicaRange **)(this + 8) != param_1) {
    this_00 = (LeicaRange **)(*(LeicaRange **)(this + 8) + -0x18);
    do {
      if (*this_00 != (LeicaRange *)0x0) {
        __base_destruct_at_end_abi_ne180000_
                  ((vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *)this_00,*this_00);
        operator_delete(*this_00);
      }
      ppLVar1 = this_00 + -2;
      this_00 = this_00 + -5;
    } while (ppLVar1 != (LeicaRange **)param_1);
  }
  *(LeicaRange **)(this + 8) = param_1;
  return;
}



/* 00116e2c ~__split_buffer */

/* std::__ndk1::__split_buffer<LeicaRange, std::__ndk1::allocator<LeicaRange>&>::~__split_buffer()
    */

void __thiscall
std::__ndk1::__split_buffer<LeicaRange,std::__ndk1::allocator<LeicaRange>&>::~__split_buffer
          (__split_buffer<LeicaRange,std::__ndk1::allocator<LeicaRange>&> *this)

{
  long lVar1;
  LeicaRange *pLVar2;
  long lVar3;
  LeicaRange **this_00;
  
  lVar1 = *(long *)(this + 8);
  lVar3 = *(long *)(this + 0x10);
  while (lVar3 != lVar1) {
    while( true ) {
      this_00 = (LeicaRange **)(lVar3 + -0x18);
      pLVar2 = *this_00;
      lVar3 = lVar3 + -0x28;
      *(long *)(this + 0x10) = lVar3;
      if (pLVar2 != (LeicaRange *)0x0) break;
      if (lVar3 == lVar1) goto LAB_00116e88;
    }
    vector<LeicaRange,std::__ndk1::allocator<LeicaRange>>::__base_destruct_at_end_abi_ne180000_
              ((vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *)this_00,pLVar2);
    operator_delete(*this_00);
    lVar3 = *(long *)(this + 0x10);
  }
LAB_00116e88:
  if (*(void **)this != (void *)0x0) {
    operator_delete(*(void **)this);
    return;
  }
  return;
}



/* 00116eb0 __throw_length_error[abi:ne180000] */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* std::__ndk1::vector<float, std::__ndk1::allocator<float> >::__throw_length_error[abi:ne180000]()
   const */

void std::__ndk1::vector<float,std::__ndk1::allocator<float>>::__throw_length_error_abi_ne180000_
               (void)

{
                    /* WARNING: Subroutine does not return */
  __ndk1::__throw_length_error_abi_ne180000_("vector");
}



/* 00116ec4 ~map[abi:ne180000] */

/* std::__ndk1::map<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>,
   std::__ndk1::allocator<char> >, std::__ndk1::vector<unsigned char,
   std::__ndk1::allocator<unsigned char> >, std::__ndk1::less<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > >,
   std::__ndk1::allocator<std::__ndk1::pair<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const,
   std::__ndk1::vector<unsigned char, std::__ndk1::allocator<unsigned char> > > >
   >::~map[abi:ne180000]() */

void __thiscall
std::__ndk1::
map<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,std::__ndk1::allocator<std::__ndk1::pair<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>const,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
::~map_abi_ne180000_
          (map<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,std::__ndk1::allocator<std::__ndk1::pair<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>const,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
           *this)

{
  __tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
  ::destroy((__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
             *)this,*(__tree_node **)(this + 8));
  return;
}



/* 00116ecc destroy */

/* std::__ndk1::__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, std::__ndk1::vector<unsigned
   char, std::__ndk1::allocator<unsigned char> > >,
   std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>,
   std::__ndk1::allocator<char> >, std::__ndk1::__value_type<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, std::__ndk1::vector<unsigned
   char, std::__ndk1::allocator<unsigned char> > >,
   std::__ndk1::less<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>,
   std::__ndk1::allocator<char> > >, true>,
   std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, std::__ndk1::vector<unsigned
   char, std::__ndk1::allocator<unsigned char> > > >
   >::destroy(std::__ndk1::__tree_node<std::__ndk1::__value_type<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, std::__ndk1::vector<unsigned
   char, std::__ndk1::allocator<unsigned char> > >, void*>*) */

void __thiscall
std::__ndk1::
__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
::destroy(__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
          *this,__tree_node *param_1)

{
  void *pvVar1;
  
  if (param_1 != (__tree_node *)0x0) {
    destroy(this,*(__tree_node **)param_1);
    destroy(this,*(__tree_node **)(param_1 + 8));
    pvVar1 = *(void **)(param_1 + 0x38);
    if (pvVar1 != (void *)0x0) {
      *(void **)(param_1 + 0x40) = pvVar1;
      operator_delete(pvVar1);
    }
    if (((byte)param_1[0x20] & 1) != 0) {
      operator_delete(*(void **)(param_1 + 0x30));
    }
    operator_delete(param_1);
    return;
  }
  return;
}



/* 00116f2c find<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>> */

/* std::__ndk1::__tree_iterator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, std::__ndk1::vector<unsigned
   char, std::__ndk1::allocator<unsigned char> > >,
   std::__ndk1::__tree_node<std::__ndk1::__value_type<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, std::__ndk1::vector<unsigned
   char, std::__ndk1::allocator<unsigned char> > >, void*>*, long>
   std::__ndk1::__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, std::__ndk1::vector<unsigned
   char, std::__ndk1::allocator<unsigned char> > >,
   std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>,
   std::__ndk1::allocator<char> >, std::__ndk1::__value_type<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, std::__ndk1::vector<unsigned
   char, std::__ndk1::allocator<unsigned char> > >,
   std::__ndk1::less<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>,
   std::__ndk1::allocator<char> > >, true>,
   std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, std::__ndk1::vector<unsigned
   char, std::__ndk1::allocator<unsigned char> > > > >::find<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > >(std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> > const&) */

__tree_iterator __thiscall
std::__ndk1::
__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
::find<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>
          (__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
           *this,basic_string *param_1)

{
  __tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
  *p_Var1;
  __tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
  *p_Var2;
  __tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
  *p_Var3;
  __tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
  *p_Var4;
  basic_string *__s2;
  __tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
  **pp_Var5;
  bool bVar6;
  int iVar7;
  __tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
  **pp_Var8;
  __tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
  **pp_Var9;
  __tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
  **pp_Var10;
  
  pp_Var8 = (__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
             **)(this + 8);
  pp_Var10 = (__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
              **)*pp_Var8;
  if (pp_Var10 !=
      (__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
       **)0x0) {
    p_Var4 = *(__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
               **)(param_1 + 8);
    __s2 = *(basic_string **)(param_1 + 0x10);
    pp_Var9 = pp_Var8;
    if (((byte)*param_1 & 1) == 0) {
      __s2 = param_1 + 1;
      p_Var4 = (__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
                *)(ulong)((byte)*param_1 >> 1);
    }
    do {
      bVar6 = ((byte)*(__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
                       *)(pp_Var10 + 4) & 1) != 0;
      p_Var2 = (__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
                *)(ulong)((byte)*(__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
                                  *)(pp_Var10 + 4) >> 1);
      if (bVar6) {
        p_Var2 = pp_Var10[5];
      }
      p_Var1 = (__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
                *)((long)pp_Var10 + 0x21);
      if (bVar6) {
        p_Var1 = pp_Var10[6];
      }
      p_Var3 = p_Var4;
      if (p_Var2 <= p_Var4) {
        p_Var3 = p_Var2;
      }
      iVar7 = memcmp(p_Var1,__s2,(size_t)p_Var3);
      bVar6 = p_Var2 < p_Var4;
      if (iVar7 != 0) {
        bVar6 = iVar7 < 0;
      }
      pp_Var5 = pp_Var10 + 1;
      if (!bVar6) {
        pp_Var9 = pp_Var10;
        pp_Var5 = pp_Var10;
      }
      pp_Var10 = (__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
                  **)*pp_Var5;
    } while (pp_Var10 !=
             (__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
              **)0x0);
    if (pp_Var9 != pp_Var8) {
      p_Var2 = (__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
                *)(ulong)((byte)*(__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
                                  *)(pp_Var9 + 4) >> 1);
      p_Var1 = (__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
                *)((long)pp_Var9 + 0x21);
      if (((byte)*(__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
                   *)(pp_Var9 + 4) & 1) != 0) {
        p_Var2 = pp_Var9[5];
        p_Var1 = pp_Var9[6];
      }
      p_Var3 = p_Var2;
      if (p_Var4 <= p_Var2) {
        p_Var3 = p_Var4;
      }
      iVar7 = memcmp(__s2,p_Var1,(size_t)p_Var3);
      bVar6 = p_Var4 < p_Var2;
      if (iVar7 != 0) {
        bVar6 = iVar7 < 0;
      }
      if (!bVar6) {
        pp_Var8 = pp_Var9;
      }
    }
  }
  return (__tree_iterator)pp_Var8;
}



/* 00117028 __emplace_unique_impl<char_const*&,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>> */

/* std::__ndk1::pair<std::__ndk1::__tree_iterator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, std::__ndk1::vector<unsigned
   char, std::__ndk1::allocator<unsigned char> > >,
   std::__ndk1::__tree_node<std::__ndk1::__value_type<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, std::__ndk1::vector<unsigned
   char, std::__ndk1::allocator<unsigned char> > >, void*>*, long>, bool>
   std::__ndk1::__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, std::__ndk1::vector<unsigned
   char, std::__ndk1::allocator<unsigned char> > >,
   std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>,
   std::__ndk1::allocator<char> >, std::__ndk1::__value_type<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, std::__ndk1::vector<unsigned
   char, std::__ndk1::allocator<unsigned char> > >,
   std::__ndk1::less<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>,
   std::__ndk1::allocator<char> > >, true>,
   std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, std::__ndk1::vector<unsigned
   char, std::__ndk1::allocator<unsigned char> > > > >::__emplace_unique_impl<char const*&,
   std::__ndk1::vector<unsigned char, std::__ndk1::allocator<unsigned char> > >(char const*&,
   std::__ndk1::vector<unsigned char, std::__ndk1::allocator<unsigned char> >&&) */

pair std::__ndk1::
     __tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
     ::
     __emplace_unique_impl<char_const*&,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>
               (char **param_1,vector *param_2)

{
  __tree_node_base **pp_Var1;
  void *pvVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  __tree_end_node *local_40;
  undefined8 *local_38;
  char local_28;
  
  __construct_node<char_const*&,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>
            (param_1,param_2);
                    /* try { // try from 00117048 to 00117057 has its CatchHandler @ 001170f8 */
  pp_Var1 = __find_equal<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>
                      ((__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
                        *)param_1,&local_40,(__value_type *)(local_38 + 4));
  puVar3 = local_38;
  puVar4 = (undefined8 *)*pp_Var1;
  if (puVar4 == (undefined8 *)0x0) {
    *local_38 = 0;
    local_38[1] = 0;
    local_38[2] = local_40;
    *pp_Var1 = (__tree_node_base *)local_38;
    if (*(char **)*param_1 != (char *)0x0) {
      *param_1 = *(char **)*param_1;
      puVar3 = (undefined8 *)*pp_Var1;
    }
    __tree_balance_after_insert_abi_ne180000_<std::__ndk1::__tree_node_base<void*>*>
              ((__tree_node_base *)param_1[1],(__tree_node_base *)puVar3);
    param_1[2] = param_1[2] + 1;
    puVar4 = local_38;
  }
  else {
    local_38 = (undefined8 *)0x0;
    if (puVar3 != (undefined8 *)0x0) {
      if (local_28 != '\0') {
        pvVar2 = (void *)puVar3[7];
        if (pvVar2 != (void *)0x0) {
          puVar3[8] = pvVar2;
          operator_delete(pvVar2);
        }
        if ((*(byte *)(puVar3 + 4) & 1) != 0) {
          operator_delete((void *)puVar3[6]);
        }
      }
      operator_delete(puVar3);
    }
  }
  return (pair)puVar4;
}



/* 0011710c __construct_node<char_const*&,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>> */

/* std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, std::__ndk1::vector<unsigned
   char, std::__ndk1::allocator<unsigned char> > >, void*>,
   std::__ndk1::__tree_node_destructor<std::__ndk1::allocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, std::__ndk1::vector<unsigned
   char, std::__ndk1::allocator<unsigned char> > >, void*> > > >
   std::__ndk1::__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, std::__ndk1::vector<unsigned
   char, std::__ndk1::allocator<unsigned char> > >,
   std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>,
   std::__ndk1::allocator<char> >, std::__ndk1::__value_type<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, std::__ndk1::vector<unsigned
   char, std::__ndk1::allocator<unsigned char> > >,
   std::__ndk1::less<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>,
   std::__ndk1::allocator<char> > >, true>,
   std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, std::__ndk1::vector<unsigned
   char, std::__ndk1::allocator<unsigned char> > > > >::__construct_node<char const*&,
   std::__ndk1::vector<unsigned char, std::__ndk1::allocator<unsigned char> > >(char const*&,
   std::__ndk1::vector<unsigned char, std::__ndk1::allocator<unsigned char> >&&) */

unique_ptr
std::__ndk1::
__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
::
__construct_node<char_const*&,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>
          (char **param_1,vector *param_2)

{
  ulong uVar1;
  unique_ptr uVar2;
  void *pvVar3;
  size_t __n;
  void *__dest;
  undefined8 *in_x2;
  void **in_x8;
  undefined8 uVar5;
  char *__s;
  undefined8 uVar6;
  undefined8 uVar7;
  void *pvVar4;
  
  pvVar3 = operator_new(0x50);
  __s = *(char **)param_2;
  *in_x8 = pvVar3;
  in_x8[1] = param_1 + 1;
  *(undefined *)(in_x8 + 2) = 0;
  __n = strlen(__s);
  if (0xffffffffffffffef < __n) {
                    /* try { // try from 001171e8 to 001171ef has its CatchHandler @ 001171f0 */
    uVar5 = basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>::
            __throw_length_error_abi_ne180000_();
                    /* catch() { ... } // from try @ 00117184 with catch @ 001171f0
                       catch() { ... } // from try @ 001171e8 with catch @ 001171f0 */
    unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,void*>,std::__ndk1::__tree_node_destructor<std::__ndk1::allocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,void*>>>>
    ::~unique_ptr_abi_ne180000_
              ((unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,void*>,std::__ndk1::__tree_node_destructor<std::__ndk1::allocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,void*>>>>
                *)in_x8);
                    /* WARNING: Subroutine does not return */
    _Unwind_Resume(uVar5);
  }
  if (__n < 0x17) {
    __dest = (void *)((long)pvVar3 + 0x21);
    *(char *)((long)pvVar3 + 0x20) = (char)((int)__n << 1);
    if (__n == 0) {
      uVar2 = 0;
      goto LAB_001171ac;
    }
  }
  else {
    uVar1 = (__n | 0xf) + 1;
                    /* try { // try from 00117184 to 0011718b has its CatchHandler @ 001171f0 */
    __dest = operator_new(uVar1);
    *(size_t *)((long)pvVar3 + 0x28) = __n;
    *(void **)((long)pvVar3 + 0x30) = __dest;
    *(ulong *)((long)pvVar3 + 0x20) = uVar1 | 1;
  }
  pvVar4 = memmove(__dest,__s,__n);
  uVar2 = (unique_ptr)pvVar4;
LAB_001171ac:
  *(undefined *)((long)__dest + __n) = 0;
  uVar5 = in_x2[2];
  uVar7 = in_x2[1];
  uVar6 = *in_x2;
  in_x2[1] = 0;
  in_x2[2] = 0;
  *in_x2 = 0;
  *(undefined8 *)((long)pvVar3 + 0x48) = uVar5;
  *(undefined8 *)((long)pvVar3 + 0x40) = uVar7;
  *(undefined8 *)((long)pvVar3 + 0x38) = uVar6;
  *(undefined *)(in_x8 + 2) = 1;
  return uVar2;
}



/* 00117204 __find_equal<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>> */

/* std::__ndk1::__tree_node_base<void*>*&
   std::__ndk1::__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, std::__ndk1::vector<unsigned
   char, std::__ndk1::allocator<unsigned char> > >,
   std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>,
   std::__ndk1::allocator<char> >, std::__ndk1::__value_type<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, std::__ndk1::vector<unsigned
   char, std::__ndk1::allocator<unsigned char> > >,
   std::__ndk1::less<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>,
   std::__ndk1::allocator<char> > >, true>,
   std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, std::__ndk1::vector<unsigned
   char, std::__ndk1::allocator<unsigned char> > > >
   >::__find_equal<std::__ndk1::__value_type<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, std::__ndk1::vector<unsigned
   char, std::__ndk1::allocator<unsigned char> > >
   >(std::__ndk1::__tree_end_node<std::__ndk1::__tree_node_base<void*>*>*&,
   std::__ndk1::__value_type<std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>,
   std::__ndk1::allocator<char> >, std::__ndk1::vector<unsigned char,
   std::__ndk1::allocator<unsigned char> > > const&) */

__tree_node_base ** __thiscall
std::__ndk1::
__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
::
__find_equal<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>
          (__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
           *this,__tree_end_node **param_1,__value_type *param_2)

{
  __tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
  *__s2;
  __tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
  *__n;
  __tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
  *p_Var1;
  __value_type *__s1;
  bool bVar2;
  __tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
  *p_Var3;
  int iVar4;
  __tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
  **pp_Var5;
  __tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
  **pp_Var6;
  __tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
  **pp_Var7;
  
  pp_Var6 = (__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
             **)(this + 8);
  pp_Var5 = (__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
             **)*pp_Var6;
  pp_Var7 = pp_Var6;
  if (pp_Var5 !=
      (__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
       **)0x0) {
    p_Var1 = *(__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
               **)(param_2 + 8);
    __s1 = *(__value_type **)(param_2 + 0x10);
    if (((byte)*param_2 & 1) == 0) {
      __s1 = param_2 + 1;
      p_Var1 = (__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
                *)(ulong)((byte)*param_2 >> 1);
    }
    do {
      while( true ) {
        pp_Var7 = pp_Var5;
        __s2 = (__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
                *)((long)pp_Var7 + 0x21);
        p_Var3 = (__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
                  *)(ulong)((byte)*(__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
                                    *)(pp_Var7 + 4) >> 1);
        if (((byte)*(__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
                     *)(pp_Var7 + 4) & 1) != 0) {
          __s2 = pp_Var7[6];
          p_Var3 = pp_Var7[5];
        }
        __n = p_Var3;
        if (p_Var1 <= p_Var3) {
          __n = p_Var1;
        }
        iVar4 = memcmp(__s1,__s2,(size_t)__n);
        bVar2 = p_Var1 < p_Var3;
        if (iVar4 != 0) {
          bVar2 = iVar4 < 0;
        }
        if (bVar2) break;
        iVar4 = memcmp(__s2,__s1,(size_t)__n);
        bVar2 = p_Var3 < p_Var1;
        if (iVar4 != 0) {
          bVar2 = iVar4 < 0;
        }
        if (!bVar2) goto LAB_001172e8;
        pp_Var6 = pp_Var7 + 1;
        pp_Var5 = (__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
                   **)*pp_Var6;
        if ((__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
             **)*pp_Var6 ==
            (__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
             **)0x0) goto LAB_001172e8;
      }
      pp_Var5 = (__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
                 **)*pp_Var7;
      pp_Var6 = pp_Var7;
    } while ((__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
              **)*pp_Var7 !=
             (__tree<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::__map_value_compare<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,std::__ndk1::less<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>>,true>,std::__ndk1::allocator<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>>>
              **)0x0);
  }
LAB_001172e8:
  *param_1 = (__tree_end_node *)pp_Var7;
  return (__tree_node_base **)pp_Var6;
}



/* 00117308 ~unique_ptr[abi:ne180000] */

/* std::__ndk1::unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, std::__ndk1::vector<unsigned
   char, std::__ndk1::allocator<unsigned char> > >, void*>,
   std::__ndk1::__tree_node_destructor<std::__ndk1::allocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<std::__ndk1::basic_string<char,
   std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >, std::__ndk1::vector<unsigned
   char, std::__ndk1::allocator<unsigned char> > >, void*> > > >::~unique_ptr[abi:ne180000]() */

void __thiscall
std::__ndk1::
unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,void*>,std::__ndk1::__tree_node_destructor<std::__ndk1::allocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,void*>>>>
::~unique_ptr_abi_ne180000_
          (unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,void*>,std::__ndk1::__tree_node_destructor<std::__ndk1::allocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,void*>>>>
           *this)

{
  void *pvVar1;
  void *pvVar2;
  
  pvVar2 = *(void **)this;
  *(undefined8 *)this = 0;
  if (pvVar2 != (void *)0x0) {
    if (this[0x10] !=
        (unique_ptr<std::__ndk1::__tree_node<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,void*>,std::__ndk1::__tree_node_destructor<std::__ndk1::allocator<std::__ndk1::__tree_node<std::__ndk1::__value_type<std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>,std::__ndk1::vector<unsigned_char,std::__ndk1::allocator<unsigned_char>>>,void*>>>>
         )0x0) {
      pvVar1 = *(void **)((long)pvVar2 + 0x38);
      if (pvVar1 != (void *)0x0) {
        *(void **)((long)pvVar2 + 0x40) = pvVar1;
        operator_delete(pvVar1);
      }
      if ((*(byte *)((long)pvVar2 + 0x20) & 1) != 0) {
        operator_delete(*(void **)((long)pvVar2 + 0x30));
      }
    }
    operator_delete(pvVar2);
    return;
  }
  return;
}



/* 00117364 __tree_balance_after_insert[abi:ne180000]<std::__ndk1::__tree_node_base<void*>*> */

/* void 
   std::__ndk1::__tree_balance_after_insert[abi:ne180000]<std::__ndk1::__tree_node_base<void*>*>(std::__ndk1::__tree_node_base<void*>*,
   std::__ndk1::__tree_node_base<void*>*) */

void std::__ndk1::__tree_balance_after_insert_abi_ne180000_<std::__ndk1::__tree_node_base<void*>*>
               (__tree_node_base *param_1,__tree_node_base *param_2)

{
  __tree_node_base _Var1;
  long **pplVar2;
  long **pplVar3;
  long *plVar4;
  long **pplVar5;
  long **pplVar6;
  
  _Var1 = (__tree_node_base)(param_2 == param_1);
  param_2[0x18] = _Var1;
  do {
    if (((bool)_Var1) ||
       (pplVar3 = *(long ***)((long)param_2 + 0x10), *(char *)(pplVar3 + 3) != '\0')) {
      return;
    }
    pplVar2 = (long **)pplVar3[2];
    pplVar5 = (long **)*pplVar2;
    if (pplVar5 == pplVar3) {
      if ((pplVar2[1] == (long *)0x0) ||
         (pplVar5 = (long **)(pplVar2[1] + 3), *(char *)pplVar5 != '\0')) {
        pplVar5 = pplVar3;
        if (*pplVar3 != (long *)param_2) {
          pplVar5 = (long **)pplVar3[1];
          plVar4 = *pplVar5;
          pplVar3[1] = plVar4;
          pplVar6 = pplVar3;
          if (plVar4 != (long *)0x0) {
            plVar4[2] = (long)pplVar3;
            pplVar2 = (long **)pplVar3[2];
            pplVar6 = (long **)*pplVar2;
          }
          pplVar5[2] = (long *)pplVar2;
          if (pplVar6 != pplVar3) {
            pplVar2 = pplVar2 + 1;
          }
          *pplVar2 = (long *)pplVar5;
          pplVar3[2] = (long *)pplVar5;
          pplVar2 = (long **)pplVar5[2];
          *pplVar5 = (long *)pplVar3;
          pplVar3 = (long **)*pplVar2;
        }
        plVar4 = pplVar3[1];
        *(undefined *)(pplVar5 + 3) = 1;
        *(undefined *)(pplVar2 + 3) = 0;
        *pplVar2 = plVar4;
        if (plVar4 != (long *)0x0) {
          plVar4[2] = (long)pplVar2;
        }
        pplVar5 = (long **)pplVar2[2];
        pplVar6 = (long **)*pplVar5;
        pplVar3[2] = (long *)pplVar5;
        pplVar5[pplVar6 != pplVar2] = (long *)pplVar3;
        pplVar3[1] = (long *)pplVar2;
        pplVar2[2] = (long *)pplVar3;
        return;
      }
    }
    else if ((pplVar5 == (long **)0x0) || (pplVar5 = pplVar5 + 3, *(char *)pplVar5 != '\0')) {
      if (*pplVar3 == (long *)param_2) {
        plVar4 = *(long **)((long)param_2 + 8);
        *pplVar3 = plVar4;
        if (plVar4 != (long *)0x0) {
          plVar4[2] = (long)pplVar3;
          pplVar2 = (long **)pplVar3[2];
        }
        *(long ***)((long)param_2 + 0x10) = pplVar2;
        if ((long **)*pplVar2 != pplVar3) {
          pplVar2 = pplVar2 + 1;
        }
        *pplVar2 = (long *)param_2;
        pplVar3[2] = (long *)param_2;
        pplVar2 = *(long ***)((long)param_2 + 0x10);
        *(long ***)((long)param_2 + 8) = pplVar3;
        pplVar3 = (long **)param_2;
      }
      pplVar5 = (long **)pplVar2[1];
      *(undefined *)(pplVar3 + 3) = 1;
      plVar4 = *pplVar5;
      *(undefined *)(pplVar2 + 3) = 0;
      pplVar2[1] = plVar4;
      if (plVar4 != (long *)0x0) {
        plVar4[2] = (long)pplVar2;
      }
      plVar4 = pplVar2[2];
      pplVar3 = (long **)*plVar4;
      pplVar5[2] = plVar4;
      plVar4[pplVar3 != pplVar2] = (long)pplVar5;
      *pplVar5 = (long *)pplVar2;
      pplVar2[2] = (long *)pplVar5;
      return;
    }
    _Var1 = (__tree_node_base)(pplVar2 == (long **)param_1);
    *(undefined *)(pplVar3 + 3) = 1;
    *(__tree_node_base *)(pplVar2 + 3) = _Var1;
    *(char *)pplVar5 = '\x01';
    param_2 = (__tree_node_base *)pplVar2;
  } while( true );
}



/* 00117500 ~unique_ptr[abi:ne180000] */

/* std::__ndk1::unique_ptr<std::__ndk1::__thread_struct,
   std::__ndk1::default_delete<std::__ndk1::__thread_struct> >::~unique_ptr[abi:ne180000]() */

void __thiscall
std::__ndk1::
unique_ptr<std::__ndk1::__thread_struct,std::__ndk1::default_delete<std::__ndk1::__thread_struct>>::
~unique_ptr_abi_ne180000_
          (unique_ptr<std::__ndk1::__thread_struct,std::__ndk1::default_delete<std::__ndk1::__thread_struct>>
           *this)

{
  __thread_struct *this_00;
  
  this_00 = *(__thread_struct **)this;
  *(undefined8 *)this = 0;
  if (this_00 != (__thread_struct *)0x0) {
    std::__ndk1::__thread_struct::~__thread_struct(this_00);
    operator_delete(this_00);
    return;
  }
  return;
}



/* 0011753c __assign_with_size[abi:ne180000]<LeicaRange*,LeicaRange*> */

/* void std::__ndk1::vector<LeicaRange, std::__ndk1::allocator<LeicaRange>
   >::__assign_with_size[abi:ne180000]<LeicaRange*, LeicaRange*>(LeicaRange*, LeicaRange*, long) */

void __thiscall
std::__ndk1::vector<LeicaRange,std::__ndk1::allocator<LeicaRange>>::
__assign_with_size_abi_ne180000_<LeicaRange*,LeicaRange*>
          (vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *this,LeicaRange *param_1,
          LeicaRange *param_2,long param_3)

{
  undefined4 uVar1;
  long lVar2;
  undefined8 uVar3;
  ulong uVar4;
  undefined8 *puVar5;
  undefined8 *puVar6;
  undefined8 *puVar7;
  long *local_80;
  undefined8 **ppuStack_78;
  undefined8 **local_70;
  undefined local_68;
  undefined8 *local_60;
  undefined8 *local_58;
  
  puVar5 = *(undefined8 **)this;
  local_80 = (long *)(this + 0x10);
  lVar2 = *local_80;
  if ((ulong)param_3 <= (ulong)((lVar2 - (long)puVar5 >> 3) * -0x3333333333333333)) {
    lVar2 = (long)*(undefined8 **)(this + 8) - (long)puVar5;
    if ((ulong)((lVar2 >> 3) * -0x3333333333333333) < (ulong)param_3) {
      puVar7 = (undefined8 *)(param_1 + lVar2);
      if (*(undefined8 **)(this + 8) != puVar5) {
        do {
          uVar3 = *(undefined8 *)param_1;
          *(undefined4 *)(puVar5 + 1) = *(undefined4 *)((long)param_1 + 8);
          *puVar5 = uVar3;
          if ((undefined8 *)param_1 != puVar5) {
            __assign_with_size_abi_ne180000_<LeicaRange*,LeicaRange*>
                      ((vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *)(puVar5 + 2),
                       *(LeicaRange **)((long)param_1 + 0x10),*(LeicaRange **)((long)param_1 + 0x18)
                       ,((long)*(LeicaRange **)((long)param_1 + 0x18) -
                         (long)*(LeicaRange **)((long)param_1 + 0x10) >> 3) * -0x3333333333333333);
          }
          lVar2 = lVar2 + -0x28;
          param_1 = (LeicaRange *)((long)param_1 + 0x28);
          puVar5 = puVar5 + 5;
        } while (lVar2 != 0);
        puVar5 = *(undefined8 **)(this + 8);
      }
      ppuStack_78 = &local_60;
      local_70 = &local_58;
      local_68 = 0;
      local_58 = puVar5;
      local_60 = puVar5;
      for (; puVar7 != (undefined8 *)param_2; puVar7 = puVar7 + 5) {
        uVar1 = *(undefined4 *)(puVar7 + 1);
        uVar3 = *puVar7;
        local_58[3] = 0;
        local_58[4] = 0;
        *(undefined4 *)(local_58 + 1) = uVar1;
        *local_58 = uVar3;
        local_58[2] = 0;
                    /* try { // try from 001177c0 to 001177c3 has its CatchHandler @ 00117834 */
        __init_with_size_abi_ne180000_<LeicaRange*,LeicaRange*>
                  ((vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *)(local_58 + 2),
                   (LeicaRange *)puVar7[2],(LeicaRange *)puVar7[3],
                   ((long)(LeicaRange *)puVar7[3] - (long)(LeicaRange *)puVar7[2] >> 3) *
                   -0x3333333333333333);
        local_58 = local_58 + 5;
      }
      *(undefined8 **)(this + 8) = local_58;
      return;
    }
    puVar7 = puVar5;
    puVar6 = puVar5;
    if (param_1 != param_2) {
      do {
        uVar3 = *(undefined8 *)param_1;
        *(undefined4 *)(puVar5 + 1) = *(undefined4 *)((long)param_1 + 8);
        *puVar5 = uVar3;
        if ((undefined8 *)param_1 != puVar5) {
          __assign_with_size_abi_ne180000_<LeicaRange*,LeicaRange*>
                    ((vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *)(puVar5 + 2),
                     *(LeicaRange **)((long)param_1 + 0x10),*(LeicaRange **)((long)param_1 + 0x18),
                     ((long)*(LeicaRange **)((long)param_1 + 0x18) -
                      (long)*(LeicaRange **)((long)param_1 + 0x10) >> 3) * -0x3333333333333333);
        }
        param_1 = (LeicaRange *)((long)param_1 + 0x28);
        puVar5 = puVar5 + 5;
        puVar7 = puVar6 + 5;
        puVar6 = puVar6 + 5;
      } while (param_1 != param_2);
    }
    __base_destruct_at_end_abi_ne180000_(this,(LeicaRange *)puVar7);
    return;
  }
  if (puVar5 != (undefined8 *)0x0) {
    __base_destruct_at_end_abi_ne180000_(this,(LeicaRange *)puVar5);
    operator_delete(*(void **)this);
    lVar2 = 0;
    *(undefined8 *)this = 0;
    *(undefined8 *)(this + 8) = 0;
    *(undefined8 *)(this + 0x10) = 0;
    puVar5 = (undefined8 *)param_3;
  }
  if ((ulong)param_3 < 0x666666666666667) {
    uVar4 = (lVar2 >> 3) * -0x6666666666666666;
    if (uVar4 < (ulong)param_3 || uVar4 - param_3 == 0) {
      uVar4 = param_3;
    }
    if (0x333333333333332 < (ulong)((lVar2 >> 3) * -0x3333333333333333)) {
      uVar4 = 0x666666666666666;
    }
    if (uVar4 < 0x666666666666667) {
      local_58 = (undefined8 *)operator_new(uVar4 * 0x28);
      ppuStack_78 = &local_60;
      *(undefined8 **)this = local_58;
      *(undefined8 **)(this + 8) = local_58;
      *(undefined8 **)(this + 0x10) = local_58 + uVar4 * 5;
      local_70 = &local_58;
      local_68 = 0;
      local_60 = local_58;
      if (param_1 != param_2) {
        do {
          uVar1 = *(undefined4 *)((long)param_1 + 8);
          uVar3 = *(undefined8 *)param_1;
          local_58[3] = 0;
          local_58[4] = 0;
          *(undefined4 *)(local_58 + 1) = uVar1;
          *local_58 = uVar3;
          local_58[2] = 0;
                    /* try { // try from 0011766c to 0011766f has its CatchHandler @ 00117838 */
          __init_with_size_abi_ne180000_<LeicaRange*,LeicaRange*>
                    ((vector<LeicaRange,std::__ndk1::allocator<LeicaRange>> *)(local_58 + 2),
                     *(LeicaRange **)((long)param_1 + 0x10),*(LeicaRange **)((long)param_1 + 0x18),
                     ((long)*(LeicaRange **)((long)param_1 + 0x18) -
                      (long)*(LeicaRange **)((long)param_1 + 0x10) >> 3) * -0x3333333333333333);
          param_1 = (LeicaRange *)((long)param_1 + 0x28);
          local_58 = local_58 + 5;
        } while (param_1 != param_2);
      }
      *(undefined8 **)(this + 8) = local_58;
      return;
    }
  }
  uVar3 = __throw_length_error_abi_ne180000_();
                    /* catch() { ... } // from try @ 001177c0 with catch @ 00117834 */
                    /* catch() { ... } // from try @ 0011766c with catch @ 00117838 */
  __exception_guard_exceptions<std::__ndk1::_AllocatorDestroyRangeReverse<std::__ndk1::allocator<LeicaRange>,LeicaRange*>>
  ::~__exception_guard_exceptions_abi_ne180000_
            ((__exception_guard_exceptions<std::__ndk1::_AllocatorDestroyRangeReverse<std::__ndk1::allocator<LeicaRange>,LeicaRange*>>
              *)&local_80);
  *(undefined8 **)(this + 8) = puVar5;
                    /* WARNING: Subroutine does not return */
  _Unwind_Resume(uVar3);
}



/* 00117850 guide */

/* raw_fusion::guide(unsigned short const*, int, int, std::__ndk1::array<float, 14ul> const&, float)
    */

void __thiscall
raw_fusion::guide(raw_fusion *this,ushort *param_1,int param_2,int param_3,array *param_4,
                 float param_5)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  void *pvVar22;
  undefined8 uVar23;
  int iVar24;
  float *pfVar25;
  uint uVar26;
  void **in_x8;
  int iVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  int iVar31;
  long lVar32;
  ulong uVar33;
  ulong uVar34;
  float fVar35;
  float fVar36;
  float fVar37;
  float fVar38;
  float fVar39;
  float fVar40;
  float fVar41;
  float fVar42;
  
  pfVar25 = (float *)(ulong)(uint)param_3;
  iVar24 = (int)param_1;
  iVar29 = iVar24 + 3;
  if (-1 < iVar24) {
    iVar29 = iVar24;
  }
  iVar4 = param_2 + 3;
  if (-1 < param_2) {
    iVar4 = param_2;
  }
  uVar3 = iVar29 >> 2;
  *in_x8 = (void *)0x0;
  in_x8[1] = (void *)0x0;
  iVar29 = (iVar4 >> 2) * uVar3;
  in_x8[2] = (void *)0x0;
  if (iVar29 == 0) {
    pvVar22 = (void *)0x0;
  }
  else {
    if (iVar29 < 0) {
                    /* try { // try from 00117b40 to 00117b47 has its CatchHandler @ 00117b48 */
      uVar23 = std::__ndk1::vector<float,std::__ndk1::allocator<float>>::
               __throw_length_error_abi_ne180000_();
                    /* catch() { ... } // from try @ 001178c4 with catch @ 00117b48
                       catch() { ... } // from try @ 00117b40 with catch @ 00117b48 */
      pvVar22 = *in_x8;
      if (pvVar22 != (void *)0x0) {
        in_x8[1] = pvVar22;
        operator_delete(pvVar22);
      }
                    /* WARNING: Subroutine does not return */
      _Unwind_Resume(uVar23);
    }
    uVar34 = (long)iVar29 * 4;
                    /* try { // try from 001178c4 to 001178cb has its CatchHandler @ 00117b48 */
    pvVar22 = operator_new(uVar34);
    *in_x8 = pvVar22;
    in_x8[2] = (void *)((long)pvVar22 + (long)iVar29 * 4);
    memset(pvVar22,0,uVar34);
    in_x8[1] = (void *)((long)pvVar22 + uVar34);
  }
  if (3 < param_2) {
    fVar42 = *pfVar25;
    fVar35 = pfVar25[1];
    fVar36 = pfVar25[2];
    fVar37 = pfVar25[3];
    fVar38 = pfVar25[4];
    iVar28 = iVar24 * 2;
    fVar39 = fVar42 - fVar35;
    iVar5 = iVar24 * 4;
    uVar26 = 0;
    fVar40 = fVar42 - fVar36;
    fVar41 = fVar42 - fVar37;
    fVar42 = fVar42 - fVar38;
    iVar27 = 0;
    uVar34 = 0;
    iVar29 = iVar24 * 3;
    iVar30 = iVar24;
    do {
      if (3 < iVar24) {
        lVar32 = 0;
        uVar33 = (ulong)uVar3;
        do {
          iVar31 = (int)lVar32;
          iVar1 = iVar27 + iVar31;
          uVar33 = uVar33 - 1;
          fVar6 = (float)NEON_ucvtf((uint)*(ushort *)(this + (long)iVar1 * 2));
          fVar7 = (float)NEON_ucvtf((uint)*(ushort *)(this + (long)(iVar1 + 1) * 2));
          iVar2 = iVar30 + iVar31;
          fVar8 = (float)NEON_ucvtf((uint)*(ushort *)(this + (long)(iVar1 + 2) * 2));
          fVar10 = (float)NEON_ucvtf((uint)*(ushort *)(this + (long)(iVar1 + 3) * 2));
          fVar12 = (float)NEON_ucvtf((uint)*(ushort *)(this + (long)iVar2 * 2));
          fVar14 = (float)NEON_ucvtf((uint)*(ushort *)(this + (long)(iVar2 + 1) * 2));
          iVar1 = iVar28 + iVar31;
          fVar16 = (float)NEON_ucvtf((uint)*(ushort *)(this + (long)(iVar2 + 2) * 2));
          fVar17 = (float)NEON_ucvtf((uint)*(ushort *)(this + (long)(iVar2 + 3) * 2));
          fVar18 = (float)NEON_ucvtf((uint)*(ushort *)(this + (long)iVar1 * 2));
          fVar19 = (float)NEON_ucvtf((uint)*(ushort *)(this + (long)(iVar1 + 1) * 2));
          iVar31 = iVar29 + iVar31;
          fVar21 = (float)NEON_ucvtf((uint)*(ushort *)(this + (long)(iVar1 + 3) * 2));
          fVar20 = (float)NEON_ucvtf((uint)*(ushort *)(this + (long)(iVar1 + 2) * 2));
          fVar11 = (float)NEON_ucvtf((uint)*(ushort *)(this + (long)(iVar31 + 1) * 2));
          fVar13 = (float)NEON_ucvtf((uint)*(ushort *)(this + (long)(iVar31 + 2) * 2));
          fVar9 = (float)NEON_ucvtf((uint)*(ushort *)(this + (long)iVar31 * 2));
          fVar15 = (float)NEON_ucvtf((uint)*(ushort *)(this + (long)(iVar31 + 3) * 2));
          *(float *)((long)pvVar22 + lVar32 + (ulong)uVar26 * 4) =
               ((fVar6 - fVar35) / fVar39 + 0.0 + (fVar7 - fVar36) / fVar40 +
                (fVar8 - fVar35) / fVar39 + (fVar10 - fVar36) / fVar40 + (fVar12 - fVar37) / fVar41
                + (fVar14 - fVar38) / fVar42 + (fVar16 - fVar37) / fVar41 +
                (fVar17 - fVar38) / fVar42 + (fVar18 - fVar35) / fVar39 + (fVar19 - fVar36) / fVar40
                + (fVar20 - fVar35) / fVar39 + (fVar21 - fVar36) / fVar40 +
                (fVar9 - fVar37) / fVar41 + (fVar11 - fVar38) / fVar42 + (fVar13 - fVar37) / fVar41
               + (fVar15 - fVar38) / fVar42) * param_5 * 0.0625;
          lVar32 = lVar32 + 4;
        } while (uVar33 != 0);
      }
      uVar34 = uVar34 + 1;
      iVar29 = iVar29 + iVar5;
      iVar28 = iVar28 + iVar5;
      iVar30 = iVar30 + iVar5;
      iVar27 = iVar27 + iVar5;
      uVar26 = uVar26 + uVar3;
    } while (uVar34 != (uint)(iVar4 >> 2));
  }
  return;
}



/* 00117b68 __throw_length_error[abi:ne180000] */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* std::__ndk1::vector<std::__ndk1::array<float, 2ul>,
   std::__ndk1::allocator<std::__ndk1::array<float, 2ul> > >::__throw_length_error[abi:ne180000]()
   const */

void std::__ndk1::
     vector<std::__ndk1::array<float,2ul>,std::__ndk1::allocator<std::__ndk1::array<float,2ul>>>::
     __throw_length_error_abi_ne180000_(void)

{
                    /* WARNING: Subroutine does not return */
  __ndk1::__throw_length_error_abi_ne180000_("vector");
}



/* 00117b7c __append */

/* std::__ndk1::vector<float, std::__ndk1::allocator<float> >::__append(unsigned long) */

void __thiscall
std::__ndk1::vector<float,std::__ndk1::allocator<float>>::__append
          (vector<float,std::__ndk1::allocator<float>> *this,ulong param_1)

{
  undefined4 *puVar1;
  undefined8 *puVar2;
  void *pvVar3;
  ulong uVar4;
  ulong uVar5;
  undefined4 *__s;
  ulong uVar6;
  ulong uVar7;
  undefined8 *puVar8;
  undefined8 *puVar9;
  undefined4 *__s_00;
  undefined4 *puVar10;
  long lVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  
  __s_00 = *(undefined4 **)(this + 8);
  if (param_1 <= (ulong)(*(long *)(this + 0x10) - (long)__s_00 >> 2)) {
    if (param_1 != 0) {
      memset(__s_00,0,param_1 * 4);
      __s_00 = __s_00 + param_1;
    }
    *(undefined4 **)(this + 8) = __s_00;
    return;
  }
  puVar10 = *(undefined4 **)this;
  lVar11 = (long)__s_00 - (long)puVar10 >> 2;
  uVar5 = lVar11 + param_1;
  if (uVar5 >> 0x3e != 0) {
    __throw_length_error_abi_ne180000_();
LAB_00117d2c:
                    /* WARNING: Subroutine does not return */
    __throw_bad_array_new_length_abi_ne180000_();
  }
  uVar4 = *(long *)(this + 0x10) - (long)puVar10;
  uVar6 = (long)uVar4 >> 1;
  if (uVar6 <= uVar5) {
    uVar6 = uVar5;
  }
  if (0x7ffffffffffffffb < uVar4) {
    uVar6 = 0x3fffffffffffffff;
  }
  if (uVar6 == 0) {
    pvVar3 = (void *)0x0;
  }
  else {
    if (uVar6 >> 0x3e != 0) goto LAB_00117d2c;
    pvVar3 = operator_new(uVar6 << 2);
  }
  __s = (undefined4 *)((long)pvVar3 + lVar11 * 4);
  memset(__s,0,param_1 * 4);
  puVar1 = __s + param_1;
  if ((long)__s_00 - (long)puVar10 != 0) {
    uVar5 = ((long)__s_00 - (long)puVar10) - 4;
    if ((0x1b < uVar5) &&
       (0x1f < (ulong)((long)__s_00 + (-((long)__s_00 - (long)puVar10) - (long)pvVar3)))) {
      puVar8 = (undefined8 *)(__s + -4);
      puVar9 = (undefined8 *)(__s_00 + -4);
      uVar5 = (uVar5 >> 2) + 1;
      uVar7 = uVar5 & 0x7ffffffffffffff8;
      __s_00 = __s_00 + -uVar7;
      __s = __s + -uVar7;
      uVar4 = uVar7;
      do {
        puVar2 = puVar9 + -1;
        uVar14 = puVar9[-2];
        uVar13 = puVar9[1];
        uVar12 = *puVar9;
        uVar4 = uVar4 - 8;
        puVar9 = puVar9 + -4;
        puVar8[-1] = *puVar2;
        puVar8[-2] = uVar14;
        puVar8[1] = uVar13;
        *puVar8 = uVar12;
        puVar8 = puVar8 + -4;
      } while (uVar4 != 0);
      if (uVar5 == uVar7) goto LAB_00117cdc;
    }
    do {
      __s_00 = __s_00 + -1;
      __s = __s + -1;
      *__s = *__s_00;
    } while (__s_00 != puVar10);
  }
LAB_00117cdc:
  *(undefined4 **)this = __s;
  *(undefined4 **)(this + 8) = puVar1;
  *(void **)(this + 0x10) = (void *)((long)pvVar3 + uVar6 * 4);
  if (puVar10 == (undefined4 *)0x0) {
    return;
  }
  operator_delete(puVar10);
  return;
}



/* 00117d30 __throw_length_error[abi:ne180000] */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* std::__ndk1::vector<unsigned short, std::__ndk1::allocator<unsigned short>
   >::__throw_length_error[abi:ne180000]() const */

void std::__ndk1::vector<unsigned_short,std::__ndk1::allocator<unsigned_short>>::
     __throw_length_error_abi_ne180000_(void)

{
                    /* WARNING: Subroutine does not return */
  __ndk1::__throw_length_error_abi_ne180000_("vector");
}



/* 00117d44 ~__exception_guard_exceptions[abi:ne180000] */

/* std::__ndk1::__exception_guard_exceptions<std::__ndk1::vector<std::__ndk1::vector<unsigned short,
   std::__ndk1::allocator<unsigned short> >, std::__ndk1::allocator<std::__ndk1::vector<unsigned
   short, std::__ndk1::allocator<unsigned short> > >
   >::__destroy_vector>::~__exception_guard_exceptions[abi:ne180000]() */

void __thiscall
std::__ndk1::
__exception_guard_exceptions<std::__ndk1::vector<std::__ndk1::vector<unsigned_short,std::__ndk1::allocator<unsigned_short>>,std::__ndk1::allocator<std::__ndk1::vector<unsigned_short,std::__ndk1::allocator<unsigned_short>>>>::__destroy_vector>
::~__exception_guard_exceptions_abi_ne180000_
          (__exception_guard_exceptions<std::__ndk1::vector<std::__ndk1::vector<unsigned_short,std::__ndk1::allocator<unsigned_short>>,std::__ndk1::allocator<std::__ndk1::vector<unsigned_short,std::__ndk1::allocator<unsigned_short>>>>::__destroy_vector>
           *this)

{
  void *pvVar1;
  void **ppvVar2;
  void **ppvVar3;
  undefined8 *puVar4;
  void **ppvVar5;
  
  if (this[8] ==
      (__exception_guard_exceptions<std::__ndk1::vector<std::__ndk1::vector<unsigned_short,std::__ndk1::allocator<unsigned_short>>,std::__ndk1::allocator<std::__ndk1::vector<unsigned_short,std::__ndk1::allocator<unsigned_short>>>>::__destroy_vector>
       )0x0) {
    puVar4 = *(undefined8 **)this;
    ppvVar5 = (void **)*puVar4;
    if (ppvVar5 != (void **)0x0) {
      ppvVar3 = (void **)puVar4[1];
      ppvVar2 = ppvVar5;
      if (ppvVar3 != ppvVar5) {
        do {
          ppvVar2 = ppvVar3 + -3;
          pvVar1 = *ppvVar2;
          if (pvVar1 != (void *)0x0) {
            ppvVar3[-2] = pvVar1;
            operator_delete(pvVar1);
          }
          ppvVar3 = ppvVar2;
        } while (ppvVar2 != ppvVar5);
        ppvVar2 = (void **)**(undefined8 **)this;
      }
      puVar4[1] = ppvVar5;
      operator_delete(ppvVar2);
      return;
    }
  }
  return;
}



/* 00117dd0 __append */

/* std::__ndk1::vector<unsigned short, std::__ndk1::allocator<unsigned short> >::__append(unsigned
   long) */

void __thiscall
std::__ndk1::vector<unsigned_short,std::__ndk1::allocator<unsigned_short>>::__append
          (vector<unsigned_short,std::__ndk1::allocator<unsigned_short>> *this,ulong param_1)

{
  undefined2 *puVar1;
  ulong uVar2;
  undefined8 *puVar3;
  void *pvVar4;
  ulong uVar5;
  ulong uVar6;
  undefined2 *__s;
  ulong uVar7;
  undefined8 *puVar8;
  undefined8 *puVar9;
  undefined2 *__s_00;
  undefined2 *puVar10;
  long lVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  
  __s_00 = *(undefined2 **)(this + 8);
  if (param_1 <= (ulong)(*(long *)(this + 0x10) - (long)__s_00 >> 1)) {
    if (param_1 != 0) {
      memset(__s_00,0,param_1 * 2);
      __s_00 = __s_00 + param_1;
    }
    *(undefined2 **)(this + 8) = __s_00;
    return;
  }
  puVar10 = *(undefined2 **)this;
  lVar11 = (long)__s_00 - (long)puVar10 >> 1;
  uVar6 = lVar11 + param_1;
  if ((long)uVar6 < 0) {
    __throw_length_error_abi_ne180000_();
LAB_00117f74:
                    /* WARNING: Subroutine does not return */
    __throw_bad_array_new_length_abi_ne180000_();
  }
  uVar5 = *(long *)(this + 0x10) - (long)puVar10;
  uVar2 = uVar5;
  if (uVar5 <= uVar6) {
    uVar2 = uVar6;
  }
  if (0x7ffffffffffffffd < uVar5) {
    uVar2 = 0x7fffffffffffffff;
  }
  if (uVar2 == 0) {
    pvVar4 = (void *)0x0;
  }
  else {
    if ((long)uVar2 < 0) goto LAB_00117f74;
    pvVar4 = operator_new(uVar2 << 1);
  }
  __s = (undefined2 *)((long)pvVar4 + lVar11 * 2);
  memset(__s,0,param_1 * 2);
  puVar1 = __s + param_1;
  if ((long)__s_00 - (long)puVar10 != 0) {
    uVar6 = ((long)__s_00 - (long)puVar10) - 2;
    if ((0x1d < uVar6) &&
       (0x1f < (ulong)((long)__s_00 + (-((long)__s_00 - (long)puVar10) - (long)pvVar4)))) {
      puVar8 = (undefined8 *)(__s + -8);
      puVar9 = (undefined8 *)(__s_00 + -8);
      uVar6 = (uVar6 >> 1) + 1;
      uVar7 = uVar6 & 0xfffffffffffffff0;
      __s_00 = __s_00 + -uVar7;
      __s = __s + -uVar7;
      uVar5 = uVar7;
      do {
        puVar3 = puVar9 + -1;
        uVar14 = puVar9[-2];
        uVar13 = puVar9[1];
        uVar12 = *puVar9;
        uVar5 = uVar5 - 0x10;
        puVar9 = puVar9 + -4;
        puVar8[-1] = *puVar3;
        puVar8[-2] = uVar14;
        puVar8[1] = uVar13;
        *puVar8 = uVar12;
        puVar8 = puVar8 + -4;
      } while (uVar5 != 0);
      if (uVar6 == uVar7) goto LAB_00117f24;
    }
    do {
      __s_00 = __s_00 + -1;
      __s = __s + -1;
      *__s = *__s_00;
    } while (__s_00 != puVar10);
  }
LAB_00117f24:
  *(undefined2 **)this = __s;
  *(undefined2 **)(this + 8) = puVar1;
  *(void **)(this + 0x10) = (void *)((long)pvVar4 + uVar2 * 2);
  if (puVar10 == (undefined2 *)0x0) {
    return;
  }
  operator_delete(puVar10);
  return;
}



/* 00117f78 __throw_length_error[abi:ne180000] */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* std::__ndk1::vector<unsigned short const*, std::__ndk1::allocator<unsigned short const*>
   >::__throw_length_error[abi:ne180000]() const */

void std::__ndk1::vector<unsigned_short_const*,std::__ndk1::allocator<unsigned_short_const*>>::
     __throw_length_error_abi_ne180000_(void)

{
                    /* WARNING: Subroutine does not return */
  __ndk1::__throw_length_error_abi_ne180000_("vector");
}



/* 00117f8c _Unwind_RaiseException */

undefined8 _Unwind_RaiseException(undefined8 *param_1)

{
  int iVar1;
  undefined8 uVar2;
  undefined auStack_4f0 [624];
  undefined auStack_280 [528];
  undefined8 local_70;
  undefined auStack_68 [24];
  code *local_50;
  
  unw_getcontext(auStack_280);
  param_1[2] = 0;
  param_1[3] = 0;
  unw_init_local(auStack_4f0,auStack_280);
  iVar1 = unw_step(auStack_4f0);
  while( true ) {
    if (iVar1 == 0) {
      return 5;
    }
    if ((iVar1 < 0) || (iVar1 = unw_get_proc_info(auStack_4f0,auStack_68), iVar1 != 0)) break;
    if ((local_50 != (code *)0x0) &&
       (iVar1 = (*local_50)(1,1,*param_1,param_1,auStack_4f0), iVar1 != 8)) {
      if (iVar1 != 6) {
        return 3;
      }
      unw_get_reg(auStack_4f0,0xfffffffe,&local_70);
      param_1[3] = local_70;
      uVar2 = unwind_phase2(auStack_280,auStack_4f0,param_1);
      return uVar2;
    }
    iVar1 = unw_step(auStack_4f0);
  }
  return 3;
}


