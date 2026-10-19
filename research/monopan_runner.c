/* Image base: 00100000 */

/* 00104c44 __atexit_handler_wrapper */

void __atexit_handler_wrapper(code *UNRECOVERED_JUMPTABLE)

{
  if (UNRECOVERED_JUMPTABLE != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00104c50. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE)();
    return;
  }
  return;
}



/* 00104c58 atexit */

int atexit(__func *__func)

{
  int iVar1;
  
  iVar1 = __cxa_atexit(__atexit_handler_wrapper,__func,&__dso_handle);
  return iVar1;
}



/* 00104c74 pthread_atfork */

int pthread_atfork(__prepare *__prepare,__parent *__parent,__child *__child)

{
  int iVar1;
  
  iVar1 = __register_atfork((int)__prepare,__parent,__child,&__dso_handle);
  return iVar1;
}



/* 00104c84 call_fini_array */

void call_fini_array(void)

{
  long lVar1;
  undefined *puVar2;
  long lVar3;
  
  puVar2 = PTR__start_00109420;
  if ((long)PTR__start_00109428 - (long)PTR__start_00109420 != 0) {
    lVar3 = (long)PTR__start_00109428 - (long)PTR__start_00109420 >> 3;
    do {
      lVar1 = lVar3 * 8;
      lVar3 = lVar3 + -1;
      (**(code **)(puVar2 + lVar1 + -8))();
    } while (lVar3 != 0);
  }
  return;
}



/* 00104cd8 main */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 main(int param_1,long param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  void *__ptr;
  void *__ptr_00;
  FILE *pFVar5;
  size_t sVar6;
  long lVar7;
  code *pcVar8;
  code *pcVar9;
  code *pcVar10;
  undefined8 uVar11;
  undefined4 uVar12;
  ulong __n;
  ulong __size;
  long local_1f8;
  undefined8 local_1f0;
  undefined8 uStack_1e8;
  undefined8 uStack_1e0;
  undefined8 uStack_1d8;
  undefined8 local_1d0;
  undefined8 uStack_1c8;
  ulong uStack_1c0;
  undefined8 uStack_1b8;
  void *local_1b0;
  void *pvStack_1a8;
  undefined8 uStack_1a0;
  undefined8 uStack_198;
  undefined8 local_190;
  undefined8 uStack_188;
  undefined4 local_180;
  uint uStack_17c;
  uint uStack_178;
  undefined4 uStack_174;
  uint local_170;
  uint uStack_16c;
  undefined8 uStack_168;
  uint local_160;
  uint uStack_15c;
  undefined8 uStack_158;
  undefined4 local_150;
  uint uStack_14c;
  undefined8 local_148;
  void *local_140;
  void *pvStack_138;
  undefined8 uStack_130;
  undefined8 local_128;
  undefined8 local_120;
  undefined8 uStack_118;
  undefined8 local_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 uStack_f8;
  undefined8 local_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 local_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 local_70;
  
  if (param_1 == 6) {
    uVar2 = atoi(*(char **)(param_2 + 0x20));
    uVar3 = atoi(*(char **)(param_2 + 0x28));
    uVar12 = 2;
    if (((((uVar2 & 1) == 0) && (uVar2 - 1 >> 0xe == 0)) && (0 < (int)uVar3)) &&
       ((((int)uVar3 < 0x4001 && ((uVar3 & 1) == 0)) &&
        (__n = (ulong)uVar3 * (ulong)uVar2, __n < 0x3d09001)))) {
      __size = __n * 3 >> 1;
      __ptr = malloc(__size);
      __ptr_00 = calloc(1,__size);
      uVar12 = 3;
      if ((__ptr != (void *)0x0) && (__ptr_00 != (void *)0x0)) {
        pFVar5 = fopen(*(char **)(param_2 + 0x10),"rb");
        if (pFVar5 == (FILE *)0x0) {
          uVar12 = 4;
        }
        else {
          sVar6 = fread(__ptr,1,__size,pFVar5);
          fclose(pFVar5);
          if (sVar6 == __size) {
            lVar7 = load_vendor(*(undefined8 *)(param_2 + 8));
            if (lVar7 == 0) {
              pFVar5 = *(FILE **)PTR_stderr_00109438;
              uVar11 = dlerror();
              fprintf(pFVar5,"Monopan: %s\n",uVar11);
              uVar12 = 6;
            }
            else {
              pcVar8 = (code *)dlsym(lVar7,"MonopanInit");
              pcVar9 = (code *)dlsym(lVar7,"MonopanProcess");
              pcVar10 = (code *)dlsym(lVar7,"MonopanDeinit");
              uVar12 = 7;
              if (((pcVar8 != (code *)0x0) && (pcVar9 != (code *)0x0)) && (pcVar10 != (code *)0x0))
              {
                local_180 = 0x7d1;
                uStack_88 = _UNK_00100a50;
                local_90 = _DAT_00100a48;
                uStack_78 = _UNK_00100a60;
                uStack_80 = _DAT_00100a58;
                uStack_174 = 2;
                uStack_15c = uVar3 >> 1;
                uStack_168 = 0;
                uStack_c8 = _UNK_00100a10;
                local_d0 = _DAT_00100a08;
                uStack_b8 = _UNK_00100a20;
                uStack_c0 = _DAT_00100a18;
                uVar1 = (uint)(__n >> 1);
                uStack_14c = uVar1 & 0x7fffffff;
                uStack_158 = 0;
                uStack_a8 = _UNK_00100a30;
                local_b0 = _DAT_00100a28;
                uStack_98 = _UNK_00100a40;
                uStack_a0 = _DAT_00100a38;
                local_150 = (undefined4)__n;
                pvStack_138 = (void *)((long)__ptr + __n);
                uStack_130 = 0;
                uStack_108 = _UNK_001009d0;
                local_110 = _DAT_001009c8;
                uStack_f8 = _UNK_001009e0;
                uStack_100 = _DAT_001009d8;
                local_148 = 0;
                local_128 = 0;
                local_120 = 0xffffffffffffffff;
                uStack_118 = 0xffffffffffffffff;
                uStack_e8 = _UNK_001009f0;
                local_f0 = _DAT_001009e8;
                uStack_d8 = _UNK_00100a00;
                uStack_e0 = _DAT_001009f8;
                local_70 = DAT_00100a68;
                pvStack_1a8 = (void *)((long)__ptr_00 + __n);
                uStack_188 = 0xffffffffffffffff;
                local_190 = 0xffffffffffffffff;
                local_1d0 = CONCAT44(uStack_15c,uVar3);
                uStack_1c0 = CONCAT44(uVar1,local_150) & 0x7fffffffffffffff;
                uStack_198 = 0;
                uStack_1a0 = 0;
                uStack_1e8 = CONCAT44(2,uVar3);
                local_1f0 = CONCAT44(uVar2,0x7d1);
                uStack_1e0 = CONCAT44(uVar2,uVar2);
                uStack_1d8 = 0;
                uStack_1c8 = 0;
                uStack_1b8 = 0;
                local_1b0 = __ptr_00;
                uStack_17c = uVar2;
                uStack_178 = uVar3;
                local_170 = uVar2;
                uStack_16c = uVar2;
                local_160 = uVar3;
                local_140 = __ptr;
                local_1f8 = (*pcVar8)(&local_110);
                if (local_1f8 == 0) {
                  uVar12 = 8;
                }
                else {
                  uVar2 = (*pcVar9)(local_1f8,&local_180,&local_1f0);
                  fprintf(*(FILE **)PTR_stderr_00109438,"MonopanProcess result=%d\n",(ulong)uVar2);
                  (*pcVar10)(&local_1f8);
                  if (uVar2 == 0) {
                    pFVar5 = fopen(*(char **)(param_2 + 0x18),"wb");
                    if (pFVar5 == (FILE *)0x0) {
                      uVar12 = 10;
                    }
                    else {
                      sVar6 = fwrite(__ptr_00,1,__n,pFVar5);
                      iVar4 = fclose(pFVar5);
                      free(__ptr);
                      free(__ptr_00);
                      uVar12 = 0;
                      if (iVar4 != 0 || sVar6 != __n) {
                        uVar12 = 0xb;
                      }
                    }
                  }
                  else {
                    uVar12 = 9;
                  }
                }
              }
            }
          }
          else {
            uVar12 = 5;
          }
        }
      }
    }
    return uVar12;
  }
  return 1;
}



/* 00105008 load_vendor */

undefined8 load_vendor(char *param_1)

{
  undefined8 uVar1;
  long lVar2;
  code *pcVar3;
  size_t sVar4;
  undefined8 *puVar5;
  undefined8 uVar6;
  FILE *__stream;
  char acStack_1060 [4096];
  undefined8 local_60;
  undefined8 uStack_58;
  undefined8 local_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  long local_38;
  
  lVar2 = dlopen("libdl_android.so",2);
  if (lVar2 == 0) {
    uStack_48 = 0;
    local_50 = 0;
    local_38 = 0;
    uStack_40 = 0;
    uStack_58 = 0;
    local_60 = 0;
  }
  else {
    pcVar3 = (code *)dlsym(lVar2,"android_get_exported_namespace");
    uStack_48 = 0;
    local_50 = 0;
    local_38 = 0;
    uStack_40 = 0;
    uStack_58 = 0;
    local_60 = 0;
    if ((pcVar3 != (code *)0x0) && (local_38 = (*pcVar3)("sphal"), local_38 != 0)) {
      local_60 = 0x200;
    }
  }
  sVar4 = strlen(param_1);
  if (sVar4 < 0x1000) {
    strcpy(acStack_1060,param_1);
    puVar5 = (undefined8 *)strrchr(acStack_1060,0x2f);
    uVar1 = s__libzx__shared_so_00100937._8_8_;
    uVar6 = s__libzx__shared_so_00100937._0_8_;
    if (puVar5 == (undefined8 *)0x0) {
      return 0;
    }
    if (0xffffffffffffeffe < (ulong)((long)puVar5 + (-0xfef - (long)acStack_1060))) {
      *(undefined2 *)(puVar5 + 2) = 0x6f;
      puVar5[1] = uVar1;
      *puVar5 = uVar6;
      lVar2 = android_dlopen_ext(acStack_1060,2,&local_60);
      if (lVar2 != 0) {
        uVar6 = android_dlopen_ext(param_1,2,&local_60);
        return uVar6;
      }
      __stream = *(FILE **)PTR_stderr_00109438;
      uVar6 = dlerror();
      fprintf(__stream,"Monopan C++: %s\n",uVar6);
      return 0;
    }
  }
  return 0;
}



/* 00105150 FUN_00105150 */

void FUN_00105150(void)

{
  (*(code *)PTR_00109450)();
  return;
}



/* 00105170 __libc_init */

void __libc_init(void)

{
  (*(code *)PTR___libc_init_00109458)();
  return;
}



/* 00105180 __cxa_atexit */

void __cxa_atexit(void)

{
  (*(code *)PTR___cxa_atexit_00109460)();
  return;
}



/* 00105190 __register_atfork */

void __register_atfork(void)

{
  (*(code *)PTR___register_atfork_00109468)();
  return;
}



/* 001051a0 atoi */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int atoi(char *__nptr)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_atoi_00109470)((int)__nptr);
  return iVar1;
}



/* 001051b0 malloc */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * malloc(size_t __size)

{
  void *pvVar1;
  
  pvVar1 = (void *)(*(code *)PTR_malloc_00109478)();
  return pvVar1;
}



/* 001051c0 calloc */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * calloc(size_t __nmemb,size_t __size)

{
  void *pvVar1;
  
  pvVar1 = (void *)(*(code *)PTR_calloc_00109480)();
  return pvVar1;
}



/* 001051d0 fopen */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

FILE * fopen(char *__filename,char *__modes)

{
  FILE *pFVar1;
  
  pFVar1 = (FILE *)(*(code *)PTR_fopen_00109488)();
  return pFVar1;
}



/* 001051e0 fread */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

size_t fread(void *__ptr,size_t __size,size_t __n,FILE *__stream)

{
  size_t sVar1;
  
  sVar1 = (*(code *)PTR_fread_00109490)();
  return sVar1;
}



/* 001051f0 fclose */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int fclose(FILE *__stream)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_fclose_00109498)((int)__stream);
  return iVar1;
}



/* 00105200 dlsym */

void dlsym(void)

{
  (*(code *)PTR_dlsym_001094a0)();
  return;
}



/* 00105210 dlerror */

void dlerror(void)

{
  (*(code *)PTR_dlerror_001094a8)();
  return;
}



/* 00105220 fprintf */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int fprintf(FILE *__stream,char *__format,...)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_fprintf_001094b0)((int)__stream);
  return iVar1;
}



/* 00105230 fwrite */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

size_t fwrite(void *__ptr,size_t __size,size_t __n,FILE *__s)

{
  size_t sVar1;
  
  sVar1 = (*(code *)PTR_fwrite_001094b8)();
  return sVar1;
}



/* 00105240 free */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void free(void *__ptr)

{
  (*(code *)PTR_free_001094c0)();
  return;
}



/* 00105250 dlopen */

void dlopen(void)

{
  (*(code *)PTR_dlopen_001094c8)();
  return;
}



/* 00105260 strlen */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

size_t strlen(char *__s)

{
  size_t sVar1;
  
  sVar1 = (*(code *)PTR_strlen_001094d0)();
  return sVar1;
}



/* 00105270 strcpy */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * strcpy(char *__dest,char *__src)

{
  char *pcVar1;
  
  pcVar1 = (char *)(*(code *)PTR_strcpy_001094d8)();
  return pcVar1;
}



/* 00105280 strrchr */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * strrchr(char *__s,int __c)

{
  char *pcVar1;
  
  pcVar1 = (char *)(*(code *)PTR_strrchr_001094e0)(__s,__c);
  return pcVar1;
}



/* 00105290 android_dlopen_ext */

void android_dlopen_ext(void)

{
  (*(code *)PTR_android_dlopen_ext_001094e8)();
  return;
}


