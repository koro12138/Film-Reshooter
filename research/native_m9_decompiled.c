/* Image base: 00100000 */

/* 001345b0 __on_dlclose */

void __on_dlclose(void)

{
  __cxa_finalize(&__dso_handle);
  return;
}



/* 001345c0 FUN_001345c0 */

void FUN_001345c0(void)

{
  return;
}



/* 001345c8 __on_dlclose_late */

void __on_dlclose_late(void)

{
  __emutls_unregister_key();
  return;
}



/* 001345d0 __atexit_handler_wrapper */

void __atexit_handler_wrapper(code *UNRECOVERED_JUMPTABLE)

{
  if (UNRECOVERED_JUMPTABLE != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x001345dc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE)();
    return;
  }
  return;
}



/* 001345e4 atexit */

int atexit(__func *__func)

{
  int iVar1;
  
  iVar1 = __cxa_atexit(__atexit_handler_wrapper,__func,&__dso_handle);
  return iVar1;
}



/* 00134600 pthread_atfork */

int pthread_atfork(__prepare *__prepare,__parent *__parent,__child *__child)

{
  int iVar1;
  
  iVar1 = __register_atfork((int)__prepare,__parent,__child,&__dso_handle);
  return iVar1;
}



/* 00134610 Java_com_codex_fullm9_NativeM9_outputDenoise */

void Java_com_codex_fullm9_NativeM9_outputDenoise
               (_JNIEnv *param_1,undefined8 param_2,_jobject *param_3,uint param_4)

{
  byte *pbVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte *pbVar4;
  byte *pbVar5;
  undefined *puVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  undefined auVar11 [16];
  undefined8 *puVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  bool bVar15;
  void *pvVar16;
  void *__s;
  runtime_error *this;
  uint uVar17;
  float *pfVar18;
  float *pfVar19;
  float *pfVar20;
  uint uVar21;
  undefined8 *puVar22;
  float *pfVar23;
  long lVar24;
  ulong uVar25;
  ulong uVar26;
  ulong uVar27;
  undefined8 *puVar28;
  ulong uVar29;
  int iVar30;
  uint uVar31;
  long lVar32;
  size_t __n;
  uint uVar33;
  float *pfVar34;
  float fVar35;
  float fVar36;
  float fVar37;
  undefined8 uVar38;
  float fVar39;
  undefined8 uVar40;
  undefined8 uVar41;
  float fVar42;
  float fVar43;
  float fVar44;
  float fVar45;
  float fVar46;
  float fVar47;
  float fVar48;
  float fVar49;
  float fVar50;
  float fVar51;
  undefined8 uVar52;
  float fVar53;
  float fVar54;
  float fVar55;
  undefined8 uVar56;
  float fVar57;
  float fVar58;
  undefined8 uVar59;
  float fVar60;
  float fVar61;
  float fVar62;
  float fVar63;
  undefined8 uVar64;
  float fVar65;
  float fVar66;
  float fVar67;
  float fVar68;
  float fVar69;
  float fVar70;
  float fVar71;
  float fVar72;
  float fVar73;
  float fVar74;
  float *local_128;
  float *local_120;
  float *local_118;
  float *local_110;
  float *local_108;
  float *local_100;
  float *local_f8;
  float *local_f0;
  float *local_e8;
  undefined8 local_e0;
  undefined8 uStack_d8;
  uint local_d0;
  uint local_cc;
  uint local_c8;
  void *local_b8;
  __less a_Stack_a9 [9];
  
  if (0xfffffff7 < param_4 - 9) {
                    /* try { // try from 0013464c to 0013465f has its CatchHandler @ 0013555c */
    Pixels::Pixels((Pixels *)&local_e0,param_1,param_3);
    if ((2 < (int)local_d0) && (2 < (int)local_cc)) {
      uVar33 = local_cc - 1;
      iVar30 = 1;
      local_f8 = (float *)0x0;
      local_f0 = (float *)0x0;
      local_e8 = (float *)0x0;
      local_110 = (float *)0x0;
      local_108 = (float *)0x0;
      local_100 = (float *)0x0;
      local_128 = (float *)0x0;
      local_120 = (float *)0x0;
      local_118 = (float *)0x0;
      uVar17 = (uint)SQRT(((double)local_d0 * (double)local_cc) / 16000.0);
      if ((int)uVar17 < 2) {
        uVar17 = 1;
      }
      do {
        lVar24 = 1;
        do {
          uVar31 = (int)lVar24 * 4;
          uVar25 = (ulong)uVar31;
          uVar10 = local_c8 * iVar30;
          pbVar3 = (byte *)((long)local_b8 + uVar25 + uVar10);
          pbVar1 = (byte *)((long)local_b8 + (long)(int)(uVar31 - 4) + (ulong)uVar10);
          pbVar2 = (byte *)((long)local_b8 + (long)(int)(uVar31 + 4) + (ulong)uVar10);
          fVar35 = (float)NEON_ucvtf((uint)*pbVar3);
          fVar36 = (float)NEON_ucvtf((uint)pbVar3[1]);
          fVar39 = (float)NEON_ucvtf((uint)*pbVar1);
          fVar42 = (float)NEON_ucvtf((uint)pbVar1[1]);
          fVar44 = (float)NEON_ucvtf((uint)pbVar3[2]);
          fVar47 = (float)NEON_ucvtf((uint)pbVar1[2]);
          fVar49 = (float)NEON_ucvtf((uint)*pbVar2);
          fVar50 = (float)NEON_ucvtf((uint)pbVar2[1]);
          pbVar4 = (byte *)((long)local_b8 + local_c8 * (iVar30 + -1) + uVar25);
          fVar53 = (float)NEON_ucvtf((uint)*pbVar4);
          fVar37 = (float)NEON_ucvtf((uint)pbVar4[1]);
          fVar43 = (float)NEON_ucvtf((uint)pbVar2[2]);
          pbVar5 = (byte *)((long)local_b8 + local_c8 * (iVar30 + 1) + uVar25);
          fVar45 = (float)NEON_ucvtf((uint)pbVar4[2]);
          fVar51 = (float)NEON_ucvtf((uint)*pbVar5);
          fVar48 = (float)NEON_ucvtf((uint)pbVar5[1]);
          fVar46 = (float)NEON_ucvtf((uint)pbVar5[2]);
          fVar35 = (((fVar35 * 0.2126 + fVar36 * 0.7152 + fVar44 * 0.0722) * 4.0 -
                    (fVar39 * 0.2126 + fVar42 * 0.7152 + fVar47 * 0.0722)) -
                   (fVar49 * 0.2126 + fVar50 * 0.7152 + fVar43 * 0.0722)) -
                   (fVar53 * 0.2126 + fVar37 * 0.7152 + fVar45 * 0.0722);
          fVar36 = fVar51 * 0.2126 + fVar48 * 0.7152 + fVar46 * 0.0722;
          fVar37 = ABS(fVar35 - fVar36);
          if (local_e8 <= local_f0) {
            lVar32 = (long)local_f0 - (long)local_f8 >> 2;
            uVar25 = lVar32 + 1;
            if (uVar25 >> 0x3e == 0) {
              uVar26 = (long)local_e8 - (long)local_f8 >> 1;
              if (uVar26 <= uVar25) {
                uVar26 = uVar25;
              }
              if (0x7ffffffffffffffb < (ulong)((long)local_e8 - (long)local_f8)) {
                uVar26 = 0x3fffffffffffffff;
              }
              if (uVar26 == 0) {
                pvVar16 = (void *)0x0;
                pfVar20 = (float *)(lVar32 * 4);
                lVar32 = (long)local_f0 - (long)local_f8;
                pfVar34 = pfVar20 + 1;
                *pfVar20 = fVar37;
                if (lVar32 != 0) goto LAB_0013490c;
LAB_00134c30:
                local_e8 = (float *)((long)pvVar16 + uVar26 * 4);
                pfVar18 = pfVar20;
              }
              else {
                if (uVar26 >> 0x3e != 0) {
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 001354dc to 001354df has its CatchHandler @ 001355a8 */
                  std::__throw_bad_array_new_length_abi_ne180000_();
                }
                    /* try { // try from 001348f4 to 001348f7 has its CatchHandler @ 001355a0 */
                pvVar16 = operator_new(uVar26 << 2);
                pfVar20 = (float *)((long)pvVar16 + lVar32 * 4);
                lVar32 = (long)local_f0 - (long)local_f8;
                pfVar34 = pfVar20 + 1;
                *pfVar20 = fVar37;
                if (lVar32 == 0) goto LAB_00134c30;
LAB_0013490c:
                pfVar18 = pfVar20;
                if ((lVar32 - 4U < 0x1c) ||
                   ((ulong)((long)local_f0 + (-((long)local_f0 - (long)local_f8) - (long)pvVar16)) <
                    0x20)) {
LAB_00134978:
                  do {
                    local_f0 = local_f0 + -1;
                    pfVar18 = pfVar18 + -1;
                    *pfVar18 = *local_f0;
                  } while (local_f0 != local_f8);
                }
                else {
                  puVar28 = (undefined8 *)(local_f0 + -4);
                  uVar25 = (lVar32 - 4U >> 2) + 1;
                  uVar27 = uVar25 & 0x7ffffffffffffff8;
                  local_f0 = local_f0 + -uVar27;
                  pfVar18 = pfVar20 + -uVar27;
                  puVar22 = (undefined8 *)(pfVar20 + -4);
                  uVar29 = uVar27;
                  do {
                    puVar12 = puVar28 + -1;
                    uVar38 = puVar28[-2];
                    uVar41 = puVar28[1];
                    uVar40 = *puVar28;
                    uVar29 = uVar29 - 8;
                    puVar28 = puVar28 + -4;
                    puVar22[-1] = *puVar12;
                    puVar22[-2] = uVar38;
                    puVar22[1] = uVar41;
                    *puVar22 = uVar40;
                    puVar22 = puVar22 + -4;
                  } while (uVar29 != 0);
                  if (uVar25 != uVar27) goto LAB_00134978;
                }
                local_e8 = (float *)((long)pvVar16 + uVar26 * 4);
              }
              if (local_f8 != (float *)0x0) {
                operator_delete(local_f8);
              }
              goto LAB_001349a0;
            }
LAB_001354c4:
                    /* try { // try from 001354c4 to 001354cb has its CatchHandler @ 001355a8 */
            std::__ndk1::vector<float,std::__ndk1::allocator<float>>::
            __throw_length_error_abi_ne180000_();
LAB_001354cc:
                    /* try { // try from 001354cc to 001354d3 has its CatchHandler @ 001355ac */
            std::__ndk1::vector<float,std::__ndk1::allocator<float>>::
            __throw_length_error_abi_ne180000_();
LAB_001354d4:
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 001354d4 to 001354d7 has its CatchHandler @ 001355b0 */
            std::__throw_bad_array_new_length_abi_ne180000_();
          }
          pfVar34 = local_f0 + 1;
          *local_f0 = fVar37;
          pfVar18 = local_f8;
LAB_001349a0:
          local_f8 = pfVar18;
          fVar35 = fVar35 - fVar36;
          fVar36 = ABS((float)((uint)*pbVar3 * 4 -
                              ((uint)*pbVar1 + (uint)*pbVar2 + (uint)*pbVar4 + (uint)*pbVar5)) -
                       fVar35);
          if (local_100 <= local_108) {
            lVar32 = (long)local_108 - (long)local_110 >> 2;
            uVar25 = lVar32 + 1;
            if (uVar25 >> 0x3e == 0) {
              uVar26 = (long)local_100 - (long)local_110 >> 1;
              if (uVar26 <= uVar25) {
                uVar26 = uVar25;
              }
              if (0x7ffffffffffffffb < (ulong)((long)local_100 - (long)local_110)) {
                uVar26 = 0x3fffffffffffffff;
              }
              if (uVar26 == 0) {
                pvVar16 = (void *)0x0;
                pfVar20 = (float *)(lVar32 * 4);
                lVar32 = (long)local_108 - (long)local_110;
                pfVar18 = pfVar20 + 1;
                *pfVar20 = fVar36;
                if (lVar32 != 0) goto LAB_00134a50;
LAB_00134c60:
                local_100 = (float *)((long)pvVar16 + uVar26 * 4);
              }
              else {
                if (uVar26 >> 0x3e != 0) {
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 001354d8 to 001354db has its CatchHandler @ 001355ac */
                  std::__throw_bad_array_new_length_abi_ne180000_();
                }
                    /* try { // try from 00134a38 to 00134a3b has its CatchHandler @ 001355a4 */
                pvVar16 = operator_new(uVar26 << 2);
                pfVar20 = (float *)((long)pvVar16 + lVar32 * 4);
                lVar32 = (long)local_108 - (long)local_110;
                pfVar18 = pfVar20 + 1;
                *pfVar20 = fVar36;
                if (lVar32 == 0) goto LAB_00134c60;
LAB_00134a50:
                pfVar19 = pfVar20;
                if ((lVar32 - 4U < 0x1c) ||
                   ((ulong)((long)local_108 + (-((long)local_108 - (long)local_110) - (long)pvVar16)
                           ) < 0x20)) {
LAB_00134abc:
                  do {
                    local_108 = local_108 + -1;
                    pfVar19 = pfVar19 + -1;
                    *pfVar19 = *local_108;
                  } while (local_108 != local_110);
                }
                else {
                  puVar28 = (undefined8 *)(local_108 + -4);
                  uVar25 = (lVar32 - 4U >> 2) + 1;
                  uVar27 = uVar25 & 0x7ffffffffffffff8;
                  local_108 = local_108 + -uVar27;
                  pfVar19 = pfVar20 + -uVar27;
                  puVar22 = (undefined8 *)(pfVar20 + -4);
                  uVar29 = uVar27;
                  do {
                    puVar12 = puVar28 + -1;
                    uVar38 = puVar28[-2];
                    uVar41 = puVar28[1];
                    uVar40 = *puVar28;
                    uVar29 = uVar29 - 8;
                    puVar28 = puVar28 + -4;
                    puVar22[-1] = *puVar12;
                    puVar22[-2] = uVar38;
                    puVar22[1] = uVar41;
                    *puVar22 = uVar40;
                    puVar22 = puVar22 + -4;
                  } while (uVar29 != 0);
                  if (uVar25 != uVar27) goto LAB_00134abc;
                }
                local_100 = (float *)((long)pvVar16 + uVar26 * 4);
                pfVar20 = pfVar19;
              }
              if (local_110 != (float *)0x0) {
                operator_delete(local_110);
              }
              goto LAB_00134ae4;
            }
            goto LAB_001354cc;
          }
          pfVar18 = local_108 + 1;
          *local_108 = fVar36;
          pfVar20 = local_110;
LAB_00134ae4:
          local_110 = pfVar20;
          fVar35 = ABS((float)((uint)pbVar3[2] * 4 -
                              ((uint)pbVar1[2] + (uint)pbVar2[2] + (uint)pbVar4[2] + (uint)pbVar5[2]
                              )) - fVar35);
          if (local_120 < local_118) {
            pfVar19 = local_120 + 1;
            *local_120 = fVar35;
            pfVar20 = local_128;
          }
          else {
            lVar32 = (long)local_120 - (long)local_128 >> 2;
            uVar25 = lVar32 + 1;
            if (uVar25 >> 0x3e != 0) {
                    /* try { // try from 001354bc to 001354c3 has its CatchHandler @ 001355b0 */
              std::__ndk1::vector<float,std::__ndk1::allocator<float>>::
              __throw_length_error_abi_ne180000_();
              goto LAB_001354c4;
            }
            uVar26 = (long)local_118 - (long)local_128 >> 1;
            if (uVar26 <= uVar25) {
              uVar26 = uVar25;
            }
            if (0x7ffffffffffffffb < (ulong)((long)local_118 - (long)local_128)) {
              uVar26 = 0x3fffffffffffffff;
            }
            if (uVar26 == 0) {
              pvVar16 = (void *)0x0;
              pfVar23 = (float *)(lVar32 * 4);
              lVar32 = (long)local_120 - (long)local_128;
              pfVar19 = pfVar23 + 1;
              *pfVar23 = fVar35;
              if (lVar32 != 0) goto LAB_00134b88;
LAB_00134c90:
              local_118 = (float *)((long)pvVar16 + uVar26 * 4);
              pfVar20 = pfVar23;
            }
            else {
              if (uVar26 >> 0x3e != 0) goto LAB_001354d4;
                    /* try { // try from 00134b70 to 00134b73 has its CatchHandler @ 0013559c */
              pvVar16 = operator_new(uVar26 << 2);
              pfVar23 = (float *)((long)pvVar16 + lVar32 * 4);
              lVar32 = (long)local_120 - (long)local_128;
              pfVar19 = pfVar23 + 1;
              *pfVar23 = fVar35;
              if (lVar32 == 0) goto LAB_00134c90;
LAB_00134b88:
              pfVar20 = pfVar23;
              if ((lVar32 - 4U < 0x1c) ||
                 ((ulong)((long)local_120 + (-((long)local_120 - (long)local_128) - (long)pvVar16))
                  < 0x20)) {
LAB_00134bf4:
                do {
                  local_120 = local_120 + -1;
                  pfVar20 = pfVar20 + -1;
                  *pfVar20 = *local_120;
                } while (local_120 != local_128);
              }
              else {
                puVar28 = (undefined8 *)(local_120 + -4);
                uVar25 = (lVar32 - 4U >> 2) + 1;
                uVar27 = uVar25 & 0x7ffffffffffffff8;
                local_120 = local_120 + -uVar27;
                pfVar20 = pfVar23 + -uVar27;
                puVar22 = (undefined8 *)(pfVar23 + -4);
                uVar29 = uVar27;
                do {
                  puVar12 = puVar28 + -1;
                  uVar38 = puVar28[-2];
                  uVar41 = puVar28[1];
                  uVar40 = *puVar28;
                  uVar29 = uVar29 - 8;
                  puVar28 = puVar28 + -4;
                  puVar22[-1] = *puVar12;
                  puVar22[-2] = uVar38;
                  puVar22[1] = uVar41;
                  *puVar22 = uVar40;
                  puVar22 = puVar22 + -4;
                } while (uVar29 != 0);
                if (uVar25 != uVar27) goto LAB_00134bf4;
              }
              local_118 = (float *)((long)pvVar16 + uVar26 * 4);
            }
            if (local_128 != (float *)0x0) {
              operator_delete(local_128);
            }
          }
          local_128 = pfVar20;
          lVar24 = lVar24 + (ulong)uVar17;
          local_120 = pfVar19;
          local_108 = pfVar18;
          local_f0 = pfVar34;
        } while (lVar24 < (long)(ulong)(local_d0 - 1));
        iVar30 = iVar30 + uVar17;
      } while (iVar30 < (int)uVar33);
      pfVar20 = local_f8 + ((long)pfVar34 - (long)local_f8 >> 3);
      if (pfVar20 != pfVar34) {
                    /* try { // try from 00134cc8 to 00134cd3 has its CatchHandler @ 00135554 */
        std::__ndk1::
        __nth_element_abi_ne180000_<std::__ndk1::_ClassicAlgPolicy,std::__ndk1::__less<void,void>&,std::__ndk1::__wrap_iter<float*>>
                  ((__wrap_iter)local_f8,(__wrap_iter)pfVar20,(__wrap_iter)pfVar34,a_Stack_a9);
      }
      fVar35 = *pfVar20;
      pfVar20 = local_110 + ((long)pfVar18 - (long)local_110 >> 3);
      if (pfVar20 != pfVar18) {
                    /* try { // try from 00134cf0 to 00134cfb has its CatchHandler @ 00135550 */
        std::__ndk1::
        __nth_element_abi_ne180000_<std::__ndk1::_ClassicAlgPolicy,std::__ndk1::__less<void,void>&,std::__ndk1::__wrap_iter<float*>>
                  ((__wrap_iter)local_110,(__wrap_iter)pfVar20,(__wrap_iter)pfVar18,a_Stack_a9);
      }
      fVar36 = *pfVar20;
      pfVar20 = local_128 + ((long)pfVar19 - (long)local_128 >> 3);
      if (pfVar20 != pfVar19) {
                    /* try { // try from 00134d18 to 00134d23 has its CatchHandler @ 0013554c */
        std::__ndk1::
        __nth_element_abi_ne180000_<std::__ndk1::_ClassicAlgPolicy,std::__ndk1::__less<void,void>&,std::__ndk1::__wrap_iter<float*>>
                  ((__wrap_iter)local_128,(__wrap_iter)pfVar20,(__wrap_iter)pfVar19,a_Stack_a9);
      }
      fVar39 = (float)NEON_fminnm(fVar35 / 3.016,0x41400000);
      fVar37 = (float)NEON_fminnm(*pfVar20 / 3.016,0x41400000);
      fVar35 = (fVar39 + -1.25) / 5.0;
      fVar36 = (float)NEON_fminnm(fVar36 / 3.016,0x41400000);
      uVar40 = NEON_fmov(0xbfa00000,4);
      uVar41 = NEON_fmov(0x40a00000,4);
      if (fVar35 <= 0.0) {
        fVar35 = 0.0;
      }
      fVar42 = (float)NEON_fminnm(fVar35 * 0.42,0x3ed70a3d);
      fVar35 = 0.0;
      if ((param_4 & 0xd) != 4) {
        fVar35 = fVar42;
      }
      uVar40 = NEON_fmaxnm(CONCAT44((fVar36 + (float)((ulong)uVar40 >> 0x20)) /
                                    (float)((ulong)uVar41 >> 0x20),
                                    (fVar37 + (float)uVar40) / (float)uVar41),0,4);
      fVar42 = 0.0;
      if ((param_4 & 0xb) != 1) {
        fVar42 = fVar35;
      }
      uVar40 = NEON_fminnm(CONCAT44((float)((ulong)uVar40 >> 0x20) * 0.6,(float)uVar40 * 0.6),
                           0x3f19999a3f19999a,4);
      if (((fVar42 != 0.0) || (uVar25 = NEON_fcmeq(uVar40,0,4), (uVar25 & 0x100000000) == 0)) ||
         ((uVar25 & 1) == 0)) {
        uVar25 = (long)(int)local_d0 * 0xc;
                    /* try { // try from 00134e14 to 00134e1b has its CatchHandler @ 00135548 */
        __s = operator_new(uVar25);
        memset(__s,0,uVar25);
        pvVar16 = local_b8;
        __n = (long)(int)local_d0 * 4;
        memmove(__s,local_b8,__n);
        uVar17 = local_c8;
        uVar25 = (ulong)local_c8;
        memmove((void *)((long)__s + __n),(void *)((long)pvVar16 + uVar25),__n);
        uVar14 = DAT_00119b20;
        uVar13 = DAT_00119b18;
        uVar38 = DAT_00119b10;
        uVar41 = DAT_00119ae8;
        if (0 < (int)local_cc) {
          if ((int)local_d0 < 1) {
            uVar33 = 0;
            uVar26 = 1;
            do {
              uVar33 = uVar33 + 1;
              if ((int)uVar33 < (int)local_cc) {
                auVar11._8_8_ = 0;
                auVar11._0_8_ = uVar26;
                memmove((void *)((long)__s +
                                __n * (uVar26 - (uVar26 / 3 +
                                                (SUB168(auVar11 * ZEXT816(0xaaaaaaaaaaaaaaab),8) &
                                                0xfffffffffffffffe)))),
                        (void *)((long)pvVar16 + uVar25),__n);
              }
              uVar26 = uVar26 + 1;
              uVar25 = (ulong)((int)uVar25 + uVar17);
            } while (local_cc != uVar33);
          }
          else {
            fVar36 = fVar36 * 2.5;
            fVar35 = fVar39 * 2.5;
            if (fVar39 * 2.5 <= 2.0) {
              fVar35 = 2.0;
            }
            uVar52 = NEON_fmov(0x3f800000,4);
            fVar39 = fVar37 * 2.5;
            if (fVar37 * 2.5 <= 2.0) {
              fVar39 = 2.0;
            }
            if (fVar36 <= 2.0) {
              fVar36 = 2.0;
            }
            uVar17 = local_d0 - 1;
            uVar31 = 0;
            do {
              uVar10 = uVar31 + 1;
              if ((int)uVar10 < (int)local_cc) {
                memmove((void *)((long)__s +
                                __n * (uVar10 - (uVar10 / 3 +
                                                ((uint)((ulong)uVar10 * 0xaaaaaaab >> 0x20) &
                                                0xfffffffe)))),
                        (void *)((long)local_b8 + (ulong)(local_c8 * uVar10)),__n);
              }
              uVar25 = 0;
              do {
                lVar24 = uVar25 * 4;
                uVar21 = (uint)uVar25;
                fVar43 = 0.0;
                fVar44 = 0.0;
                fVar37 = 0.0;
                fVar45 = 0.0;
                fVar46 = 0.0;
                pbVar1 = (byte *)((long)__s +
                                 lVar24 + __n * (uVar31 - (uVar31 / 3 +
                                                          ((uint)((ulong)uVar31 * 0xaaaaaaab >> 0x20
                                                                 ) & 0xfffffffe))));
                uVar8 = uVar21 - 1;
                if ((int)uVar17 <= (int)(uVar21 - 1)) {
                  uVar8 = uVar17;
                }
                if ((int)uVar17 <= (int)uVar21) {
                  uVar21 = uVar17;
                }
                uVar25 = uVar25 + 1;
                fVar47 = (float)NEON_ucvtf((uint)*pbVar1);
                fVar48 = (float)NEON_ucvtf((uint)pbVar1[1]);
                fVar49 = (float)NEON_ucvtf((uint)pbVar1[2]);
                uVar9 = (uint)uVar25;
                if ((int)uVar17 <= (int)(uint)uVar25) {
                  uVar9 = uVar17;
                }
                iVar30 = -1;
                fVar48 = fVar47 * 0.2126 + fVar48 * 0.7152 + fVar49 * 0.0722;
                fVar51 = 0.0;
                fVar49 = fVar49 - fVar48;
                fVar50 = fVar47 - fVar48;
                do {
                  uVar7 = uVar31 + iVar30;
                  if ((int)uVar33 <= (int)(uVar31 + iVar30)) {
                    uVar7 = uVar33;
                  }
                  bVar15 = iVar30 != 0;
                  iVar30 = iVar30 + 1;
                  uVar7 = uVar7 & ((int)uVar7 >> 0x1f ^ 0xffffffffU);
                  lVar32 = __n * (uVar7 + (int)((ulong)uVar7 * 0x55555556 >> 0x20) * -3);
                  pbVar2 = (byte *)((long)__s +
                                   (ulong)((uVar9 & ((int)uVar9 >> 0x1f ^ 0xffffffffU)) << 2) +
                                   lVar32);
                  pbVar3 = (byte *)((long)__s +
                                   (ulong)((uVar8 & ((int)uVar8 >> 0x1f ^ 0xffffffffU)) << 2) +
                                   lVar32);
                  puVar6 = (undefined *)
                           ((long)__s +
                           (ulong)((uVar21 & ((int)uVar21 >> 0x1f ^ 0xffffffffU)) << 2) + lVar32);
                  fVar53 = (float)NEON_ucvtf((uint)pbVar2[1]);
                  fVar54 = (float)NEON_ucvtf((uint)*pbVar2);
                  fVar55 = (float)NEON_ucvtf((uint)pbVar2[2]);
                  uVar59 = NEON_ucvtf((ulong)CONCAT14(puVar6[1],(uint)*pbVar3),4);
                  uVar56 = NEON_ucvtf((ulong)CONCAT14(*puVar6,(uint)pbVar3[1]),4);
                  fVar60 = fVar54 * 0.2126 + fVar53 * 0.7152 + fVar55 * 0.0722;
                  fVar57 = (float)((ulong)uVar56 >> 0x20);
                  uVar64 = NEON_ucvtf((ulong)CONCAT14(puVar6[2],(uint)pbVar3[2]),4);
                  fVar65 = (float)((ulong)uVar64 >> 0x20);
                  fVar53 = 2.0;
                  fVar66 = (fVar60 - fVar48) / fVar35;
                  if (bVar15) {
                    fVar53 = 1.0;
                  }
                  fVar61 = (float)uVar56 * (float)uVar38 + (float)uVar59 * (float)uVar13 +
                           (float)uVar64 * 0.0722;
                  fVar62 = fVar57 * (float)((ulong)uVar38 >> 0x20) +
                           (float)((ulong)uVar59 >> 0x20) * (float)((ulong)uVar13 >> 0x20) +
                           fVar65 * 0.0722;
                  fVar58 = (float)uVar59 - fVar61;
                  fVar57 = fVar57 - fVar62;
                  fVar63 = (float)uVar64 - fVar61;
                  fVar65 = fVar65 - fVar62;
                  fVar67 = (fVar61 - fVar48) / fVar35;
                  fVar68 = (fVar62 - fVar48) / fVar35;
                  fVar69 = (fVar58 - fVar50) / fVar36;
                  fVar70 = (fVar57 - fVar50) / fVar36;
                  fVar72 = (float)((ulong)uVar52 >> 0x20);
                  fVar66 = fVar53 / (fVar66 * fVar66 * fVar66 * fVar66 + 1.0);
                  fVar67 = fVar53 / (fVar67 * fVar67 * fVar67 * fVar67 + (float)uVar52);
                  fVar68 = (fVar53 + fVar53) / (fVar68 * fVar68 * fVar68 * fVar68 + fVar72);
                  fVar73 = (fVar63 - fVar49) / fVar39;
                  fVar74 = (fVar65 - fVar49) / fVar39;
                  fVar70 = fVar68 / (fVar70 * fVar70 * fVar70 * fVar70 + 1.0);
                  fVar71 = ((fVar54 - fVar60) - fVar50) / fVar36;
                  fVar53 = ((fVar55 - fVar60) - fVar49) / fVar39;
                  fVar69 = fVar67 / (fVar69 * fVar69 * fVar69 * fVar69 + 1.0);
                  fVar73 = fVar67 / (fVar73 * fVar73 * fVar73 * fVar73 + (float)uVar52);
                  fVar74 = fVar68 / (fVar74 * fVar74 * fVar74 * fVar74 + fVar72);
                  fVar72 = fVar66 / (fVar71 * fVar71 * fVar71 * fVar71 + 1.0);
                  fVar53 = fVar66 / (fVar53 * fVar53 * fVar53 * fVar53 + 1.0);
                  fVar45 = fVar45 + fVar69 + fVar70 + fVar72;
                  fVar46 = fVar46 + fVar67 + fVar68 + fVar66;
                  fVar43 = fVar43 + fVar58 * fVar69 + fVar57 * fVar70 + (fVar54 - fVar60) * fVar72;
                  fVar44 = fVar44 + fVar61 * fVar67 + fVar62 * fVar68 + fVar60 * fVar66;
                  fVar37 = fVar37 + fVar73 + fVar74 + fVar53;
                  fVar51 = fVar51 + fVar63 * fVar73 + fVar65 * fVar74 + (fVar55 - fVar60) * fVar53;
                } while (iVar30 != 2);
                fVar53 = (255.0 - fVar48) * 0.125;
                if (fVar48 * 0.125 <= fVar53) {
                  fVar53 = fVar48 * 0.125;
                }
                uVar56 = NEON_fminnm(CONCAT44(fVar42 * (fVar44 / fVar46 - fVar48),
                                              (float)((ulong)uVar40 >> 0x20) *
                                              (fVar43 / fVar45 - fVar50)),uVar41,4);
                fVar43 = (float)NEON_fminnm(fVar53,0x3f800000);
                uVar56 = NEON_fmaxnm(uVar56,uVar14,4);
                if (fVar43 <= 0.0) {
                  fVar43 = 0.0;
                }
                fVar44 = (float)((ulong)uVar56 >> 0x20);
                fVar47 = fVar43 * ((float)uVar56 + fVar44) + fVar47;
                if (ABS(fVar47) == INFINITY) {
                  this = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 001354ec to 001354f7 has its CatchHandler @ 00135570 */
                  std::runtime_error::runtime_error(this,"Non-finite image sample");
LAB_00135530:
                    /* try { // try from 00135530 to 00135547 has its CatchHandler @ 00135584 */
                    /* WARNING: Subroutine does not return */
                  __cxa_throw(this,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
                }
                puVar6 = (undefined *)((long)local_b8 + (ulong)(local_c8 * uVar31) + lVar24);
                fVar37 = (float)NEON_fminnm((float)uVar40 * (fVar51 / fVar37 - fVar49),0x41000000);
                if (fVar37 <= -8.0) {
                  fVar37 = -8.0;
                }
                fVar45 = (float)NEON_fminnm((int)fVar47,0x437f0000);
                if (fVar45 <= 0.0) {
                  fVar45 = 0.0;
                }
                *puVar6 = (char)(int)fVar45;
                fVar45 = (float)NEON_ucvtf((uint)pbVar1[1]);
                fVar45 = fVar43 * (fVar44 + (fVar37 * 0.0722 + (float)uVar56 * 0.2126) / -0.7152) +
                         fVar45;
                if (ABS(fVar45) == INFINITY) {
                  this = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00135508 to 00135513 has its CatchHandler @ 0013556c */
                  std::runtime_error::runtime_error(this,"Non-finite image sample");
                  goto LAB_00135530;
                }
                fVar45 = (float)NEON_fminnm((int)fVar45,0x437f0000);
                if (fVar45 <= 0.0) {
                  fVar45 = 0.0;
                }
                puVar6[1] = (char)(int)fVar45;
                fVar45 = (float)NEON_ucvtf((uint)pbVar1[2]);
                fVar45 = fVar43 * (fVar37 + fVar44) + fVar45;
                if (ABS(fVar45) == INFINITY) {
                  this = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00135524 to 0013552f has its CatchHandler @ 00135568 */
                  std::runtime_error::runtime_error(this,"Non-finite image sample");
                  goto LAB_00135530;
                }
                fVar37 = (float)NEON_fminnm((int)fVar45,0x437f0000);
                if (fVar37 <= 0.0) {
                  fVar37 = 0.0;
                }
                puVar6[2] = (char)(int)fVar37;
              } while (uVar25 != local_d0);
              uVar31 = uVar10;
            } while (uVar10 != local_cc);
          }
        }
        operator_delete(__s);
      }
      if (local_128 != (float *)0x0) {
        operator_delete(local_128);
      }
      if (local_110 != (float *)0x0) {
        operator_delete(local_110);
      }
      if (local_f8 != (float *)0x0) {
        operator_delete(local_f8);
      }
    }
    if (local_b8 != (void *)0x0) {
                    /* try { // try from 00135488 to 0013548b has its CatchHandler @ 00135558 */
      AndroidBitmap_unlockPixels(local_e0,uStack_d8);
    }
  }
  return;
}



/* 00135714 Java_com_codex_fullm9_NativeM9_hdrSample */

long Java_com_codex_fullm9_NativeM9_hdrSample
               (long *param_1,undefined8 param_2,_jobject *param_3,uint param_4,uint param_5)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  ulong uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  int iVar11;
  void *__s;
  long lVar12;
  runtime_error *prVar13;
  uint uVar14;
  ulong uVar15;
  ulong uVar16;
  ulong uVar17;
  double dVar18;
  double dVar19;
  float fVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  double dVar24;
  double dVar25;
  double dVar26;
  double dVar27;
  double dVar28;
  double dVar29;
  double dVar30;
  double dVar31;
  undefined8 local_90;
  undefined8 uStack_88;
  uint local_80;
  uint local_7c;
  int local_78;
  long local_68;
  
                    /* try { // try from 00135740 to 0013574b has its CatchHandler @ 00135a64 */
  Pixels::Pixels((Pixels *)&local_90,(_JNIEnv *)param_1,param_3);
  if ((((param_4 - 0x181 < 0xfffffe80) || (param_5 - 0x181 < 0xfffffe80)) ||
      ((int)local_80 < (int)param_4)) || ((int)local_7c < (int)param_5)) {
    prVar13 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00135a38 to 00135a43 has its CatchHandler @ 00135a7c */
    std::runtime_error::runtime_error(prVar13,"HDR sample dimensions");
                    /* try { // try from 00135a44 to 00135a5b has its CatchHandler @ 00135a70 */
                    /* WARNING: Subroutine does not return */
    __cxa_throw(prVar13,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
  }
  uVar17 = (ulong)param_5 * (ulong)param_4;
                    /* try { // try from 00135784 to 0013578b has its CatchHandler @ 00135a60 */
  __s = operator_new(uVar17 * 4);
  memset(__s,0,uVar17 * 4);
  dVar10 = DAT_00119b38;
  dVar9 = DAT_00119b30;
  dVar8 = DAT_00119ad8;
  uVar15 = 0;
  do {
    iVar7 = (int)uVar15;
    uVar15 = uVar15 + 1;
    uVar16 = 0;
    dVar18 = ((double)(ulong)local_7c / (double)param_5) * (double)(int)uVar15;
    dVar19 = ((double)(ulong)local_7c / (double)param_5) * (double)iVar7;
    uVar5 = local_7c;
    if ((int)dVar18 <= (int)local_7c) {
      uVar5 = (int)dVar18;
    }
    do {
      dVar21 = 0.0;
      uVar4 = uVar16 + 1;
      if ((int)dVar19 < (int)uVar5) {
        dVar24 = 0.0;
        dVar22 = ((double)(ulong)local_80 / (double)param_4) * (double)(int)uVar4;
        dVar23 = ((double)(ulong)local_80 / (double)param_4) * (double)(int)uVar16;
        iVar11 = (int)dVar23;
        uVar6 = local_80;
        if ((int)dVar22 <= (int)local_80) {
          uVar6 = (int)dVar22;
        }
        if (iVar11 < (int)uVar6) {
          uVar14 = (int)dVar19;
          do {
            dVar25 = (double)uVar14;
            dVar26 = dVar25 + 1.0;
            if (dVar18 <= dVar25 + 1.0) {
              dVar26 = dVar18;
            }
            if (dVar25 <= dVar19) {
              dVar25 = dVar19;
            }
            lVar12 = (long)(int)uVar6 - (long)iVar11;
            iVar3 = iVar11;
            iVar2 = iVar11 << 2;
            do {
              dVar27 = (double)iVar3;
              pbVar1 = (byte *)(local_68 + (ulong)(local_78 * uVar14) + (long)iVar2);
              iVar2 = iVar2 + 4;
              iVar3 = iVar3 + 1;
              dVar29 = (double)NEON_ucvtf((ulong)*pbVar1);
              dVar30 = (double)NEON_ucvtf((ulong)pbVar1[1]);
              dVar31 = (double)NEON_ucvtf((ulong)pbVar1[2]);
              dVar28 = dVar27 + 1.0;
              if (dVar22 <= dVar27 + 1.0) {
                dVar28 = dVar22;
              }
              if (dVar27 <= dVar23) {
                dVar27 = dVar23;
              }
              lVar12 = lVar12 + -1;
              dVar27 = (dVar26 - dVar25) * (dVar28 - dVar27);
              dVar21 = dVar21 + dVar27;
              dVar24 = dVar24 + dVar27 * (dVar29 * dVar8 + dVar30 * dVar9 + dVar31 * dVar10);
            } while (lVar12 != 0);
            uVar14 = uVar14 + 1;
          } while (uVar14 != uVar5);
        }
      }
      else {
        dVar24 = 0.0;
      }
      if (ABS((float)(dVar24 / dVar21)) == INFINITY) {
        prVar13 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00135a08 to 00135a13 has its CatchHandler @ 00135aa0 */
        std::runtime_error::runtime_error(prVar13,"Non-finite image sample");
                    /* try { // try from 00135a14 to 00135a2b has its CatchHandler @ 00135a94 */
                    /* WARNING: Subroutine does not return */
        __cxa_throw(prVar13,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
      }
      fVar20 = (float)NEON_fminnm((int)(dVar24 / dVar21),0x437f0000);
      if (fVar20 <= 0.0) {
        fVar20 = 0.0;
      }
      *(uint *)((long)__s + uVar16 * 4 + (ulong)(iVar7 * param_4) * 4) =
           (int)fVar20 * 0x10101 | 0xff000000;
      uVar16 = uVar4;
    } while (uVar4 != param_4);
    if (uVar15 == param_5) {
                    /* try { // try from 0013598c to 001359bf has its CatchHandler @ 00135a90 */
      lVar12 = (**(code **)(*param_1 + 0x598))(param_1,uVar17 & 0xffffffff);
      if (lVar12 != 0) {
        (**(code **)(*param_1 + 0x698))(param_1,lVar12,0,uVar17 & 0xffffffff,__s);
      }
      operator_delete(__s);
      if (local_68 != 0) {
                    /* try { // try from 001359d4 to 001359d7 has its CatchHandler @ 00135a5c */
        AndroidBitmap_unlockPixels(local_90,uStack_88);
      }
      return lVar12;
    }
  } while( true );
}



/* 00135be4 Java_com_codex_fullm9_NativeM9_frameCreate */

uint * Java_com_codex_fullm9_NativeM9_frameCreate
                 (_JNIEnv *param_1,undefined8 param_2,_jobject *param_3)

{
  undefined *puVar1;
  long lVar2;
  int iVar3;
  uint uVar4;
  uint *this;
  long lVar5;
  long lVar6;
  uint uVar7;
  uint uVar8;
  undefined8 local_60;
  undefined8 uStack_58;
  int local_50;
  int iStack_4c;
  int local_48;
  long local_38;
  
                    /* try { // try from 00135bfc to 00135c07 has its CatchHandler @ 00135d84 */
  Pixels::Pixels((Pixels *)&local_60,param_1,param_3);
                    /* try { // try from 00135c08 to 00135c0f has its CatchHandler @ 00135d70 */
  this = (uint *)operator_new(0x70);
                    /* try { // try from 00135c18 to 00135c1b has its CatchHandler @ 00135d5c */
  m9::Frame::Frame((Frame *)this,local_50,iStack_4c);
  lVar5 = 0;
  do {
    lVar6 = 0;
    do {
      uVar4 = *this;
      if ((int)uVar4 < 2) {
        uVar7 = 0;
      }
      else {
        uVar7 = (int)lVar6 - this[2];
        if (uVar4 <= uVar7) {
          do {
            iVar3 = 0;
            if (-1 < (int)uVar7) {
              iVar3 = uVar4 * 2 + -2;
            }
            uVar7 = iVar3 - uVar7;
          } while (uVar4 <= uVar7);
        }
      }
      uVar4 = this[1];
      if ((int)uVar4 < 2) {
        uVar8 = 0;
      }
      else {
        uVar8 = (int)lVar5 - this[3];
        if (uVar4 <= uVar8) {
          do {
            iVar3 = 0;
            if (-1 < (int)uVar8) {
              iVar3 = uVar4 * 2 + -2;
            }
            uVar8 = iVar3 - uVar8;
          } while (uVar4 <= uVar8);
        }
      }
      puVar1 = (undefined *)(local_38 + (ulong)(local_48 * uVar8) + (long)(int)uVar7 * 4);
      lVar2 = lVar6 + lVar5 * 0x1000;
      lVar6 = lVar6 + 1;
      lVar2 = lVar2 * 3;
      *(undefined *)(*(long *)(this + 4) + lVar2) = *puVar1;
      *(undefined *)(*(long *)(this + 4) + lVar2 + 1) = puVar1[1];
      *(undefined *)(*(long *)(this + 4) + lVar2 + 2) = puVar1[2];
    } while (lVar6 != 0x1000);
    lVar5 = lVar5 + 1;
  } while (lVar5 != 0xc00);
                    /* try { // try from 00135d14 to 00135d1b has its CatchHandler @ 00135d48 */
  m9::Frame::prepare();
  if (local_38 != 0) {
                    /* try { // try from 00135d28 to 00135d2b has its CatchHandler @ 00135d44 */
    AndroidBitmap_unlockPixels(local_60,uStack_58);
  }
  return this;
}



/* 00135e54 Java_com_codex_fullm9_NativeM9_styleInput */

void Java_com_codex_fullm9_NativeM9_styleInput
               (long *param_1,undefined8 param_2,Frame *param_3,undefined8 param_4)

{
  float *pfVar1;
  long lVar2;
  runtime_error *this;
  
  if (param_3 == (Frame *)0x0) {
    this = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00135ef4 to 00135eff has its CatchHandler @ 00135f18 */
    std::runtime_error::runtime_error(this,"Missing frame");
  }
  else {
                    /* try { // try from 00135e80 to 00135ea7 has its CatchHandler @ 00135f30 */
    pfVar1 = (float *)(**(code **)(*param_1 + 0x730))(param_1,param_4);
    if ((pfVar1 != (float *)0x0) &&
       (lVar2 = (**(code **)(*param_1 + 0x738))(param_1,param_4), 0xec3fff < lVar2)) {
      m9::Frame::styleInput(param_3,pfVar1);
      return;
    }
    this = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00135ed8 to 00135ee3 has its CatchHandler @ 00135f1c */
    std::runtime_error::runtime_error(this,"Invalid direct tensor buffer");
  }
                    /* try { // try from 00135f00 to 00135f17 has its CatchHandler @ 00135f30 */
                    /* WARNING: Subroutine does not return */
  __cxa_throw(this,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
}



/* 00135ff8 Java_com_codex_fullm9_NativeM9_styleOutput */

void Java_com_codex_fullm9_NativeM9_styleOutput
               (long *param_1,undefined8 param_2,Frame *param_3,undefined8 param_4)

{
  float *pfVar1;
  long lVar2;
  runtime_error *this;
  
  if (param_3 == (Frame *)0x0) {
    this = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013609c to 001360a7 has its CatchHandler @ 001360c0 */
    std::runtime_error::runtime_error(this,"Missing frame");
  }
  else {
                    /* try { // try from 00136024 to 0013605f has its CatchHandler @ 001360d8 */
    pfVar1 = (float *)(**(code **)(*param_1 + 0x730))(param_1,param_4);
    if ((pfVar1 != (float *)0x0) &&
       (lVar2 = (**(code **)(*param_1 + 0x738))(param_1,param_4), 0xb12fff < lVar2)) {
      m9::Frame::styleOutput(param_3,pfVar1);
      return;
    }
    this = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00136080 to 0013608b has its CatchHandler @ 001360c4 */
    std::runtime_error::runtime_error(this,"Invalid direct tensor buffer");
  }
                    /* try { // try from 001360a8 to 001360bf has its CatchHandler @ 001360d8 */
                    /* WARNING: Subroutine does not return */
  __cxa_throw(this,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
}



/* 001361a0 Java_com_codex_fullm9_NativeM9_tileInput */

void Java_com_codex_fullm9_NativeM9_tileInput
               (long *param_1,undefined8 param_2,Frame *param_3,uint param_4,undefined8 param_5)

{
  float *pfVar1;
  long lVar2;
  runtime_error *this;
  
  if (param_4 < 0x30) {
                    /* try { // try from 001361d8 to 001361ff has its CatchHandler @ 00136290 */
    pfVar1 = (float *)(**(code **)(*param_1 + 0x730))(param_1,param_5);
    if ((pfVar1 != (float *)0x0) &&
       (lVar2 = (**(code **)(*param_1 + 0x738))(param_1,param_5), 0x6c5fff < lVar2)) {
      m9::Frame::tileInput(param_3,param_4,pfVar1);
      return;
    }
    this = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00136238 to 00136243 has its CatchHandler @ 0013627c */
    std::runtime_error::runtime_error(this,"Invalid direct tensor buffer");
  }
  else {
    this = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00136254 to 0013625f has its CatchHandler @ 00136278 */
    std::runtime_error::runtime_error(this,"Tile index");
  }
                    /* try { // try from 00136260 to 00136277 has its CatchHandler @ 00136290 */
                    /* WARNING: Subroutine does not return */
  __cxa_throw(this,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
}



/* 0013635c Java_com_codex_fullm9_NativeM9_tileOutput */

void Java_com_codex_fullm9_NativeM9_tileOutput
               (long *param_1,undefined8 param_2,Frame *param_3,uint param_4,undefined8 param_5)

{
  float *pfVar1;
  long lVar2;
  runtime_error *this;
  
  if (param_4 < 0x30) {
                    /* try { // try from 00136394 to 001363d3 has its CatchHandler @ 00136450 */
    pfVar1 = (float *)(**(code **)(*param_1 + 0x730))(param_1,param_5);
    if ((pfVar1 != (float *)0x0) &&
       (lVar2 = (**(code **)(*param_1 + 0x738))(param_1,param_5), 0x362fff < lVar2)) {
      m9::Frame::tileOutput(param_3,param_4,pfVar1);
      return;
    }
    this = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 001363f8 to 00136403 has its CatchHandler @ 0013643c */
    std::runtime_error::runtime_error(this,"Invalid direct tensor buffer");
  }
  else {
    this = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00136414 to 0013641f has its CatchHandler @ 00136438 */
    std::runtime_error::runtime_error(this,"Tile index");
  }
                    /* try { // try from 00136420 to 00136437 has its CatchHandler @ 00136450 */
                    /* WARNING: Subroutine does not return */
  __cxa_throw(this,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
}



/* 0013651c Java_com_codex_fullm9_NativeM9_frameFinish */

void Java_com_codex_fullm9_NativeM9_frameFinish
               (long *param_1,undefined8 param_2,uint *param_3,_jobject *param_4,undefined8 param_5,
               undefined8 param_6)

{
  undefined *puVar1;
  int iVar2;
  uchar *__s;
  runtime_error *prVar3;
  ulong uVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  float fVar8;
  float local_bc;
  float local_b8;
  float local_b4;
  float afStack_b0 [8];
  undefined8 local_90;
  undefined8 uStack_88;
  uint local_80;
  uint local_7c;
  int local_78;
  long local_68;
  
                    /* try { // try from 00136550 to 0013655f has its CatchHandler @ 00136818 */
  Pixels::Pixels((Pixels *)&local_90,(_JNIEnv *)param_1,param_4);
                    /* try { // try from 00136588 to 001365b3 has its CatchHandler @ 0013683c */
  if ((((local_80 != *param_3) || (local_7c != param_3[1])) ||
      (iVar2 = (**(code **)(*param_1 + 0x558))(param_1,param_5), iVar2 != 0x3993)) ||
     (iVar2 = (**(code **)(*param_1 + 0x558))(param_1,param_6), iVar2 != 8)) {
    prVar3 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 001367ec to 001367f7 has its CatchHandler @ 00136828 */
    std::runtime_error::runtime_error(prVar3,"Filter dimensions");
                    /* try { // try from 001367f8 to 0013680f has its CatchHandler @ 0013683c */
                    /* WARNING: Subroutine does not return */
    __cxa_throw(prVar3,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
  }
                    /* try { // try from 001365bc to 001365c3 has its CatchHandler @ 00136814 */
  __s = (uchar *)operator_new(0x3993);
  memset(__s,0,0x3993);
                    /* try { // try from 001365dc to 00136613 has its CatchHandler @ 00136824 */
  (**(code **)(*param_1 + 0x640))(param_1,param_5,0,0x3993,__s);
  (**(code **)(*param_1 + 0x668))(param_1,param_6,0,8,afStack_b0);
  uVar5 = param_3[1];
  if ((0 < (int)uVar5) && (uVar4 = (ulong)*param_3, 0 < (int)*param_3)) {
    iVar2 = 0;
    do {
      if (0 < (int)uVar4) {
        uVar7 = 0;
        lVar6 = 0;
        do {
                    /* try { // try from 00136738 to 0013674f has its CatchHandler @ 00136848 */
          m9::leicaPixel((uchar *)(*(long *)(param_3 + 0x16) +
                                  (long)(int)(((int)lVar6 +
                                              param_3[2] + (iVar2 + param_3[3]) * 0x1000) * 3)),__s,
                         afStack_b0,(int)lVar6,iVar2,(int)uVar4,param_3[1],&local_bc);
          if (ABS(local_bc * 255.0) == INFINITY) {
LAB_00136774:
            prVar3 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00136780 to 0013678b has its CatchHandler @ 00136858 */
            std::runtime_error::runtime_error(prVar3,"Non-finite image sample");
                    /* try { // try from 0013678c to 001367a3 has its CatchHandler @ 0013684c */
                    /* WARNING: Subroutine does not return */
            __cxa_throw(prVar3,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
          }
          fVar8 = (float)NEON_fminnm((int)(local_bc * 255.0),0x437f0000);
          puVar1 = (undefined *)(local_68 + (uVar7 & 0xfffffffc) + (ulong)(uint)(local_78 * iVar2));
          if (fVar8 <= 0.0) {
            fVar8 = 0.0;
          }
          *puVar1 = (char)(int)fVar8;
          if (ABS(local_b8 * 255.0) == INFINITY) goto LAB_00136774;
          fVar8 = (float)NEON_fminnm((int)(local_b8 * 255.0),0x437f0000);
          if (fVar8 <= 0.0) {
            fVar8 = 0.0;
          }
          puVar1[1] = (char)(int)fVar8;
          if (ABS(local_b4 * 255.0) == INFINITY) goto LAB_00136774;
          puVar1[3] = 0xff;
          lVar6 = lVar6 + 1;
          uVar7 = uVar7 + 4;
          fVar8 = (float)NEON_fminnm((int)(local_b4 * 255.0),0x437f0000);
          if (fVar8 <= 0.0) {
            fVar8 = 0.0;
          }
          puVar1[2] = (char)(int)fVar8;
          uVar4 = (ulong)(int)*param_3;
        } while (lVar6 < (long)uVar4);
        uVar5 = param_3[1];
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < (int)uVar5);
  }
  operator_delete(__s);
  if (local_68 != 0) {
                    /* try { // try from 001367b8 to 001367bb has its CatchHandler @ 00136810 */
    AndroidBitmap_unlockPixels(local_90,uStack_88);
  }
  return;
}



/* 00136934 Java_com_codex_fullm9_NativeM9_frameClose */

void Java_com_codex_fullm9_NativeM9_frameClose(undefined8 param_1,undefined8 param_2,void *param_3)

{
  void *pvVar1;
  
  if (param_3 != (void *)0x0) {
    pvVar1 = *(void **)((long)param_3 + 0x58);
    if (pvVar1 != (void *)0x0) {
      *(void **)((long)param_3 + 0x60) = pvVar1;
      operator_delete(pvVar1);
    }
    pvVar1 = *(void **)((long)param_3 + 0x40);
    if (pvVar1 != (void *)0x0) {
      *(void **)((long)param_3 + 0x48) = pvVar1;
      operator_delete(pvVar1);
    }
    pvVar1 = *(void **)((long)param_3 + 0x28);
    if (pvVar1 != (void *)0x0) {
      *(void **)((long)param_3 + 0x30) = pvVar1;
      operator_delete(pvVar1);
    }
    pvVar1 = *(void **)((long)param_3 + 0x10);
    if (pvVar1 != (void *)0x0) {
      *(void **)((long)param_3 + 0x18) = pvVar1;
      operator_delete(pvVar1);
    }
    operator_delete(param_3);
    return;
  }
  return;
}



/* 0013699c Java_com_codex_fullm9_NativeM9_rawOpen */

uint * Java_com_codex_fullm9_NativeM9_rawOpen
                 (long *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  ushort uVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  void *__s;
  long lVar5;
  int *piVar6;
  uint *puVar7;
  runtime_error *prVar8;
  ulong __n;
  uint uVar9;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  uint *local_68;
  int local_44;
  
  if (((Java_com_codex_fullm9_NativeM9_rawOpen::a & 1) == 0) &&
     (iVar4 = __cxa_guard_acquire(&Java_com_codex_fullm9_NativeM9_rawOpen::a), iVar4 != 0)) {
                    /* try { // try from 00136d88 to 00136d93 has its CatchHandler @ 00136e3c */
    RawApi::RawApi((RawApi *)Java_com_codex_fullm9_NativeM9_rawOpen::a);
    __cxa_guard_release(&Java_com_codex_fullm9_NativeM9_rawOpen::a);
  }
                    /* try { // try from 001369e0 to 00136a17 has its CatchHandler @ 00136f28 */
  uVar3 = (**(code **)(*param_1 + 0x558))(param_1,param_3);
  __n = (ulong)uVar3;
  if ((0xf000000e < uVar3 + 0xefffffff) &&
     (iVar4 = (**(code **)(*param_1 + 0x558))(param_1,param_4), iVar4 == 4)) {
                    /* try { // try from 00136a24 to 00136a2b has its CatchHandler @ 00136efc */
    __s = operator_new(__n);
    memset(__s,0,__n);
                    /* try { // try from 00136a44 to 00136a5b has its CatchHandler @ 00136ee8 */
    (**(code **)(*param_1 + 0x640))(param_1,param_3,0,__n,__s);
                    /* try { // try from 00136a64 to 00136b57 has its CatchHandler @ 00136f68 */
    (**(code **)(*param_1 + 0x668))(param_1,param_4,0,4,&local_80);
    lVar5 = (*(code *)Java_com_codex_fullm9_NativeM9_rawOpen::a._8_8_)(0);
    if (lVar5 == 0) {
      prVar8 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00136db0 to 00136dbb has its CatchHandler @ 00136e70 */
      std::runtime_error::runtime_error(prVar8,"LibRaw init");
                    /* try { // try from 00136dbc to 00136dd7 has its CatchHandler @ 00136f68 */
                    /* WARNING: Subroutine does not return */
      __cxa_throw(prVar8,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
    }
    iVar4 = (*(code *)Java_com_codex_fullm9_NativeM9_rawOpen::a._16_8_)(lVar5,__s,__n);
    if ((iVar4 == 0) &&
       (iVar4 = (*(code *)Java_com_codex_fullm9_NativeM9_rawOpen::a._24_8_)(lVar5), iVar4 == 0)) {
      (*(code *)Java_com_codex_fullm9_NativeM9_rawOpen::a._64_8_)(0x3f800000,lVar5,0);
      (*(code *)Java_com_codex_fullm9_NativeM9_rawOpen::a._64_8_)(0x3f800000,lVar5,1);
      (*(code *)Java_com_codex_fullm9_NativeM9_rawOpen::a._80_8_)(lVar5,0x10);
      (*(code *)Java_com_codex_fullm9_NativeM9_rawOpen::a._88_8_)(lVar5,0);
      (*(code *)Java_com_codex_fullm9_NativeM9_rawOpen::a._96_8_)(lVar5,3);
      (*(code *)Java_com_codex_fullm9_NativeM9_rawOpen::a._104_8_)(lVar5,1);
      (*(code *)Java_com_codex_fullm9_NativeM9_rawOpen::a._112_8_)(lVar5,0);
                    /* try { // try from 00136b64 to 00136bab has its CatchHandler @ 00136f54 */
      (*(code *)Java_com_codex_fullm9_NativeM9_rawOpen::a._72_8_)(local_80,lVar5,0);
      (*(code *)Java_com_codex_fullm9_NativeM9_rawOpen::a._72_8_)(local_7c,lVar5,1);
      (*(code *)Java_com_codex_fullm9_NativeM9_rawOpen::a._72_8_)(local_78,lVar5,2);
      (*(code *)Java_com_codex_fullm9_NativeM9_rawOpen::a._72_8_)(local_74,lVar5,3);
                    /* try { // try from 00136bb4 to 00136bbb has its CatchHandler @ 00136f68 */
      iVar4 = (*(code *)Java_com_codex_fullm9_NativeM9_rawOpen::a._32_8_)(lVar5);
      if (iVar4 == 0) {
        local_44 = 0;
                    /* try { // try from 00136bcc to 00136bdb has its CatchHandler @ 00136f58 */
        piVar6 = (int *)(*(code *)Java_com_codex_fullm9_NativeM9_rawOpen::a._40_8_)(lVar5,&local_44)
        ;
        if ((((piVar6 != (int *)0x0) && (local_44 == 0)) && (*piVar6 == 2)) &&
           ((*(short *)(piVar6 + 2) == 3 && (*(short *)((long)piVar6 + 10) == 0x10)))) {
          uVar1 = *(ushort *)((long)piVar6 + 6);
          if (0xf < uVar1) {
            uVar2 = *(ushort *)(piVar6 + 1);
            if ((0xf < uVar2) && (piVar6[3] == (uint)uVar1 * (uint)uVar2 * 6)) {
              uVar9 = (uint)uVar2;
              uVar3 = (uint)uVar1;
              if ((ulong)uVar2 * (ulong)uVar1 < 0x4000001) {
                    /* try { // try from 00136c50 to 00136c57 has its CatchHandler @ 00136ec8 */
                puVar7 = (uint *)operator_new(0x38);
                *puVar7 = uVar3;
                puVar7[1] = uVar9;
                *(undefined8 *)(puVar7 + 4) = 0;
                *(undefined8 *)(puVar7 + 2) = 0;
                *(undefined8 *)(puVar7 + 8) = 0;
                *(undefined8 *)(puVar7 + 6) = 0;
                *(undefined8 *)(puVar7 + 0xc) = 0;
                *(undefined8 *)(puVar7 + 10) = 0;
                    /* try { // try from 00136c80 to 00136c87 has its CatchHandler @ 00136e84 */
                std::__ndk1::vector<unsigned_short,std::__ndk1::allocator<unsigned_short>>::__append
                          ((vector<unsigned_short,std::__ndk1::allocator<unsigned_short>> *)
                           (puVar7 + 8),
                           (ulong)uVar3 * (ulong)uVar9 * 2 + (ulong)uVar3 * (ulong)uVar9);
                local_68 = puVar7;
                memmove(*(void **)(puVar7 + 8),piVar6 + 4,(ulong)uVar2 * (ulong)uVar1 * 6);
                    /* try { // try from 00136ca8 to 00136cc3 has its CatchHandler @ 00136f14 */
                (*(code *)Java_com_codex_fullm9_NativeM9_rawOpen::a._48_8_)(piVar6);
                (*(code *)Java_com_codex_fullm9_NativeM9_rawOpen::a._56_8_)(lVar5);
                operator_delete(__s);
                return puVar7;
              }
              prVar8 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00136e18 to 00136e23 has its CatchHandler @ 00136e68 */
              std::runtime_error::runtime_error(prVar8,"RAW exceeds 64 MP memory budget");
                    /* try { // try from 00136e24 to 00136e3b has its CatchHandler @ 00136e64 */
                    /* WARNING: Subroutine does not return */
              __cxa_throw(prVar8,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
            }
          }
        }
        prVar8 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00136cfc to 00136d07 has its CatchHandler @ 00136f40 */
        std::runtime_error::runtime_error(prVar8,"Unsupported linear RAW result");
                    /* try { // try from 00136d08 to 00136d23 has its CatchHandler @ 00136f58 */
                    /* WARNING: Subroutine does not return */
        __cxa_throw(prVar8,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
      }
      prVar8 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00136de8 to 00136df3 has its CatchHandler @ 00136e6c */
      std::runtime_error::runtime_error(prVar8,"Linear RAW processing failed");
    }
    else {
      prVar8 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00136d68 to 00136d73 has its CatchHandler @ 00136ed4 */
      std::runtime_error::runtime_error(prVar8,"RAW unpack failed");
    }
                    /* try { // try from 00136df4 to 00136e0b has its CatchHandler @ 00136f68 */
                    /* WARNING: Subroutine does not return */
    __cxa_throw(prVar8,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
  }
  prVar8 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00136d34 to 00136d3f has its CatchHandler @ 00136f00 */
  std::runtime_error::runtime_error(prVar8,"RAW input size");
                    /* try { // try from 00136d40 to 00136d57 has its CatchHandler @ 00136f28 */
                    /* WARNING: Subroutine does not return */
  __cxa_throw(prVar8,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
}



/* 00137070 Java_com_codex_fullm9_NativeM9_rawSize */

undefined8
Java_com_codex_fullm9_NativeM9_rawSize(long *param_1,undefined8 param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  undefined8 local_28;
  
  local_28 = *param_3;
  uVar1 = (**(code **)(*param_1 + 0x598))(param_1,2);
  (**(code **)(*param_1 + 0x698))(param_1,uVar1,0,2,&local_28);
  return uVar1;
}



/* 001370d4 Java_com_codex_fullm9_NativeM9_rawStats */

undefined8 Java_com_codex_fullm9_NativeM9_rawStats(long *param_1,undefined8 param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined8 *puVar7;
  int iVar8;
  undefined8 *__s;
  void *pvVar9;
  undefined8 uVar10;
  long lVar11;
  undefined8 *puVar12;
  int iVar13;
  int iVar14;
  undefined8 *puVar15;
  int iVar16;
  undefined8 *puVar17;
  long lVar18;
  float *pfVar19;
  ulong uVar20;
  int iVar21;
  ulong uVar22;
  undefined8 *puVar23;
  ulong uVar24;
  int iVar25;
  int iVar26;
  ushort *puVar27;
  long lVar28;
  undefined8 *puVar29;
  long lVar30;
  ushort *puVar31;
  float *pfVar32;
  int iVar33;
  int iVar34;
  ulong uVar35;
  float fVar36;
  undefined8 uVar37;
  float fVar38;
  float fVar39;
  undefined auVar40 [16];
  undefined auVar41 [16];
  undefined auVar42 [16];
  undefined8 uVar43;
  undefined auVar44 [16];
  float fVar45;
  float fVar46;
  undefined auVar47 [16];
  undefined auVar48 [16];
  undefined auVar49 [16];
  undefined auVar50 [16];
  undefined auVar51 [16];
  undefined auVar52 [16];
  undefined auVar53 [16];
  undefined auVar54 [16];
  undefined auVar55 [16];
  undefined8 *local_80;
  __less _Stack_61;
  
  iVar33 = *param_3;
  iVar14 = param_3[1];
  iVar34 = iVar14 + 0xf;
  if (-1 < iVar14) {
    iVar34 = iVar14;
  }
  iVar21 = iVar33 + 0xf;
  if (-1 < iVar33) {
    iVar21 = iVar33;
  }
  iVar13 = (int)SQRT(((double)iVar14 * (double)iVar33) / 400000.0);
  if (iVar13 < 2) {
    iVar13 = 1;
  }
                    /* try { // try from 0013714c to 00137153 has its CatchHandler @ 00137b24 */
  __s = (undefined8 *)operator_new(0x400);
  uVar5 = iVar21 >> 4;
  uVar35 = (ulong)uVar5;
  puVar29 = __s + 0x80;
  iVar34 = iVar34 >> 4;
  memset(__s,0,0x400);
  uVar10 = DAT_00119ad0;
  fVar36 = (float)(uVar5 * iVar34);
  fVar38 = (0.0 / fVar36) * 255.0;
  if (iVar14 < 0x10) {
    uVar10 = CONCAT44(fVar38,fVar38);
    uVar43 = CONCAT44(fVar38,fVar38);
    __s[1] = uVar43;
    *__s = uVar10;
    __s[3] = uVar43;
    __s[2] = uVar10;
    __s[5] = uVar43;
    __s[4] = uVar10;
    __s[7] = uVar43;
    __s[6] = uVar10;
    __s[9] = uVar43;
    __s[8] = uVar10;
    __s[0xb] = uVar43;
    __s[10] = uVar10;
    __s[0xd] = uVar43;
    __s[0xc] = uVar10;
    __s[0xf] = uVar43;
    __s[0xe] = uVar10;
    __s[0x11] = uVar43;
    __s[0x10] = uVar10;
    __s[0x13] = uVar43;
    __s[0x12] = uVar10;
    __s[0x15] = uVar43;
    __s[0x14] = uVar10;
    __s[0x17] = uVar43;
    __s[0x16] = uVar10;
    __s[0x19] = uVar43;
    __s[0x18] = uVar10;
    __s[0x1b] = uVar43;
    __s[0x1a] = uVar10;
    __s[0x1d] = uVar43;
    __s[0x1c] = uVar10;
    __s[0x1f] = uVar43;
    __s[0x1e] = uVar10;
    __s[0x21] = uVar43;
    __s[0x20] = uVar10;
    __s[0x23] = uVar43;
    __s[0x22] = uVar10;
    __s[0x25] = uVar43;
    __s[0x24] = uVar10;
    __s[0x27] = uVar43;
    __s[0x26] = uVar10;
    __s[0x29] = uVar43;
    __s[0x28] = uVar10;
    __s[0x2b] = uVar43;
    __s[0x2a] = uVar10;
    __s[0x2d] = uVar43;
    __s[0x2c] = uVar10;
    __s[0x2f] = uVar43;
    __s[0x2e] = uVar10;
    __s[0x31] = uVar43;
    __s[0x30] = uVar10;
    __s[0x33] = uVar43;
    __s[0x32] = uVar10;
    __s[0x35] = uVar43;
    __s[0x34] = uVar10;
    __s[0x37] = uVar43;
    __s[0x36] = uVar10;
    __s[0x39] = uVar43;
    __s[0x38] = uVar10;
    __s[0x3b] = uVar43;
    __s[0x3a] = uVar10;
    __s[0x3d] = uVar43;
    __s[0x3c] = uVar10;
    __s[0x3f] = uVar43;
    __s[0x3e] = uVar10;
    __s[0x41] = uVar43;
    __s[0x40] = uVar10;
    __s[0x43] = uVar43;
    __s[0x42] = uVar10;
    __s[0x45] = uVar43;
    __s[0x44] = uVar10;
    __s[0x47] = uVar43;
    __s[0x46] = uVar10;
    __s[0x49] = uVar43;
    __s[0x48] = uVar10;
    __s[0x4b] = uVar43;
    __s[0x4a] = uVar10;
    __s[0x4d] = uVar43;
    __s[0x4c] = uVar10;
    __s[0x4f] = uVar43;
    __s[0x4e] = uVar10;
    __s[0x51] = uVar43;
    __s[0x50] = uVar10;
    __s[0x53] = uVar43;
    __s[0x52] = uVar10;
    __s[0x55] = uVar43;
    __s[0x54] = uVar10;
    __s[0x57] = uVar43;
    __s[0x56] = uVar10;
    __s[0x59] = uVar43;
    __s[0x58] = uVar10;
    __s[0x5b] = uVar43;
    __s[0x5a] = uVar10;
    __s[0x5d] = uVar43;
    __s[0x5c] = uVar10;
    __s[0x5f] = uVar43;
    __s[0x5e] = uVar10;
    __s[0x61] = uVar43;
    __s[0x60] = uVar10;
    __s[99] = uVar43;
    __s[0x62] = uVar10;
    __s[0x65] = uVar43;
    __s[100] = uVar10;
    __s[0x67] = uVar43;
    __s[0x66] = uVar10;
    __s[0x69] = uVar43;
    __s[0x68] = uVar10;
    __s[0x6b] = uVar43;
    __s[0x6a] = uVar10;
    __s[0x6d] = uVar43;
    __s[0x6c] = uVar10;
    __s[0x6f] = uVar43;
    __s[0x6e] = uVar10;
    __s[0x71] = uVar43;
    __s[0x70] = uVar10;
    __s[0x73] = uVar43;
    __s[0x72] = uVar10;
    __s[0x75] = uVar43;
    __s[0x74] = uVar10;
    __s[0x77] = uVar43;
    __s[0x76] = uVar10;
    __s[0x79] = uVar43;
    __s[0x78] = uVar10;
  }
  else {
    if (0xf < iVar33) {
      lVar28 = *(long *)(param_3 + 8);
      if (lVar28 == *(long *)(param_3 + 10)) {
        iVar6 = iVar33 * iVar34;
        lVar18 = *(long *)(param_3 + 2);
        iVar16 = 0;
        lVar28 = 0;
        uVar24 = uVar35 & 0x7fffff8;
        iVar21 = 4;
        do {
          lVar11 = 0;
          iVar2 = iVar16;
          iVar1 = iVar21;
          do {
            fVar38 = 0.0;
            iVar25 = 0;
            iVar4 = iVar2;
            iVar3 = iVar1;
            do {
              if ((uVar5 < 8) ||
                 (iVar26 = (int)lVar28 * iVar6 + (int)lVar11 * uVar5 + iVar33 * iVar25,
                 uVar22 = uVar24, iVar8 = iVar3,
                 iVar26 + (int)(uVar35 - 1) < iVar26 || uVar35 - 1 >> 0x20 != 0)) {
                uVar22 = 0;
LAB_00137a24:
                iVar26 = iVar4 + (int)uVar22;
                lVar30 = uVar35 - uVar22;
                do {
                  pfVar19 = (float *)(lVar18 + (long)iVar26 * 0xc);
                  lVar30 = lVar30 + -1;
                  iVar26 = iVar26 + 1;
                  uVar43 = *(undefined8 *)(pfVar19 + 1);
                  fVar38 = fVar38 + *pfVar19 * 0.299 + (float)uVar43 * (float)uVar10 +
                                    (float)((ulong)uVar43 >> 0x20) * (float)((ulong)uVar10 >> 0x20);
                } while (lVar30 != 0);
              }
              else {
                do {
                  uVar22 = uVar22 - 8;
                  pfVar19 = (float *)(lVar18 + (long)(iVar8 + -4) * 0xc);
                  pfVar32 = (float *)(lVar18 + (long)iVar8 * 0xc);
                  fVar38 = fVar38 + *pfVar19 * 0.299 + pfVar19[1] * 0.587 + pfVar19[2] * 0.114 +
                           pfVar19[3] * 0.299 + pfVar19[4] * 0.587 + pfVar19[5] * 0.114 +
                           pfVar19[6] * 0.299 + pfVar19[7] * 0.587 + pfVar19[8] * 0.114 +
                           pfVar19[9] * 0.299 + pfVar19[10] * 0.587 + pfVar19[0xb] * 0.114 +
                           *pfVar32 * 0.299 + pfVar32[1] * 0.587 + pfVar32[2] * 0.114 +
                           pfVar32[3] * 0.299 + pfVar32[4] * 0.587 + pfVar32[5] * 0.114 +
                           pfVar32[6] * 0.299 + pfVar32[7] * 0.587 + pfVar32[8] * 0.114 +
                           pfVar32[9] * 0.299 + pfVar32[10] * 0.587 + pfVar32[0xb] * 0.114;
                  iVar8 = iVar8 + 8;
                } while (uVar22 != 0);
                uVar22 = uVar24;
                if (uVar24 != uVar35) goto LAB_00137a24;
              }
              iVar25 = iVar25 + 1;
              iVar3 = iVar3 + iVar33;
              iVar4 = iVar4 + iVar33;
            } while (iVar25 != iVar34);
            iVar1 = iVar1 + uVar5;
            iVar2 = iVar2 + uVar5;
            *(float *)((long)__s + lVar11 * 4 + lVar28 * 0x40) = (fVar38 / fVar36) * 255.0;
            lVar11 = lVar11 + 1;
          } while (lVar11 != 0x10);
          lVar28 = lVar28 + 1;
          iVar21 = iVar21 + iVar6;
          iVar16 = iVar16 + iVar6;
        } while (lVar28 != 0x10);
      }
      else {
        iVar6 = iVar33 * iVar34;
        iVar16 = 0;
        lVar18 = 0;
        uVar24 = uVar35 & 0x7fffff0;
        iVar21 = 8;
        do {
          lVar11 = 0;
          iVar1 = iVar21;
          iVar2 = iVar16;
          do {
            fVar38 = 0.0;
            iVar25 = 0;
            iVar3 = iVar1;
            iVar4 = iVar2;
            do {
              if ((uVar5 < 0x10) ||
                 (iVar26 = (int)lVar18 * iVar6 + (int)lVar11 * uVar5 + iVar33 * iVar25,
                 uVar22 = uVar24, iVar8 = iVar3,
                 iVar26 + (int)(uVar35 - 1) < iVar26 || uVar35 - 1 >> 0x20 != 0)) {
                uVar22 = 0;
LAB_001372d4:
                iVar26 = iVar4 + (int)uVar22;
                lVar30 = uVar35 - uVar22;
                do {
                  puVar31 = (ushort *)(lVar28 + (long)iVar26 * 6);
                  lVar30 = lVar30 + -1;
                  iVar26 = iVar26 + 1;
                  fVar39 = (float)NEON_ucvtf((uint)*puVar31);
                  fVar45 = (float)NEON_ucvtf((uint)puVar31[1]);
                  fVar46 = (float)NEON_ucvtf((uint)puVar31[2]);
                  fVar38 = fVar38 + (fVar39 / 65535.0) * 0.299 + (fVar45 / 65535.0) * 0.587 +
                                    (fVar46 / 65535.0) * 0.114;
                } while (lVar30 != 0);
              }
              else {
                do {
                  uVar22 = uVar22 - 0x10;
                  puVar31 = (ushort *)(lVar28 + (long)(iVar8 + -8) * 6);
                  puVar27 = (ushort *)(lVar28 + (long)iVar8 * 6);
                  auVar40._2_2_ = 0;
                  auVar40._0_2_ = puVar31[0xc];
                  auVar40._4_2_ = puVar31[0xf];
                  auVar40._6_2_ = 0;
                  auVar40._8_2_ = puVar31[0x12];
                  auVar40._10_2_ = 0;
                  auVar40._12_2_ = puVar31[0x15];
                  auVar40._14_2_ = 0;
                  auVar52._2_2_ = 0;
                  auVar52._0_2_ = puVar31[1];
                  auVar52._4_2_ = puVar31[4];
                  auVar52._6_2_ = 0;
                  auVar52._8_2_ = puVar31[7];
                  auVar52._10_2_ = 0;
                  auVar52._12_2_ = puVar31[10];
                  auVar52._14_2_ = 0;
                  auVar55._2_2_ = 0;
                  auVar55._0_2_ = puVar31[2];
                  auVar55._4_2_ = puVar31[5];
                  auVar55._6_2_ = 0;
                  auVar55._8_2_ = puVar31[8];
                  auVar55._10_2_ = 0;
                  auVar55._12_2_ = puVar31[0xb];
                  auVar55._14_2_ = 0;
                  auVar50._2_2_ = 0;
                  auVar50._0_2_ = puVar31[0xd];
                  auVar50._4_2_ = puVar31[0x10];
                  auVar50._6_2_ = 0;
                  auVar50._8_2_ = puVar31[0x13];
                  auVar50._10_2_ = 0;
                  auVar50._12_2_ = puVar31[0x16];
                  auVar50._14_2_ = 0;
                  auVar40 = NEON_ucvtf(auVar40,4);
                  auVar54 = NEON_ucvtf(auVar52,4);
                  auVar55 = NEON_ucvtf(auVar55,4);
                  auVar52 = NEON_ucvtf(auVar50,4);
                  auVar47._2_2_ = 0;
                  auVar47._0_2_ = *puVar27;
                  auVar47._4_2_ = puVar27[3];
                  auVar47._6_2_ = 0;
                  auVar47._8_2_ = puVar27[6];
                  auVar47._10_2_ = 0;
                  auVar47._12_2_ = puVar27[9];
                  auVar47._14_2_ = 0;
                  auVar41._2_2_ = 0;
                  auVar41._0_2_ = *puVar31;
                  auVar41._4_2_ = puVar31[3];
                  auVar41._6_2_ = 0;
                  auVar41._8_2_ = puVar31[6];
                  auVar41._10_2_ = 0;
                  auVar41._12_2_ = puVar31[9];
                  auVar41._14_2_ = 0;
                  auVar48._2_2_ = 0;
                  auVar48._0_2_ = puVar31[0xe];
                  auVar48._4_2_ = puVar31[0x11];
                  auVar48._6_2_ = 0;
                  auVar48._8_2_ = puVar31[0x14];
                  auVar48._10_2_ = 0;
                  auVar48._12_2_ = puVar31[0x17];
                  auVar48._14_2_ = 0;
                  auVar47 = NEON_ucvtf(auVar47,4);
                  auVar41 = NEON_ucvtf(auVar41,4);
                  auVar48 = NEON_ucvtf(auVar48,4);
                  auVar42._2_2_ = 0;
                  auVar42._0_2_ = puVar27[0xc];
                  auVar42._4_2_ = puVar27[0xf];
                  auVar42._6_2_ = 0;
                  auVar42._8_2_ = puVar27[0x12];
                  auVar42._10_2_ = 0;
                  auVar42._12_2_ = puVar27[0x15];
                  auVar42._14_2_ = 0;
                  auVar44._2_2_ = 0;
                  auVar44._0_2_ = puVar27[0xe];
                  auVar44._4_2_ = puVar27[0x11];
                  auVar44._6_2_ = 0;
                  auVar44._8_2_ = puVar27[0x14];
                  auVar44._10_2_ = 0;
                  auVar44._12_2_ = puVar27[0x17];
                  auVar44._14_2_ = 0;
                  auVar42 = NEON_ucvtf(auVar42,4);
                  auVar44 = NEON_ucvtf(auVar44,4);
                  auVar49._2_2_ = 0;
                  auVar49._0_2_ = puVar27[1];
                  auVar49._4_2_ = puVar27[4];
                  auVar49._6_2_ = 0;
                  auVar49._8_2_ = puVar27[7];
                  auVar49._10_2_ = 0;
                  auVar49._12_2_ = puVar27[10];
                  auVar49._14_2_ = 0;
                  auVar50 = NEON_ucvtf(auVar49,4);
                  auVar53._2_2_ = 0;
                  auVar53._0_2_ = puVar27[0xd];
                  auVar53._4_2_ = puVar27[0x10];
                  auVar53._6_2_ = 0;
                  auVar53._8_2_ = puVar27[0x13];
                  auVar53._10_2_ = 0;
                  auVar53._12_2_ = puVar27[0x16];
                  auVar53._14_2_ = 0;
                  auVar51._2_2_ = 0;
                  auVar51._0_2_ = puVar27[2];
                  auVar51._4_2_ = puVar27[5];
                  auVar51._6_2_ = 0;
                  auVar51._8_2_ = puVar27[8];
                  auVar51._10_2_ = 0;
                  auVar51._12_2_ = puVar27[0xb];
                  auVar51._14_2_ = 0;
                  auVar51 = NEON_ucvtf(auVar51,4);
                  auVar49 = NEON_ucvtf(auVar53,4);
                  fVar38 = fVar38 + (auVar41._0_4_ / 65535.0) * 0.299 +
                                    (auVar54._0_4_ / 65535.0) * 0.587 +
                                    (auVar55._0_4_ / 65535.0) * 0.114 +
                           (auVar41._4_4_ / 65535.0) * 0.299 + (auVar54._4_4_ / 65535.0) * 0.587 +
                           (auVar55._4_4_ / 65535.0) * 0.114 +
                           (auVar41._8_4_ / 65535.0) * 0.299 + (auVar54._8_4_ / 65535.0) * 0.587 +
                           (auVar55._8_4_ / 65535.0) * 0.114 +
                           (auVar41._12_4_ / 65535.0) * 0.299 + (auVar54._12_4_ / 65535.0) * 0.587 +
                           (auVar55._12_4_ / 65535.0) * 0.114 +
                           (auVar40._0_4_ / 65535.0) * 0.299 + (auVar52._0_4_ / 65535.0) * 0.587 +
                           (auVar48._0_4_ / 65535.0) * 0.114 +
                           (auVar40._4_4_ / 65535.0) * 0.299 + (auVar52._4_4_ / 65535.0) * 0.587 +
                           (auVar48._4_4_ / 65535.0) * 0.114 +
                           (auVar40._8_4_ / 65535.0) * 0.299 + (auVar52._8_4_ / 65535.0) * 0.587 +
                           (auVar48._8_4_ / 65535.0) * 0.114 +
                           (auVar40._12_4_ / 65535.0) * 0.299 + (auVar52._12_4_ / 65535.0) * 0.587 +
                           (auVar48._12_4_ / 65535.0) * 0.114 +
                           (auVar47._0_4_ / 65535.0) * 0.299 + (auVar50._0_4_ / 65535.0) * 0.587 +
                           (auVar51._0_4_ / 65535.0) * 0.114 +
                           (auVar47._4_4_ / 65535.0) * 0.299 + (auVar50._4_4_ / 65535.0) * 0.587 +
                           (auVar51._4_4_ / 65535.0) * 0.114 +
                           (auVar47._8_4_ / 65535.0) * 0.299 + (auVar50._8_4_ / 65535.0) * 0.587 +
                           (auVar51._8_4_ / 65535.0) * 0.114 +
                           (auVar47._12_4_ / 65535.0) * 0.299 + (auVar50._12_4_ / 65535.0) * 0.587 +
                           (auVar51._12_4_ / 65535.0) * 0.114 +
                           (auVar42._0_4_ / 65535.0) * 0.299 + (auVar49._0_4_ / 65535.0) * 0.587 +
                           (auVar44._0_4_ / 65535.0) * 0.114 +
                           (auVar42._4_4_ / 65535.0) * 0.299 + (auVar49._4_4_ / 65535.0) * 0.587 +
                           (auVar44._4_4_ / 65535.0) * 0.114 +
                           (auVar42._8_4_ / 65535.0) * 0.299 + (auVar49._8_4_ / 65535.0) * 0.587 +
                           (auVar44._8_4_ / 65535.0) * 0.114 +
                           (auVar42._12_4_ / 65535.0) * 0.299 + (auVar49._12_4_ / 65535.0) * 0.587 +
                           (auVar44._12_4_ / 65535.0) * 0.114;
                  iVar8 = iVar8 + 0x10;
                } while (uVar22 != 0);
                uVar22 = uVar24;
                if (uVar24 != uVar35) goto LAB_001372d4;
              }
              iVar25 = iVar25 + 1;
              iVar3 = iVar3 + iVar33;
              iVar4 = iVar4 + iVar33;
            } while (iVar25 != iVar34);
            iVar1 = iVar1 + uVar5;
            iVar2 = iVar2 + uVar5;
            *(float *)((long)__s + lVar11 * 4 + lVar18 * 0x40) = (fVar38 / fVar36) * 255.0;
            lVar11 = lVar11 + 1;
          } while (lVar11 != 0x10);
          lVar18 = lVar18 + 1;
          iVar21 = iVar21 + iVar6;
          iVar16 = iVar16 + iVar6;
        } while (lVar18 != 0x10);
      }
      goto LAB_001375f0;
    }
    uVar10 = CONCAT44(fVar38,fVar38);
    uVar43 = CONCAT44(fVar38,fVar38);
    __s[1] = uVar43;
    *__s = uVar10;
    __s[3] = uVar43;
    __s[2] = uVar10;
    __s[5] = uVar43;
    __s[4] = uVar10;
    __s[7] = uVar43;
    __s[6] = uVar10;
    __s[9] = uVar43;
    __s[8] = uVar10;
    __s[0xb] = uVar43;
    __s[10] = uVar10;
    __s[0xd] = uVar43;
    __s[0xc] = uVar10;
    __s[0xf] = uVar43;
    __s[0xe] = uVar10;
    __s[0x11] = uVar43;
    __s[0x10] = uVar10;
    __s[0x13] = uVar43;
    __s[0x12] = uVar10;
    __s[0x15] = uVar43;
    __s[0x14] = uVar10;
    __s[0x17] = uVar43;
    __s[0x16] = uVar10;
    __s[0x19] = uVar43;
    __s[0x18] = uVar10;
    __s[0x1b] = uVar43;
    __s[0x1a] = uVar10;
    __s[0x1d] = uVar43;
    __s[0x1c] = uVar10;
    __s[0x1f] = uVar43;
    __s[0x1e] = uVar10;
    __s[0x21] = uVar43;
    __s[0x20] = uVar10;
    __s[0x23] = uVar43;
    __s[0x22] = uVar10;
    __s[0x25] = uVar43;
    __s[0x24] = uVar10;
    __s[0x27] = uVar43;
    __s[0x26] = uVar10;
    __s[0x29] = uVar43;
    __s[0x28] = uVar10;
    __s[0x2b] = uVar43;
    __s[0x2a] = uVar10;
    __s[0x2d] = uVar43;
    __s[0x2c] = uVar10;
    __s[0x2f] = uVar43;
    __s[0x2e] = uVar10;
    __s[0x31] = uVar43;
    __s[0x30] = uVar10;
    __s[0x33] = uVar43;
    __s[0x32] = uVar10;
    __s[0x35] = uVar43;
    __s[0x34] = uVar10;
    __s[0x37] = uVar43;
    __s[0x36] = uVar10;
    __s[0x39] = uVar43;
    __s[0x38] = uVar10;
    __s[0x3b] = uVar43;
    __s[0x3a] = uVar10;
    __s[0x3d] = uVar43;
    __s[0x3c] = uVar10;
    __s[0x3f] = uVar43;
    __s[0x3e] = uVar10;
    __s[0x41] = uVar43;
    __s[0x40] = uVar10;
    __s[0x43] = uVar43;
    __s[0x42] = uVar10;
    __s[0x45] = uVar43;
    __s[0x44] = uVar10;
    __s[0x47] = uVar43;
    __s[0x46] = uVar10;
    __s[0x49] = uVar43;
    __s[0x48] = uVar10;
    __s[0x4b] = uVar43;
    __s[0x4a] = uVar10;
    __s[0x4d] = uVar43;
    __s[0x4c] = uVar10;
    __s[0x4f] = uVar43;
    __s[0x4e] = uVar10;
    __s[0x51] = uVar43;
    __s[0x50] = uVar10;
    __s[0x53] = uVar43;
    __s[0x52] = uVar10;
    __s[0x55] = uVar43;
    __s[0x54] = uVar10;
    __s[0x57] = uVar43;
    __s[0x56] = uVar10;
    __s[0x59] = uVar43;
    __s[0x58] = uVar10;
    __s[0x5b] = uVar43;
    __s[0x5a] = uVar10;
    __s[0x5d] = uVar43;
    __s[0x5c] = uVar10;
    __s[0x5f] = uVar43;
    __s[0x5e] = uVar10;
    __s[0x61] = uVar43;
    __s[0x60] = uVar10;
    __s[99] = uVar43;
    __s[0x62] = uVar10;
    __s[0x65] = uVar43;
    __s[100] = uVar10;
    __s[0x67] = uVar43;
    __s[0x66] = uVar10;
    __s[0x69] = uVar43;
    __s[0x68] = uVar10;
    __s[0x6b] = uVar43;
    __s[0x6a] = uVar10;
    __s[0x6d] = uVar43;
    __s[0x6c] = uVar10;
    __s[0x6f] = uVar43;
    __s[0x6e] = uVar10;
    __s[0x71] = uVar43;
    __s[0x70] = uVar10;
    __s[0x73] = uVar43;
    __s[0x72] = uVar10;
    __s[0x75] = uVar43;
    __s[0x74] = uVar10;
    __s[0x77] = uVar43;
    __s[0x76] = uVar10;
    __s[0x79] = uVar43;
    __s[0x78] = uVar10;
  }
  uVar10 = CONCAT44(fVar38,fVar38);
  __s[0x7b] = uVar10;
  __s[0x7a] = uVar10;
  __s[0x7d] = uVar10;
  __s[0x7c] = uVar10;
  __s[0x7f] = uVar10;
  __s[0x7e] = uVar10;
LAB_001375f0:
  local_80 = puVar29;
  if ((0 < iVar14) && (0 < iVar33)) {
    iVar34 = 0;
    puVar23 = puVar29;
    do {
      if (0 < iVar33) {
        iVar14 = 0;
        puVar15 = puVar29;
        puVar12 = __s;
        do {
          while( true ) {
            iVar21 = iVar14 + iVar33 * iVar34;
            lVar28 = (long)iVar21 + (long)iVar21 * 2;
            if (*(long *)(param_3 + 8) == *(long *)(param_3 + 10)) {
              pfVar19 = (float *)(*(long *)(param_3 + 2) + lVar28 * 4);
              fVar36 = *pfVar19;
              fVar39 = pfVar19[1];
              fVar38 = pfVar19[2];
            }
            else {
              puVar31 = (ushort *)(*(long *)(param_3 + 8) + lVar28 * 2);
              fVar36 = (float)NEON_ucvtf((uint)*puVar31);
              fVar39 = (float)NEON_ucvtf((uint)puVar31[1]);
              fVar38 = (float)NEON_ucvtf((uint)puVar31[2]);
              fVar36 = fVar36 / 65535.0;
              fVar39 = fVar39 / 65535.0;
              fVar38 = fVar38 / 65535.0;
            }
            fVar38 = (fVar39 * 0.587 + fVar36 * 0.299 + fVar38 * 0.114) * 255.0;
            if (puVar15 < puVar23) break;
            lVar18 = (long)puVar15 - (long)puVar12;
            lVar28 = lVar18 >> 2;
            uVar35 = lVar28 + 1;
            if (uVar35 >> 0x3e != 0) {
                    /* try { // try from 00137b10 to 00137b1f has its CatchHandler @ 00137b40 */
              std::__ndk1::vector<float,std::__ndk1::allocator<float>>::
              __throw_length_error_abi_ne180000_();
LAB_00137b18:
                    /* WARNING: Subroutine does not return */
              std::__throw_bad_array_new_length_abi_ne180000_();
            }
            uVar24 = (long)puVar23 - (long)puVar12 >> 1;
            if (uVar24 <= uVar35) {
              uVar24 = uVar35;
            }
            if (0x7ffffffffffffffb < (ulong)((long)puVar23 - (long)puVar12)) {
              uVar24 = 0x3fffffffffffffff;
            }
            if (uVar24 == 0) {
              pvVar9 = (void *)0x0;
              puVar17 = (undefined8 *)(lVar28 * 4);
              lVar28 = (long)puVar15 - (long)puVar12;
              puVar29 = (undefined8 *)((long)puVar17 + 4);
              *(float *)puVar17 = fVar38;
              if (lVar28 != 0) goto LAB_00137774;
LAB_001377d8:
              puVar23 = (undefined8 *)((long)pvVar9 + uVar24 * 4);
              __s = puVar17;
            }
            else {
              if (uVar24 >> 0x3e != 0) goto LAB_00137b18;
                    /* try { // try from 00137748 to 0013774b has its CatchHandler @ 00137b30 */
              pvVar9 = operator_new(uVar24 << 2);
              puVar17 = (undefined8 *)((long)pvVar9 + lVar28 * 4);
              lVar28 = (long)puVar15 - (long)puVar12;
              puVar29 = (undefined8 *)((long)puVar17 + 4);
              *(float *)puVar17 = fVar38;
              if (lVar28 == 0) goto LAB_001377d8;
LAB_00137774:
              if (lVar28 - 4U < 0xac) {
LAB_00137788:
                do {
                  puVar15 = (undefined8 *)((long)puVar15 + -4);
                  __s = (undefined8 *)((long)puVar17 + -4);
                  *(float *)__s = *(float *)puVar15;
                  puVar17 = __s;
                } while (puVar15 != puVar12);
              }
              else {
                pfVar19 = (float *)((long)puVar15 + -4);
                uVar22 = (long)pvVar9 + lVar18 + -4;
                uVar35 = (long)pfVar19 - (long)puVar12 & 0xfffffffffffffffc;
                if (((uVar22 < uVar22 - uVar35) || (pfVar19 < (float *)((long)pfVar19 - uVar35))) ||
                   ((ulong)((long)puVar15 + (-lVar18 - (long)pvVar9)) < 0x20)) goto LAB_00137788;
                uVar35 = (lVar28 - 4U >> 2) + 1;
                uVar20 = uVar35 & 0x7ffffffffffffff8;
                __s = (undefined8 *)((long)puVar17 + uVar20 * -4);
                puVar17 = puVar17 + -2;
                puVar23 = puVar15 + -2;
                uVar22 = uVar20;
                do {
                  puVar7 = puVar23 + -1;
                  uVar37 = puVar23[-2];
                  uVar43 = puVar23[1];
                  uVar10 = *puVar23;
                  uVar22 = uVar22 - 8;
                  puVar23 = puVar23 + -4;
                  puVar17[-1] = *puVar7;
                  puVar17[-2] = uVar37;
                  puVar17[1] = uVar43;
                  *puVar17 = uVar10;
                  puVar17 = puVar17 + -4;
                } while (uVar22 != 0);
                puVar15 = (undefined8 *)((long)puVar15 + uVar20 * -4);
                puVar17 = __s;
                if (uVar35 != uVar20) goto LAB_00137788;
              }
              puVar23 = (undefined8 *)((long)pvVar9 + uVar24 * 4);
            }
            if (puVar12 != (undefined8 *)0x0) {
              operator_delete(puVar12);
              iVar33 = *param_3;
            }
            iVar14 = iVar14 + iVar13;
            puVar15 = puVar29;
            puVar12 = __s;
            if (iVar33 <= iVar14) goto LAB_00137638;
          }
          puVar29 = (undefined8 *)((long)puVar15 + 4);
          *(float *)puVar15 = fVar38;
          iVar14 = iVar14 + iVar13;
          puVar15 = puVar29;
          __s = puVar12;
        } while (iVar14 < iVar33);
LAB_00137638:
        iVar14 = param_3[1];
        local_80 = puVar29;
      }
      iVar34 = iVar34 + iVar13;
    } while (iVar34 < iVar14);
  }
                    /* try { // try from 0013789c to 001378a7 has its CatchHandler @ 00137b20 */
  std::__ndk1::__sort<std::__ndk1::__less<float,float>&,float*>
            ((float *)(__s + 0x80),(float *)puVar29,&_Stack_61);
  uVar35 = (ulong)((long)local_80 - (long)__s) >> 2;
                    /* try { // try from 001378c0 to 001378ef has its CatchHandler @ 00137b2c */
  uVar10 = (**(code **)(*param_1 + 0x5a8))(param_1,uVar35 & 0xffffffff);
  (**(code **)(*param_1 + 0x6a8))(param_1,uVar10,0,uVar35 & 0xffffffff,__s);
  if (__s != (undefined8 *)0x0) {
    operator_delete(__s);
  }
  return uVar10;
}



/* 00137c18 Java_com_codex_fullm9_NativeM9_rawRender */

void Java_com_codex_fullm9_NativeM9_rawRender
               (long *param_1,undefined8 param_2,uint *param_3,undefined8 param_4,undefined8 param_5
               ,_jobject *param_6,_jobject *param_7)

{
  long lVar1;
  uchar *puVar2;
  ushort *puVar3;
  float *pfVar4;
  undefined *puVar5;
  uchar uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  uchar *__s;
  runtime_error *prVar10;
  uint uVar11;
  ulong uVar12;
  uint uVar13;
  ulong uVar14;
  long lVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float local_a22c;
  float local_a228;
  float local_a224;
  undefined8 local_a220;
  undefined8 uStack_a218;
  uint local_a210;
  uint local_a20c;
  int local_a208;
  long local_a1f8;
  undefined8 local_a1f0;
  undefined8 uStack_a1e8;
  uint local_a1e0;
  uint local_a1dc;
  int local_a1d8;
  long local_a1c8;
  undefined4 local_a1c0 [2];
  undefined *local_a1b8;
  undefined *puStack_a1b0;
  undefined *local_a1a8;
  undefined *puStack_a1a0;
  undefined *local_a198;
  undefined *puStack_a190;
  undefined4 local_a188 [2];
  undefined *local_a180;
  undefined *puStack_a178;
  undefined *local_a170;
  undefined *puStack_a168;
  undefined *local_a160;
  undefined *puStack_a158;
  undefined4 local_a14c;
  undefined auStack_a148 [36];
  undefined auStack_a124 [1536];
  undefined auStack_9b24 [1536];
  undefined auStack_9524 [1028];
  undefined auStack_9120 [16384];
  undefined auStack_5120 [56];
  undefined4 local_50e8;
  undefined auStack_50e4 [36];
  undefined auStack_50c0 [1536];
  undefined auStack_4ac0 [1536];
  undefined auStack_44c0 [1028];
  undefined auStack_40bc [16384];
  undefined auStack_bc [56];
  float local_84;
  float local_80;
  float local_7c;
  
                    /* try { // try from 00137c68 to 00137c8f has its CatchHandler @ 00138264 */
  iVar9 = (**(code **)(*param_1 + 0x558))(param_1,param_4);
  if ((iVar9 != 0x1419) ||
     (iVar9 = (**(code **)(*param_1 + 0x558))(param_1,param_5), iVar9 != 0x1419)) {
    prVar10 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013819c to 001381a7 has its CatchHandler @ 00138244 */
    std::runtime_error::runtime_error(prVar10,"IPE parameter size");
                    /* try { // try from 001381a8 to 001381c7 has its CatchHandler @ 00138264 */
                    /* WARNING: Subroutine does not return */
    __cxa_throw(prVar10,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
  }
                    /* try { // try from 00137ca4 to 00137ce3 has its CatchHandler @ 00138260 */
  (**(code **)(*param_1 + 0x668))(param_1,param_4,0,0x1419,&local_50e8);
  (**(code **)(*param_1 + 0x668))(param_1,param_5,0,0x1419,&local_a14c);
  local_a180 = auStack_50e4;
  puStack_a178 = auStack_50c0;
  local_a170 = auStack_4ac0;
  puStack_a168 = auStack_44c0;
  local_a160 = auStack_40bc;
  puStack_a158 = auStack_bc;
  local_a188[0] = local_50e8;
  local_a1b8 = auStack_a148;
  puStack_a1b0 = auStack_a124;
  local_a1a8 = auStack_9b24;
  puStack_a1a0 = auStack_9524;
  local_a198 = auStack_9120;
  puStack_a190 = auStack_5120;
  local_a1c0[0] = local_a14c;
                    /* try { // try from 00137d50 to 00137d5f has its CatchHandler @ 00138240 */
  Pixels::Pixels((Pixels *)&local_a1f0,(_JNIEnv *)param_1,param_6);
                    /* try { // try from 00137d60 to 00137d6f has its CatchHandler @ 00138234 */
  Pixels::Pixels((Pixels *)&local_a220,(_JNIEnv *)param_1,param_7);
  uVar12 = (ulong)local_a1e0;
  if ((local_a1e0 != *param_3) || (local_a1dc != param_3[1])) {
    prVar10 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 001381d8 to 001381e3 has its CatchHandler @ 00138230 */
    std::runtime_error::runtime_error(prVar10,"RAW frame size");
                    /* try { // try from 001381e4 to 00138207 has its CatchHandler @ 0013822c */
                    /* WARNING: Subroutine does not return */
    __cxa_throw(prVar10,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
  }
  if ((0 < (int)local_a1dc) && (0 < (int)local_a1e0)) {
    iVar9 = 0;
    do {
      if (0 < (int)uVar12) {
        uVar14 = 0;
        lVar15 = 0;
        do {
          iVar7 = (int)lVar15 + iVar9 * (int)uVar12;
          lVar1 = (long)iVar7 + (long)iVar7 * 2;
          if (*(long *)(param_3 + 8) == *(long *)(param_3 + 10)) {
            pfVar4 = (float *)(*(long *)(param_3 + 2) + lVar1 * 4);
            local_a22c = *pfVar4;
            local_a228 = pfVar4[1];
            local_a224 = pfVar4[2];
          }
          else {
            puVar3 = (ushort *)(*(long *)(param_3 + 8) + lVar1 * 2);
            local_a22c = (float)NEON_ucvtf((uint)*puVar3);
            local_a22c = local_a22c / 65535.0;
            local_a228 = (float)NEON_ucvtf((uint)puVar3[1]);
            local_a228 = local_a228 / 65535.0;
            local_a224 = (float)NEON_ucvtf((uint)puVar3[2]);
            local_a224 = local_a224 / 65535.0;
          }
                    /* try { // try from 00137e8c to 00137e9b has its CatchHandler @ 00138270 */
          m9::Ipe::yuv((Ipe *)local_a188,&local_a22c,&local_84);
          fVar18 = local_84 + local_7c * 1.402;
          if (1.0 <= fVar18) {
            fVar18 = 1.0;
          }
          if (fVar18 <= 0.0) {
            fVar18 = 0.0;
          }
          fVar16 = local_84 + local_80 * 1.772;
          if (1.0 <= fVar16) {
            fVar16 = 1.0;
          }
          if (fVar16 <= 0.0) {
            fVar16 = 0.0;
          }
          fVar18 = fVar18 * 255.0;
          if (ABS(fVar18) == INFINITY) goto LAB_00138154;
          fVar17 = local_84 + local_80 * -0.344136 + local_7c * -0.714136;
          if (1.0 <= fVar17) {
            fVar17 = 1.0;
LAB_00137f44:
            if ((float)(int)fVar18 < 255.0) goto LAB_00137f54;
LAB_0013802c:
            fVar18 = 255.0;
          }
          else {
            if (0.0 < fVar17) goto LAB_00137f44;
            fVar17 = 0.0;
            if (255.0 <= (float)(int)fVar18) goto LAB_0013802c;
LAB_00137f54:
            fVar18 = (float)(int)fVar18;
            if (fVar18 <= 0.0) {
              fVar18 = 0.0;
            }
          }
          puVar5 = (undefined *)
                   (local_a1c8 + (uVar14 & 0xfffffffc) + (ulong)(uint)(local_a1d8 * iVar9));
          *puVar5 = (char)(int)fVar18;
          if (ABS(fVar17 * 255.0) == INFINITY) {
LAB_00138154:
            prVar10 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00138160 to 0013816b has its CatchHandler @ 00138288 */
            std::runtime_error::runtime_error(prVar10,"Non-finite image sample");
                    /* try { // try from 0013816c to 0013818f has its CatchHandler @ 0013827c */
                    /* WARNING: Subroutine does not return */
            __cxa_throw(prVar10,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
          }
          fVar18 = (float)(int)(fVar17 * 255.0);
          if (255.0 <= fVar18) {
            fVar18 = 255.0;
          }
          if (fVar18 <= 0.0) {
            fVar18 = 0.0;
          }
          puVar5[1] = (char)(int)fVar18;
          if (ABS(fVar16 * 255.0) == INFINITY) goto LAB_00138154;
          fVar18 = (float)(int)(fVar16 * 255.0);
          if (255.0 <= fVar18) {
            fVar18 = 255.0;
          }
          if (fVar18 <= 0.0) {
            fVar18 = 0.0;
          }
          puVar5[3] = 0xff;
          lVar15 = lVar15 + 1;
          uVar14 = uVar14 + 4;
          puVar5[2] = (char)(int)fVar18;
          uVar12 = (ulong)(int)*param_3;
        } while (lVar15 < (long)uVar12);
        local_a1dc = param_3[1];
      }
      iVar9 = iVar9 + 1;
    } while (iVar9 < (int)local_a1dc);
  }
  uVar8 = local_a20c;
  uVar13 = local_a210;
  uVar11 = local_a20c * local_a210;
  if (uVar11 == 0) {
    __s = (uchar *)0x0;
  }
  else {
                    /* try { // try from 0013804c to 00138053 has its CatchHandler @ 00138210 */
    __s = (uchar *)operator_new((ulong)uVar11);
    memset(__s,0,(ulong)uVar11);
  }
                    /* try { // try from 0013806c to 00138083 has its CatchHandler @ 00138214 */
  m9::gainmap((Raw *)param_3,(Ipe *)local_a1c0,uVar13,uVar8,__s);
  if ((local_a20c != 0) && (local_a210 != 0)) {
    uVar11 = 0;
    do {
      if (local_a210 != 0) {
        iVar9 = 0;
        uVar13 = 0;
        do {
          uVar8 = uVar13 + uVar11 * local_a210;
          uVar13 = uVar13 + 1;
          uVar6 = __s[uVar8];
          puVar2 = (uchar *)(local_a1f8 + (ulong)(local_a208 * uVar11) + (long)iVar9);
          iVar9 = iVar9 + 4;
          puVar2[2] = uVar6;
          puVar2[1] = uVar6;
          *puVar2 = uVar6;
          puVar2[3] = 0xff;
        } while (uVar13 < local_a210);
      }
      uVar11 = uVar11 + 1;
    } while (uVar11 < local_a20c);
  }
  if (__s != (uchar *)0x0) {
    operator_delete(__s);
  }
  if (local_a1f8 != 0) {
                    /* try { // try from 00138118 to 0013811b has its CatchHandler @ 0013820c */
    AndroidBitmap_unlockPixels(local_a220,uStack_a218);
  }
  if (local_a1c8 != 0) {
                    /* try { // try from 00138128 to 0013812b has its CatchHandler @ 00138208 */
    AndroidBitmap_unlockPixels(local_a1f0,uStack_a1e8);
  }
  return;
}



/* 0013838c Java_com_codex_fullm9_NativeM9_rawClose */

void Java_com_codex_fullm9_NativeM9_rawClose(undefined8 param_1,undefined8 param_2,void *param_3)

{
  void *pvVar1;
  
  if (param_3 != (void *)0x0) {
    pvVar1 = *(void **)((long)param_3 + 0x20);
    if (pvVar1 != (void *)0x0) {
      *(void **)((long)param_3 + 0x28) = pvVar1;
      operator_delete(pvVar1);
    }
    pvVar1 = *(void **)((long)param_3 + 8);
    if (pvVar1 != (void *)0x0) {
      *(void **)((long)param_3 + 0x10) = pvVar1;
      operator_delete(pvVar1);
    }
    operator_delete(param_3);
    return;
  }
  return;
}



/* 001383d4 Java_com_codex_fullm9_NativeM9_restoreDetail */

void Java_com_codex_fullm9_NativeM9_restoreDetail
               (_JNIEnv *param_1,undefined8 param_2,_jobject *param_3,_jobject *param_4,
               _jobject *param_5)

{
  byte *pbVar1;
  byte *pbVar2;
  uint uVar3;
  byte *pbVar4;
  byte *pbVar5;
  undefined *puVar6;
  byte *pbVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  undefined8 *puVar13;
  uint uVar14;
  void *pvVar15;
  runtime_error *prVar16;
  int iVar17;
  ulong uVar18;
  uint uVar19;
  float *pfVar20;
  float *pfVar21;
  uint uVar22;
  float *pfVar23;
  ulong uVar24;
  undefined8 *puVar25;
  undefined8 *puVar26;
  long lVar27;
  ulong uVar28;
  uint uVar29;
  ulong uVar30;
  long lVar31;
  int iVar32;
  long lVar33;
  float *pfVar34;
  undefined8 uVar35;
  undefined8 uVar36;
  float fVar37;
  undefined8 uVar38;
  undefined8 uVar39;
  undefined8 uVar40;
  float fVar41;
  float fVar42;
  float fVar43;
  float fVar44;
  float fVar45;
  float fVar46;
  float fVar47;
  float fVar48;
  undefined8 uVar49;
  float fVar50;
  float fVar51;
  float fVar52;
  float fVar53;
  float fVar54;
  float fVar55;
  float fVar56;
  float fVar57;
  float fVar58;
  float fVar59;
  float fVar60;
  float fVar61;
  undefined8 uVar62;
  float fVar63;
  float fVar64;
  float fVar65;
  float fVar66;
  float fVar67;
  float fVar68;
  float fVar69;
  float fVar70;
  float fVar71;
  float fVar72;
  float fVar73;
  float fVar74;
  float fVar75;
  float fVar76;
  float fVar77;
  float fVar78;
  float fVar79;
  float *local_158;
  float *local_148;
  undefined8 local_140;
  undefined8 uStack_138;
  uint local_130;
  uint local_12c;
  int local_128;
  long local_118;
  undefined8 local_110;
  undefined8 uStack_108;
  uint local_100;
  uint uStack_fc;
  int local_f8;
  long local_e8;
  undefined8 local_e0;
  undefined8 uStack_d8;
  uint local_d0;
  uint local_cc;
  int local_c8;
  long local_b8;
  __less a_Stack_a9 [9];
  
                    /* try { // try from 00138410 to 0013841f has its CatchHandler @ 001390ec */
  Pixels::Pixels((Pixels *)&local_e0,param_1,param_3);
                    /* try { // try from 00138420 to 0013842f has its CatchHandler @ 001390e0 */
  Pixels::Pixels((Pixels *)&local_110,param_1,param_4);
                    /* try { // try from 00138430 to 0013843f has its CatchHandler @ 001390d4 */
  Pixels::Pixels((Pixels *)&local_140,param_1,param_5);
  if ((local_d0 != local_130) || (local_cc != local_12c)) {
    prVar16 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00139080 to 0013908b has its CatchHandler @ 001390c0 */
    std::runtime_error::runtime_error(prVar16,"Detail dimensions");
                    /* try { // try from 0013908c to 001390a3 has its CatchHandler @ 001390b4 */
                    /* WARNING: Subroutine does not return */
    __cxa_throw(prVar16,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
  }
  local_158 = (float *)0x0;
  local_148 = (float *)0x0;
  uVar22 = (uint)SQRT(((double)(ulong)local_d0 * (double)(ulong)local_cc) / 50000.0);
  if ((int)uVar22 < 2) {
    uVar22 = 1;
  }
  if ((2 < (int)local_cc) && (2 < (int)local_d0)) {
    pfVar34 = (float *)0x0;
    iVar32 = 1;
    uVar29 = local_d0;
    uVar19 = local_cc;
    do {
      if (2 < (int)uVar29) {
        lVar33 = 1;
        pfVar23 = pfVar34;
        do {
          while( true ) {
            uVar19 = (int)lVar33 * 4;
            lVar27 = local_b8 + (ulong)(uint)(local_c8 * iVar32);
            lVar31 = local_b8 + (ulong)uVar19;
            pbVar4 = (byte *)(lVar27 + (ulong)uVar19);
            pbVar1 = (byte *)(lVar27 + (int)(uVar19 - 4));
            pbVar2 = (byte *)(lVar27 + (int)(uVar19 + 4));
            fVar41 = (float)NEON_ucvtf((uint)*pbVar4);
            fVar37 = (float)NEON_ucvtf((uint)pbVar4[1]);
            fVar45 = (float)NEON_ucvtf((uint)*pbVar1);
            fVar46 = (float)NEON_ucvtf((uint)pbVar1[1]);
            fVar42 = (float)NEON_ucvtf((uint)pbVar4[2]);
            fVar48 = (float)NEON_ucvtf((uint)*pbVar2);
            fVar55 = (float)NEON_ucvtf((uint)pbVar2[1]);
            fVar58 = (float)NEON_ucvtf((uint)pbVar1[2]);
            pbVar1 = (byte *)(lVar31 + (ulong)(uint)(local_c8 * (iVar32 + -1)));
            pbVar4 = (byte *)(lVar31 + (ulong)(uint)(local_c8 * (iVar32 + 1)));
            fVar64 = (float)NEON_ucvtf((uint)pbVar2[2]);
            fVar57 = (float)NEON_ucvtf((uint)*pbVar1);
            fVar47 = (float)NEON_ucvtf((uint)pbVar1[1]);
            fVar43 = (float)NEON_ucvtf((uint)*pbVar4);
            fVar56 = (float)NEON_ucvtf((uint)pbVar4[1]);
            fVar59 = (float)NEON_ucvtf((uint)pbVar1[2]);
            fVar44 = (float)NEON_ucvtf((uint)pbVar4[2]);
            fVar37 = ABS(((((fVar41 * 0.299 + fVar37 * 0.587 + fVar42 * 0.114) * 4.0 -
                           (fVar45 * 0.299 + fVar46 * 0.587 + fVar58 * 0.114)) -
                          (fVar48 * 0.299 + fVar55 * 0.587 + fVar64 * 0.114)) -
                         (fVar57 * 0.299 + fVar47 * 0.587 + fVar59 * 0.114)) -
                         (fVar43 * 0.299 + fVar56 * 0.587 + fVar44 * 0.114));
            if (pfVar23 < local_148) break;
            lVar31 = (long)pfVar23 - (long)local_158;
            lVar27 = lVar31 >> 2;
            uVar18 = lVar27 + 1;
            if (uVar18 >> 0x3e != 0) {
                    /* try { // try from 00139068 to 00139073 has its CatchHandler @ 001390fc */
              std::__ndk1::vector<float,std::__ndk1::allocator<float>>::
              __throw_length_error_abi_ne180000_();
LAB_00139070:
                    /* WARNING: Subroutine does not return */
              std::__throw_bad_array_new_length_abi_ne180000_();
            }
            uVar24 = (long)local_148 - (long)local_158 >> 1;
            if (uVar24 <= uVar18) {
              uVar24 = uVar18;
            }
            if (0x7ffffffffffffffb < (ulong)((long)local_148 - (long)local_158)) {
              uVar24 = 0x3fffffffffffffff;
            }
            if (uVar24 == 0) {
              pvVar15 = (void *)0x0;
              pfVar20 = (float *)(lVar27 * 4);
              lVar27 = (long)pfVar23 - (long)local_158;
              pfVar34 = pfVar20 + 1;
              *pfVar20 = fVar37;
              if (lVar27 != 0) goto LAB_001386b8;
LAB_00138748:
              local_148 = (float *)((long)pvVar15 + uVar24 * 4);
              pfVar21 = pfVar20;
            }
            else {
              if (uVar24 >> 0x3e != 0) goto LAB_00139070;
                    /* try { // try from 001386a0 to 001386a3 has its CatchHandler @ 001390f8 */
              pvVar15 = operator_new(uVar24 << 2);
              pfVar20 = (float *)((long)pvVar15 + lVar27 * 4);
              lVar27 = (long)pfVar23 - (long)local_158;
              pfVar34 = pfVar20 + 1;
              *pfVar20 = fVar37;
              if (lVar27 == 0) goto LAB_00138748;
LAB_001386b8:
              if (lVar27 - 4U < 0xac) {
LAB_001386cc:
                do {
                  pfVar23 = pfVar23 + -1;
                  pfVar21 = pfVar20 + -1;
                  *pfVar21 = *pfVar23;
                  pfVar20 = pfVar21;
                } while (pfVar23 != local_158);
              }
              else {
                pfVar21 = pfVar23 + -1;
                uVar28 = (long)pvVar15 + lVar31 + -4;
                uVar18 = (long)pfVar21 - (long)local_158 & 0xfffffffffffffffc;
                if (((uVar28 < uVar28 - uVar18) || (pfVar21 < (float *)((long)pfVar21 - uVar18))) ||
                   ((ulong)((long)pfVar23 + (-lVar31 - (long)pvVar15)) < 0x20)) goto LAB_001386cc;
                puVar26 = (undefined8 *)(pfVar23 + -4);
                uVar18 = (lVar27 - 4U >> 2) + 1;
                uVar30 = uVar18 & 0x7ffffffffffffff8;
                pfVar23 = pfVar23 + -uVar30;
                pfVar21 = pfVar20 + -uVar30;
                puVar25 = (undefined8 *)(pfVar20 + -4);
                uVar28 = uVar30;
                do {
                  puVar13 = puVar26 + -1;
                  uVar38 = puVar26[-2];
                  uVar36 = puVar26[1];
                  uVar35 = *puVar26;
                  uVar28 = uVar28 - 8;
                  puVar26 = puVar26 + -4;
                  puVar25[-1] = *puVar13;
                  puVar25[-2] = uVar38;
                  puVar25[1] = uVar36;
                  *puVar25 = uVar35;
                  puVar25 = puVar25 + -4;
                } while (uVar28 != 0);
                pfVar20 = pfVar21;
                if (uVar18 != uVar30) goto LAB_001386cc;
              }
              local_148 = (float *)((long)pvVar15 + uVar24 * 4);
            }
            if (local_158 != (float *)0x0) {
              operator_delete(local_158);
              uVar29 = local_d0;
            }
            lVar33 = lVar33 + (ulong)uVar22;
            pfVar23 = pfVar34;
            local_158 = pfVar21;
            uVar19 = local_cc;
            if ((int)(uVar29 - 1) <= lVar33) goto LAB_001384d4;
          }
          pfVar34 = pfVar23 + 1;
          *pfVar23 = fVar37;
          lVar33 = lVar33 + (ulong)uVar22;
          pfVar23 = pfVar34;
          uVar19 = local_cc;
        } while (lVar33 < (int)(uVar29 - 1));
      }
LAB_001384d4:
      iVar32 = iVar32 + uVar22;
    } while (iVar32 < (int)(uVar19 - 1));
    if (local_158 != pfVar34) {
      pfVar23 = local_158 + ((long)pfVar34 - (long)local_158 >> 3);
      if (pfVar23 != pfVar34) {
                    /* try { // try from 00138804 to 00138813 has its CatchHandler @ 001390a4 */
        std::__ndk1::
        __nth_element_abi_ne180000_<std::__ndk1::_ClassicAlgPolicy,std::__ndk1::__less<void,void>&,std::__ndk1::__wrap_iter<float*>>
                  ((__wrap_iter)local_158,(__wrap_iter)pfVar23,(__wrap_iter)pfVar34,a_Stack_a9);
      }
      fVar37 = *pfVar23 / 3.016;
      uVar35 = DAT_00119af0;
      uVar36 = DAT_00119b00;
      uVar38 = DAT_00119b28;
      goto joined_r0x0013883c;
    }
  }
  fVar37 = 0.0;
  uVar35 = DAT_00119af0;
  uVar36 = DAT_00119b00;
  uVar38 = DAT_00119b28;
joined_r0x0013883c:
  DAT_00119af0 = uVar35;
  DAT_00119b00 = uVar36;
  DAT_00119b28 = uVar38;
  if ((local_12c != 0) && (local_130 != 0)) {
    fVar41 = fVar37 * 2.5;
    if (fVar37 * 2.5 <= 2.0) {
      fVar41 = 2.0;
    }
    uVar39 = NEON_fmov(0x3f800000,4);
    uVar22 = 0;
    do {
      while (local_130 == 0) {
        uVar22 = uVar22 + 1;
        if (local_12c <= uVar22) goto LAB_00138fe0;
      }
      iVar32 = 0;
      uVar29 = uVar22 + 1;
      uVar19 = 0;
      do {
        uVar10 = local_100 - 1;
        uVar11 = uStack_fc - 1;
        uVar12 = local_d0 - 1;
        fVar42 = (float)NEON_ucvtf(local_12c);
        fVar37 = (((float)(ulong)uVar19 + 0.5) * (float)(ulong)local_100) / (float)(ulong)local_130
                 + -0.5;
        if ((float)(ulong)uVar10 <= fVar37) {
          fVar37 = (float)(ulong)uVar10;
        }
        fVar42 = (((float)(ulong)uVar22 + 0.5) * (float)(ulong)uStack_fc) / fVar42 + -0.5;
        if (fVar37 <= 0.0) {
          fVar37 = 0.0;
        }
        uVar14 = (uint)fVar37;
        if ((float)(ulong)uVar11 <= fVar42) {
          fVar42 = (float)(ulong)uVar11;
        }
        uVar3 = uVar19 + 1;
        if (fVar42 <= 0.0) {
          fVar42 = 0.0;
        }
        if ((int)(uVar14 + 1) <= (int)uVar10) {
          uVar10 = uVar14 + 1;
        }
        uVar18 = -(ulong)(uVar10 >> 0x1f) & 0xfffffffc00000000 | (ulong)uVar10 << 2;
        fVar37 = fVar37 - (float)(int)fVar37;
        iVar17 = (int)fVar42;
        uVar10 = local_cc - 1;
        if (iVar17 + 1 <= (int)uVar11) {
          uVar11 = iVar17 + 1;
        }
        uVar8 = uVar12;
        if ((int)uVar19 <= (int)local_d0) {
          uVar8 = uVar19 - 1;
        }
        uVar9 = uVar19;
        if ((int)local_d0 <= (int)uVar19) {
          uVar9 = uVar12;
        }
        if ((int)uVar3 < (int)local_d0) {
          uVar12 = uVar19 + 1;
        }
        uVar19 = uVar10;
        if ((int)uVar22 <= (int)local_cc) {
          uVar19 = uVar22 - 1;
        }
        uVar24 = (ulong)((uVar12 & ((int)uVar12 >> 0x1f ^ 0xffffffffU)) << 2);
        pbVar1 = (byte *)(local_b8 + iVar32 + (ulong)(local_c8 * uVar22));
        uVar30 = (ulong)((uVar8 & ((int)uVar8 >> 0x1f ^ 0xffffffffU)) << 2);
        uVar28 = (ulong)((uVar9 & ((int)uVar9 >> 0x1f ^ 0xffffffffU)) << 2);
        lVar33 = local_b8 + (ulong)((uVar19 & ((int)uVar19 >> 0x1f ^ 0xffffffffU)) * local_c8);
        uVar19 = uVar22;
        if ((int)local_cc <= (int)uVar22) {
          uVar19 = uVar10;
        }
        pbVar2 = (byte *)(lVar33 + uVar24);
        fVar43 = (float)NEON_ucvtf((uint)*pbVar1);
        fVar44 = (float)NEON_ucvtf((uint)pbVar1[1]);
        fVar45 = (float)NEON_ucvtf((uint)pbVar1[2]);
        uVar12 = uVar29;
        if ((int)local_cc <= (int)uVar29) {
          uVar12 = uVar10;
        }
        fVar47 = (float)NEON_ucvtf((uint)*pbVar2);
        fVar48 = (float)NEON_ucvtf((uint)pbVar2[1]);
        fVar57 = (float)NEON_ucvtf((uint)pbVar2[2]);
        lVar27 = local_b8 + (ulong)((uVar19 & ((int)uVar19 >> 0x1f ^ 0xffffffffU)) * local_c8);
        pbVar1 = (byte *)(lVar27 + uVar30);
        fVar46 = (float)NEON_ucvtf((uint)*pbVar1);
        fVar56 = (float)NEON_ucvtf((uint)pbVar1[1]);
        fVar55 = fVar43 * 0.299 + fVar44 * 0.587 + fVar45 * 0.114;
        pbVar2 = (byte *)(lVar27 + uVar28);
        pbVar4 = (byte *)(lVar27 + uVar24);
        lVar27 = local_b8 + (ulong)((uVar12 & ((int)uVar12 >> 0x1f ^ 0xffffffffU)) * local_c8);
        fVar43 = (float)NEON_ucvtf((uint)pbVar1[2]);
        fVar75 = fVar47 * 0.299 + fVar48 * 0.587 + fVar57 * 0.114;
        fVar47 = (float)NEON_ucvtf((uint)pbVar4[1]);
        pbVar1 = (byte *)(lVar27 + uVar30);
        fVar45 = (float)NEON_ucvtf((uint)*pbVar2);
        fVar48 = (float)NEON_ucvtf((uint)pbVar2[1]);
        fVar57 = (float)NEON_ucvtf((uint)*pbVar4);
        fVar44 = (fVar75 - fVar55) / fVar41;
        fVar77 = fVar46 * 0.299 + fVar56 * 0.587 + fVar43 * 0.114;
        pbVar5 = (byte *)(lVar33 + uVar30);
        puVar6 = (undefined *)(lVar33 + uVar28);
        fVar43 = (float)NEON_ucvtf((uint)pbVar2[2]);
        fVar46 = (fVar77 - fVar55) / fVar41;
        fVar56 = fVar45 * 0.299 + fVar48 * 0.587 + fVar43 * 0.114;
        fVar43 = (float)NEON_ucvtf((uint)pbVar4[2]);
        uVar62 = NEON_ucvtf((ulong)CONCAT14(*puVar6,(uint)pbVar5[1]),4);
        uVar49 = NEON_ucvtf((ulong)CONCAT14(puVar6[1],(uint)*pbVar5),4);
        fVar48 = (fVar56 - fVar55) / fVar41;
        fVar57 = fVar57 * 0.299 + fVar47 * 0.587 + fVar43 * 0.114;
        uVar40 = NEON_ucvtf((ulong)CONCAT14(puVar6[2],(uint)pbVar5[2]),4);
        fVar43 = (fVar57 - fVar55) / fVar41;
        fVar60 = (float)uVar62 * (float)uVar36 + (float)uVar49 * (float)uVar38 +
                 (float)uVar40 * 0.114;
        fVar63 = (float)((ulong)uVar62 >> 0x20) * (float)((ulong)uVar36 >> 0x20) +
                 (float)((ulong)uVar49 >> 0x20) * (float)((ulong)uVar38 >> 0x20) +
                 (float)((ulong)uVar40 >> 0x20) * 0.114;
        fVar59 = (float)NEON_ucvtf((uint)pbVar1[1]);
        fVar45 = (fVar60 - fVar55) / fVar41;
        fVar47 = (fVar63 - fVar55) / fVar41;
        fVar53 = 1.0 / (fVar44 * fVar44 * fVar44 * fVar44 + 1.0);
        fVar64 = 2.0 / (fVar46 * fVar46 * fVar46 * fVar46 + 1.0);
        fVar50 = 4.0 / (fVar48 * fVar48 * fVar48 * fVar48 + 1.0);
        fVar44 = (float)NEON_ucvtf((uint)*pbVar1);
        fVar52 = 2.0 / (fVar43 * fVar43 * fVar43 * fVar43 + 1.0);
        pbVar2 = (byte *)(lVar27 + uVar28);
        pbVar4 = (byte *)(lVar27 + uVar24);
        fVar43 = (float)NEON_ucvtf((uint)pbVar1[2]);
        fVar66 = (float)NEON_ucvtf((uint)*pbVar2);
        fVar58 = (float)NEON_ucvtf((uint)pbVar2[1]);
        fVar68 = (float)NEON_ucvtf((uint)pbVar4[1]);
        fVar46 = (float)uVar35 / (fVar45 * fVar45 * fVar45 * fVar45 + (float)uVar39);
        fVar48 = (float)((ulong)uVar35 >> 0x20) /
                 (fVar47 * fVar47 * fVar47 * fVar47 + (float)((ulong)uVar39 >> 0x20));
        fVar54 = fVar44 * 0.299 + fVar59 * 0.587 + fVar43 * 0.114;
        uVar24 = -(ulong)(uVar14 >> 0x1f) & 0xfffffffc00000000 | (ulong)uVar14 << 2;
        fVar43 = (float)NEON_ucvtf((uint)pbVar2[2]);
        pbVar1 = (byte *)(local_118 + iVar32 + (ulong)(local_128 * uVar22));
        fVar45 = (fVar54 - fVar55) / fVar41;
        fVar44 = (float)NEON_ucvtf((uint)*pbVar4);
        fVar67 = fVar66 * 0.299 + fVar58 * 0.587 + fVar43 * 0.114;
        fVar43 = (float)NEON_ucvtf((uint)pbVar4[2]);
        lVar33 = local_e8 + (ulong)(uint)(local_f8 * iVar17);
        pbVar2 = (byte *)(lVar33 + uVar24);
        lVar27 = local_e8 + (ulong)(uVar11 * local_f8);
        pbVar4 = (byte *)(lVar33 + uVar18);
        pbVar5 = (byte *)(lVar27 + uVar24);
        pbVar7 = (byte *)(lVar27 + uVar18);
        fVar70 = (float)NEON_ucvtf((uint)pbVar2[1]);
        fVar47 = (fVar67 - fVar55) / fVar41;
        fVar44 = fVar44 * 0.299 + fVar68 * 0.587 + fVar43 * 0.114;
        fVar73 = (float)NEON_ucvtf((uint)*pbVar2);
        fVar66 = (float)NEON_ucvtf((uint)*pbVar7);
        fVar43 = (fVar44 - fVar55) / fVar41;
        fVar59 = (float)NEON_ucvtf((uint)pbVar1[1]);
        fVar51 = (float)NEON_ucvtf((uint)pbVar5[2]);
        fVar45 = 1.0 / (fVar45 * fVar45 * fVar45 * fVar45 + 1.0);
        fVar55 = 2.0 / (fVar47 * fVar47 * fVar47 * fVar47 + 1.0);
        fVar47 = (float)NEON_ucvtf((uint)*pbVar1);
        fVar61 = (float)NEON_ucvtf((uint)pbVar1[2]);
        fVar76 = 1.0 / (fVar43 * fVar43 * fVar43 * fVar43 + 1.0);
        fVar69 = (float)NEON_ucvtf((uint)*pbVar4);
        fVar71 = (float)NEON_ucvtf((uint)pbVar2[2]);
        fVar72 = (float)NEON_ucvtf((uint)pbVar5[1]);
        fVar43 = fVar47 * 0.299 + fVar59 * 0.587 + fVar61 * 0.114;
        fVar65 = (float)NEON_ucvtf((uint)pbVar4[1]);
        fVar74 = (float)NEON_ucvtf((uint)*pbVar5);
        fVar78 = (float)NEON_ucvtf((uint)pbVar7[1]);
        fVar68 = (float)NEON_ucvtf((uint)pbVar4[2]);
        fVar79 = (float)NEON_ucvtf((uint)pbVar7[2]);
        fVar58 = fVar43 / 24.0;
        fVar43 = (255.0 - fVar43) / 24.0;
        if (fVar58 <= fVar43) {
          fVar43 = fVar58;
        }
        fVar37 = (float)NEON_fminnm((fVar60 * fVar46 + 0.0 + fVar63 * fVar48 + fVar75 * fVar53 +
                                     fVar77 * fVar64 + fVar56 * fVar50 + fVar57 * fVar52 +
                                     fVar54 * fVar45 + fVar67 * fVar55 + fVar44 * fVar76) /
                                    (fVar46 + 0.0 + fVar48 + fVar53 + fVar64 + fVar50 + fVar52 +
                                     fVar45 + fVar55 + fVar76) -
                                    ((1.0 - (fVar42 - (float)(int)fVar42)) *
                                     ((fVar73 * 0.299 + fVar70 * 0.587 + fVar71 * 0.114) *
                                      (1.0 - fVar37) +
                                     fVar37 * (fVar69 * 0.299 + fVar65 * 0.587 + fVar68 * 0.114)) +
                                    (fVar42 - (float)(int)fVar42) *
                                    ((1.0 - fVar37) *
                                     (fVar74 * 0.299 + fVar72 * 0.587 + fVar51 * 0.114) +
                                    fVar37 * (fVar66 * 0.299 + fVar78 * 0.587 + fVar79 * 0.114))),
                                    0x41c00000);
        fVar42 = (float)NEON_fminnm(fVar43,0x3f800000);
        if (fVar37 <= -24.0) {
          fVar37 = -24.0;
        }
        if (fVar42 <= 0.0) {
          fVar42 = 0.0;
        }
        fVar37 = fVar37 * fVar42;
        fVar42 = ABS(fVar37 + fVar47);
        if ((INFINITY <= fVar42) && (fVar42 <= INFINITY)) {
LAB_00138fb4:
          prVar16 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00138fc0 to 00138fcb has its CatchHandler @ 0013910c */
          std::runtime_error::runtime_error(prVar16,"Non-finite image sample");
                    /* try { // try from 00139050 to 00139067 has its CatchHandler @ 00139100 */
                    /* WARNING: Subroutine does not return */
          __cxa_throw(prVar16,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
        }
        fVar42 = (float)NEON_fminnm((int)(fVar37 + fVar47),0x437f0000);
        if (fVar42 <= 0.0) {
          fVar42 = 0.0;
        }
        *pbVar1 = (byte)(int)fVar42;
        if (ABS(fVar37 + fVar59) == INFINITY) goto LAB_00138fb4;
        fVar42 = (float)NEON_fminnm((int)(fVar37 + fVar59),0x437f0000);
        if (fVar42 <= 0.0) {
          fVar42 = 0.0;
        }
        pbVar1[1] = (byte)(int)fVar42;
        if (ABS(fVar37 + fVar61) == INFINITY) goto LAB_00138fb4;
        iVar32 = iVar32 + 4;
        fVar37 = (float)NEON_fminnm((int)(fVar37 + fVar61),0x437f0000);
        if (fVar37 <= 0.0) {
          fVar37 = 0.0;
        }
        pbVar1[2] = (byte)(int)fVar37;
        uVar19 = uVar3;
      } while (uVar3 < local_130);
      uVar22 = uVar29;
    } while (uVar29 < local_12c);
  }
LAB_00138fe0:
  if (local_158 != (float *)0x0) {
    operator_delete(local_158);
  }
  if (local_118 != 0) {
                    /* try { // try from 00138ffc to 00138fff has its CatchHandler @ 001390b0 */
    AndroidBitmap_unlockPixels(local_140,uStack_138);
  }
  if (local_e8 != 0) {
                    /* try { // try from 0013900c to 0013900f has its CatchHandler @ 001390ac */
    AndroidBitmap_unlockPixels(local_110,uStack_108);
  }
  if (local_b8 != 0) {
                    /* try { // try from 0013901c to 0013901f has its CatchHandler @ 001390a8 */
    AndroidBitmap_unlockPixels(local_e0,uStack_d8);
  }
  return;
}



/* 00139280 Java_com_codex_fullm9_NativeM9_restoreTexture */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Java_com_codex_fullm9_NativeM9_restoreTexture
               (long *param_1,undefined8 param_2,_jobject *param_3,_jobject *param_4)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  byte bVar8;
  byte bVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  long lVar14;
  long lVar15;
  undefined auVar16 [16];
  undefined auVar17 [16];
  undefined auVar18 [16];
  undefined auVar19 [16];
  undefined auVar20 [16];
  undefined auVar21 [16];
  undefined auVar22 [16];
  undefined auVar23 [16];
  undefined auVar24 [16];
  undefined auVar25 [16];
  undefined8 uVar26;
  undefined auVar27 [16];
  undefined auVar28 [16];
  undefined auVar29 [16];
  undefined auVar30 [16];
  undefined auVar31 [16];
  undefined auVar32 [16];
  undefined auVar33 [16];
  undefined auVar34 [16];
  undefined auVar35 [16];
  undefined auVar36 [16];
  undefined auVar37 [16];
  undefined auVar38 [16];
  undefined auVar39 [16];
  undefined auVar40 [16];
  undefined auVar41 [16];
  undefined auVar42 [16];
  undefined auVar43 [16];
  undefined auVar44 [16];
  undefined auVar45 [16];
  undefined auVar46 [16];
  undefined auVar47 [16];
  undefined auVar48 [16];
  undefined auVar49 [16];
  undefined auVar50 [16];
  undefined auVar51 [16];
  undefined auVar52 [16];
  undefined auVar53 [16];
  undefined auVar54 [16];
  undefined auVar55 [16];
  undefined auVar56 [16];
  undefined auVar57 [16];
  undefined auVar58 [16];
  undefined auVar59 [16];
  undefined auVar60 [16];
  undefined auVar61 [16];
  undefined auVar62 [16];
  undefined auVar63 [16];
  undefined auVar64 [16];
  undefined auVar65 [16];
  undefined auVar66 [16];
  undefined auVar67 [16];
  undefined auVar68 [16];
  undefined auVar69 [16];
  undefined auVar70 [16];
  undefined auVar71 [16];
  undefined auVar72 [16];
  undefined auVar73 [16];
  undefined auVar74 [16];
  undefined auVar75 [16];
  undefined auVar76 [16];
  undefined auVar77 [16];
  undefined auVar78 [16];
  undefined auVar79 [16];
  undefined auVar80 [16];
  undefined auVar81 [16];
  undefined auVar82 [16];
  undefined auVar83 [16];
  undefined auVar84 [16];
  undefined auVar85 [16];
  undefined auVar86 [16];
  undefined auVar87 [16];
  undefined auVar88 [16];
  undefined auVar89 [16];
  undefined auVar90 [16];
  undefined auVar91 [16];
  undefined auVar92 [16];
  undefined auVar93 [16];
  undefined auVar94 [16];
  undefined auVar95 [16];
  undefined auVar96 [16];
  undefined4 uVar97;
  undefined4 uVar98;
  uint uVar99;
  uint uVar100;
  undefined *puVar101;
  char cVar102;
  void *pvVar103;
  undefined8 *puVar104;
  undefined8 *puVar105;
  runtime_error *prVar106;
  long *plVar107;
  char *__s;
  size_t __n;
  undefined8 uVar108;
  long lVar109;
  uint uVar110;
  ulong uVar111;
  uint uVar112;
  long lVar113;
  uint uVar114;
  uint uVar115;
  long lVar116;
  float *pfVar117;
  float *pfVar118;
  uint uVar119;
  ulong uVar120;
  byte *pbVar121;
  ulong uVar122;
  ulong uVar123;
  long lVar124;
  long lVar125;
  ulong uVar126;
  long lVar127;
  undefined8 *puVar128;
  long lVar129;
  ulong uVar130;
  ulong uVar131;
  ulong uVar132;
  long lVar133;
  long lVar134;
  long lVar135;
  float *pfVar136;
  long lVar137;
  float *pfVar138;
  ulong uVar139;
  long lVar140;
  int iVar141;
  void *pvVar142;
  long lVar143;
  long lVar144;
  ulong uVar145;
  int iVar146;
  ulong uVar147;
  float fVar148;
  undefined4 uVar149;
  undefined4 uVar150;
  float fVar151;
  float fVar152;
  undefined4 uVar153;
  undefined4 uVar154;
  float fVar155;
  float fVar156;
  float fVar157;
  float fVar158;
  float fVar159;
  float fVar160;
  float fVar161;
  float fVar162;
  byte bVar163;
  float fVar164;
  float fVar165;
  float fVar166;
  undefined auVar167 [16];
  undefined auVar168 [16];
  undefined auVar169 [16];
  undefined auVar170 [16];
  undefined auVar171 [16];
  undefined auVar172 [16];
  float fVar173;
  undefined auVar174 [16];
  undefined auVar175 [16];
  undefined auVar176 [16];
  undefined auVar177 [16];
  undefined auVar178 [16];
  undefined auVar179 [16];
  undefined auVar180 [16];
  undefined auVar181 [16];
  undefined in_q17 [16];
  undefined auVar182 [16];
  undefined auVar183 [16];
  undefined auVar184 [16];
  undefined auVar185 [16];
  undefined auVar186 [16];
  undefined auVar187 [16];
  undefined auVar188 [16];
  undefined auVar189 [16];
  undefined auVar190 [16];
  undefined in_q18 [16];
  undefined auVar191 [16];
  undefined auVar192 [16];
  undefined auVar193 [16];
  undefined auVar194 [16];
  undefined auVar195 [16];
  undefined auVar196 [16];
  undefined auVar197 [16];
  undefined auVar198 [16];
  undefined auVar199 [16];
  undefined auVar200 [16];
  float fVar201;
  undefined auVar202 [16];
  undefined auVar203 [16];
  float fVar204;
  undefined8 uVar205;
  undefined auVar206 [16];
  undefined auVar207 [16];
  undefined auVar208 [16];
  float fVar209;
  float fVar210;
  undefined auVar211 [16];
  undefined auVar212 [16];
  float fVar213;
  undefined auVar214 [16];
  undefined auVar215 [16];
  float fVar216;
  undefined in_q27 [16];
  undefined auVar217 [16];
  undefined auVar218 [16];
  undefined auVar219 [16];
  undefined auVar220 [16];
  undefined auVar221 [16];
  float fVar222;
  undefined in_q28 [16];
  undefined auVar223 [16];
  undefined auVar224 [16];
  undefined auVar225 [16];
  float fVar226;
  float fVar227;
  undefined in_q29 [16];
  undefined auVar228 [16];
  undefined auVar229 [16];
  undefined auVar230 [16];
  undefined auVar231 [16];
  undefined auVar232 [16];
  undefined auVar233 [16];
  undefined auVar234 [16];
  undefined auVar235 [16];
  undefined auVar236 [16];
  undefined auVar237 [12];
  undefined8 *local_138;
  undefined8 *local_130;
  undefined *local_128;
  float *local_120;
  float *local_118;
  float *local_110;
  undefined8 local_108;
  undefined8 uStack_100;
  uint local_f8;
  uint local_f4;
  uint local_f0;
  undefined *local_e0;
  undefined8 local_d8;
  size_t local_d0;
  undefined8 local_c8;
  uint local_c0;
  undefined *local_b0;
  
                    /* try { // try from 001392c4 to 001392cf has its CatchHandler @ 0013b338 */
  cVar102 = (**(code **)(*param_1 + 0xc0))(param_1,param_3,param_4);
  if (cVar102 != '\0') {
    return;
  }
                    /* try { // try from 001392d8 to 001392e7 has its CatchHandler @ 0013b334 */
  Pixels::Pixels((Pixels *)&local_d8,(_JNIEnv *)param_1,param_3);
                    /* try { // try from 001392e8 to 001392f7 has its CatchHandler @ 0013b328 */
  Pixels::Pixels((Pixels *)&local_108,(_JNIEnv *)param_1,param_4);
  pvVar142 = local_c8;
  uVar99 = (uint)local_c8;
  lVar116 = (long)(int)(uint)local_c8;
  if ((local_f8 != (uint)local_c8) || (uVar100 = local_c8._4_4_, local_f4 != local_c8._4_4_)) {
    prVar106 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013b2a0 to 0013b2ab has its CatchHandler @ 0013b2e4 */
    std::runtime_error::runtime_error(prVar106,"Texture dimensions");
                    /* try { // try from 0013b2ac to 0013b2c3 has its CatchHandler @ 0013b2d8 */
                    /* WARNING: Subroutine does not return */
    __cxa_throw(prVar106,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
  }
  if (((int)(uint)local_c8 < 5) || ((int)local_c8._4_4_ < 5)) goto LAB_0013a80c;
  uVar126 = (ulong)local_c8 & 0xffffffff;
  iVar10 = (uint)local_c8 - 1;
  iVar11 = local_c8._4_4_ - 2;
  auVar168 = ZEXT816(0x40800000);
  uVar12 = local_c8._4_4_ - 1;
  auVar170 = ZEXT416(0x3e59b3d0);
  auVar212 = ZEXT416(0x3d93dd98);
  auVar207 = ZEXT416(0x3f371759);
  iVar141 = 1;
  iVar13 = (uint)local_c8 - 2;
  local_120 = (float *)0x0;
  local_118 = (float *)0x0;
  local_110 = (float *)0x0;
  uVar114 = (uint)SQRT(((double)(uint)local_c8 * (double)local_c8._4_4_) / 16000.0);
  if ((int)uVar114 < 2) {
    uVar114 = 1;
  }
  do {
    iVar146 = 1;
    do {
      while( true ) {
        pfVar138 = local_118;
        pfVar118 = local_120;
        uVar110 = iVar141 * -0x61c8864f + iVar146 * -0x7a143589;
        uVar110 = (uVar110 ^ uVar110 >> 0xd) * -0x3d4d51c3;
        uVar119 = 0;
        if (uVar114 != 0) {
          uVar119 = uVar110 / uVar114;
        }
        uVar112 = 0;
        if (uVar114 != 0) {
          uVar112 = (uVar110 >> 0x10) / uVar114;
        }
        iVar2 = (uVar110 - uVar119 * uVar114) + iVar146;
        if (iVar13 <= iVar2) {
          iVar2 = iVar13;
        }
        iVar3 = ((uVar110 >> 0x10) - uVar112 * uVar114) + iVar141;
        iVar2 = iVar2 * 4;
        if (iVar11 <= iVar3) {
          iVar3 = iVar11;
        }
        uVar110 = local_c0 * iVar3;
        pbVar4 = local_b0 + (long)iVar2 + (ulong)uVar110;
        pbVar121 = local_b0 + (long)(iVar2 + -4) + (ulong)uVar110;
        pbVar1 = local_b0 + (long)(iVar2 + 4) + (ulong)uVar110;
        fVar148 = (float)NEON_ucvtf((uint)*pbVar4);
        fVar151 = (float)NEON_ucvtf((uint)pbVar4[1]);
        fVar155 = (float)NEON_ucvtf((uint)*pbVar121);
        fVar156 = (float)NEON_ucvtf((uint)pbVar121[1]);
        fVar158 = (float)NEON_ucvtf((uint)pbVar4[2]);
        fVar161 = (float)NEON_ucvtf((uint)pbVar121[2]);
        fVar164 = (float)NEON_ucvtf((uint)*pbVar1);
        fVar165 = (float)NEON_ucvtf((uint)pbVar1[1]);
        pbVar121 = local_b0 + (ulong)((iVar3 + -1) * local_c0) + (long)iVar2;
        pbVar4 = local_b0 + (ulong)(local_c0 + uVar110) + (long)iVar2;
        fVar201 = auVar170._0_4_;
        fVar204 = auVar207._0_4_;
        fVar227 = auVar212._0_4_;
        fVar173 = (float)NEON_ucvtf((uint)*pbVar121);
        fVar152 = (float)NEON_ucvtf((uint)pbVar121[1]);
        fVar157 = (float)NEON_ucvtf((uint)pbVar1[2]);
        fVar166 = (float)NEON_ucvtf((uint)*pbVar4);
        fVar159 = (float)NEON_ucvtf((uint)pbVar121[2]);
        fVar162 = (float)NEON_ucvtf((uint)pbVar4[1]);
        auVar221 = ZEXT116(pbVar4[2]);
        fVar160 = (float)NEON_ucvtf((uint)pbVar4[2]);
        fVar148 = ABS(((((fVar148 * fVar201 + fVar151 * fVar204 + fVar158 * fVar227) *
                         auVar168._0_4_ -
                        (fVar155 * fVar201 + fVar156 * fVar204 + fVar161 * fVar227)) -
                       (fVar164 * fVar201 + fVar165 * fVar204 + fVar157 * fVar227)) -
                      (fVar173 * fVar201 + fVar152 * fVar204 + fVar159 * fVar227)) -
                      (fVar166 * fVar201 + fVar162 * fVar204 + fVar160 * fVar227));
        if (local_118 < local_110) break;
        lVar144 = (long)local_118 - (long)local_120;
        lVar135 = lVar144 >> 2;
        uVar139 = lVar135 + 1;
        if (uVar139 >> 0x3e != 0) {
                    /* try { // try from 0013b268 to 0013b27b has its CatchHandler @ 0013b39c */
          std::__ndk1::vector<float,std::__ndk1::allocator<float>>::
          __throw_length_error_abi_ne180000_();
LAB_0013b274:
                    /* WARNING: Subroutine does not return */
          std::__throw_bad_array_new_length_abi_ne180000_();
        }
        uVar120 = (long)local_110 - (long)local_120 >> 1;
        if (uVar120 <= uVar139) {
          uVar120 = uVar139;
        }
        if (0x7ffffffffffffffb < (ulong)((long)local_110 - (long)local_120)) {
          uVar120 = 0x3fffffffffffffff;
        }
        if (uVar120 == 0) {
          pvVar103 = (void *)0x0;
          pfVar117 = (float *)(lVar135 * 4);
          lVar135 = (long)local_118 - (long)local_120;
          pfVar136 = pfVar117 + 1;
          *pfVar117 = fVar148;
          if (lVar135 != 0) goto LAB_001395e0;
LAB_001396b8:
          local_110 = (float *)((long)pvVar103 + uVar120 * 4);
          local_120 = pfVar117;
        }
        else {
          if (uVar120 >> 0x3e != 0) goto LAB_0013b274;
                    /* try { // try from 001395c8 to 001395cb has its CatchHandler @ 0013b38c */
          pvVar103 = operator_new(uVar120 << 2);
          pfVar117 = (float *)((long)pvVar103 + lVar135 * 4);
          lVar135 = (long)pfVar138 - (long)pfVar118;
          pfVar136 = pfVar117 + 1;
          *pfVar117 = fVar148;
          if (lVar135 == 0) goto LAB_001396b8;
LAB_001395e0:
          local_120 = pfVar117;
          if ((lVar135 - 4U < 0x1c) ||
             ((ulong)((long)pfVar138 + (-lVar144 - (long)pvVar103)) < 0x20)) {
LAB_0013964c:
            do {
              pfVar138 = pfVar138 + -1;
              local_120 = local_120 + -1;
              *local_120 = *pfVar138;
            } while (pfVar138 != pfVar118);
          }
          else {
            puVar105 = (undefined8 *)(pfVar138 + -4);
            uVar139 = (lVar135 - 4U >> 2) + 1;
            uVar123 = uVar139 & 0x7ffffffffffffff8;
            pfVar138 = pfVar138 + -uVar123;
            local_120 = pfVar117 + -uVar123;
            puVar104 = (undefined8 *)(pfVar117 + -4);
            uVar130 = uVar123;
            do {
              puVar128 = puVar105 + -1;
              uVar205 = puVar105[-2];
              uVar26 = puVar105[1];
              uVar108 = *puVar105;
              uVar130 = uVar130 - 8;
              puVar105 = puVar105 + -4;
              puVar104[-1] = *puVar128;
              puVar104[-2] = uVar205;
              puVar104[1] = uVar26;
              *puVar104 = uVar108;
              puVar104 = puVar104 + -4;
            } while (uVar130 != 0);
            if (uVar139 != uVar123) goto LAB_0013964c;
          }
          local_110 = (float *)((long)pvVar103 + uVar120 * 4);
        }
        if (pfVar118 != (float *)0x0) {
          local_118 = pfVar136;
          operator_delete(pfVar118);
        }
        iVar146 = iVar146 + uVar114;
        local_118 = pfVar136;
        if (iVar10 <= iVar146) goto LAB_001393cc;
      }
      pfVar136 = local_118 + 1;
      *local_118 = fVar148;
      iVar146 = iVar146 + uVar114;
      local_118 = pfVar136;
    } while (iVar146 < iVar10);
LAB_001393cc:
    iVar141 = iVar141 + uVar114;
    local_118 = pfVar136;
  } while (iVar141 < (int)uVar12);
  auVar168._8_8_ = 0;
  auVar168._0_8_ = (long)pfVar136 - (long)local_120 >> 2;
  pfVar118 = (float *)((long)local_120 +
                      (SUB168(auVar168 * ZEXT816(0xcccccccccccccccd),8) & 0xfffffffffffffffc));
  if (pfVar118 != pfVar136) {
                    /* try { // try from 001396f8 to 00139707 has its CatchHandler @ 0013b2d4 */
    std::__ndk1::
    __nth_element_abi_ne180000_<std::__ndk1::_ClassicAlgPolicy,std::__ndk1::__less<void,void>&,std::__ndk1::__wrap_iter<float*>>
              ((__wrap_iter)local_120,(__wrap_iter)pfVar118,(__wrap_iter)pfVar136,
               (__less *)&local_138);
  }
  fVar148 = *pfVar118;
  local_138 = (undefined8 *)0x0;
  local_130 = (undefined8 *)0x0;
  local_128 = (undefined *)0x0;
  if ((ulong)(lVar116 * 5) >> 0x3e == 0) {
    uVar139 = lVar116 * 0x14;
                    /* try { // try from 00139728 to 0013972f has its CatchHandler @ 0013b314 */
    puVar104 = (undefined8 *)operator_new(uVar139);
    local_128 = (undefined *)((long)puVar104 + lVar116 * 0x14);
    local_138 = puVar104;
    memset(puVar104,0,uVar139);
    local_130 = (undefined8 *)((long)puVar104 + uVar139);
    if ((ulong)(lVar116 * 3) >> 0x3e == 0) {
                    /* try { // try from 00139770 to 00139777 has its CatchHandler @ 0013b300 */
      puVar105 = (undefined8 *)operator_new(lVar116 * 0xc);
      fVar151 = 1.133;
      memset(puVar105,0,lVar116 * 0xc);
      uVar98 = _UNK_00119bec;
      uVar97 = _UNK_00119bac;
      uVar139 = (ulong)local_c0;
      uVar120 = uVar126 * 4;
      if ((uVar99 < 9) ||
         ((puVar104 < local_b0 + (uVar120 - 1) &&
          (local_b0 < (undefined *)((long)puVar104 + uVar120))))) {
        lVar135 = 0;
      }
      else {
        if (uVar99 < 0x11) {
          lVar135 = 0;
        }
        else {
          auVar212._8_4_ = _UNK_00119ba8;
          auVar212._0_8_ = _DAT_00119ba0;
          auVar207._8_4_ = _UNK_00119ba8;
          auVar207._0_8_ = _DAT_00119ba0;
          auVar170._8_4_ = _UNK_00119ba8;
          auVar170._0_8_ = _DAT_00119ba0;
          uVar130 = 0x10;
          if (((ulong)pvVar142 & 0xf) != 0) {
            uVar130 = (ulong)pvVar142 & 0xf;
          }
          auVar172._8_4_ = _UNK_00119be8;
          auVar172._0_8_ = _DAT_00119be0;
          auVar232._8_4_ = _UNK_00119be8;
          auVar232._0_8_ = _DAT_00119be0;
          auVar236._8_4_ = _UNK_00119be8;
          auVar236._0_8_ = _DAT_00119be0;
          auVar211._8_8_ = _UNK_00119bd8;
          auVar211._0_8_ = _DAT_00119bd0;
          auVar206._8_8_ = _UNK_00119b48;
          auVar206._0_8_ = _DAT_00119b40;
          lVar135 = uVar126 - uVar130;
          uVar123 = uVar126;
          puVar128 = puVar104;
          puVar101 = local_b0;
          do {
            auVar219[0] = *puVar101;
            auVar234[0] = puVar101[1];
            auVar230[0] = puVar101[2];
            auVar219[1] = puVar101[4];
            auVar234[1] = puVar101[5];
            auVar230[1] = puVar101[6];
            auVar219[2] = puVar101[8];
            auVar234[2] = puVar101[9];
            auVar230[2] = puVar101[10];
            auVar219[3] = puVar101[0xc];
            auVar234[3] = puVar101[0xd];
            auVar230[3] = puVar101[0xe];
            auVar219[4] = puVar101[0x10];
            auVar234[4] = puVar101[0x11];
            auVar230[4] = puVar101[0x12];
            auVar219[5] = puVar101[0x14];
            auVar234[5] = puVar101[0x15];
            auVar230[5] = puVar101[0x16];
            auVar219[6] = puVar101[0x18];
            auVar234[6] = puVar101[0x19];
            auVar230[6] = puVar101[0x1a];
            auVar219[7] = puVar101[0x1c];
            auVar234[7] = puVar101[0x1d];
            auVar230[7] = puVar101[0x1e];
            auVar219[8] = puVar101[0x20];
            auVar234[8] = puVar101[0x21];
            auVar230[8] = puVar101[0x22];
            auVar219[9] = puVar101[0x24];
            auVar234[9] = puVar101[0x25];
            auVar230[9] = puVar101[0x26];
            auVar219[10] = puVar101[0x28];
            auVar234[10] = puVar101[0x29];
            auVar230[10] = puVar101[0x2a];
            auVar219[11] = puVar101[0x2c];
            auVar234[11] = puVar101[0x2d];
            auVar230[11] = puVar101[0x2e];
            auVar219[12] = puVar101[0x30];
            auVar234[12] = puVar101[0x31];
            auVar230[12] = puVar101[0x32];
            auVar219[13] = puVar101[0x34];
            auVar234[13] = puVar101[0x35];
            auVar230[13] = puVar101[0x36];
            auVar219[14] = puVar101[0x38];
            auVar234[14] = puVar101[0x39];
            auVar230[14] = puVar101[0x3a];
            auVar219[15] = puVar101[0x3c];
            auVar234[15] = puVar101[0x3d];
            auVar230[15] = puVar101[0x3e];
            puVar101 = puVar101 + 0x40;
            uVar123 = uVar123 - 0x10;
            auVar168 = a64_TBL(ZEXT816(0),auVar219,auVar206);
            auVar233 = a64_TBL(ZEXT816(0),auVar234,auVar206);
            auVar235 = a64_TBL(ZEXT816(0),auVar219,auVar211);
            auVar202 = a64_TBL(ZEXT816(0),auVar234,auVar211);
            auVar236._12_4_ = uVar98;
            auVar203 = a64_TBL(ZEXT816(0),auVar219,auVar236);
            auVar232._12_4_ = uVar98;
            auVar208 = a64_TBL(ZEXT816(0),auVar234,auVar232);
            auVar170._12_4_ = uVar97;
            auVar219 = a64_TBL(ZEXT816(0),auVar219,auVar170);
            auVar207._12_4_ = uVar97;
            auVar214 = a64_TBL(ZEXT816(0),auVar234,auVar207);
            in_q27 = a64_TBL(ZEXT816(0),auVar230,auVar206);
            in_q28 = a64_TBL(ZEXT816(0),auVar230,auVar211);
            auVar172._12_4_ = uVar98;
            in_q29 = a64_TBL(ZEXT816(0),auVar230,auVar172);
            auVar212._12_4_ = uVar97;
            auVar221 = a64_TBL(ZEXT816(0),auVar230,auVar212);
            auVar168 = NEON_ucvtf(auVar168,4);
            auVar200 = NEON_ucvtf(auVar233,4);
            auVar235 = NEON_ucvtf(auVar235,4);
            auVar202 = NEON_ucvtf(auVar202,4);
            auVar203 = NEON_ucvtf(auVar203,4);
            auVar208 = NEON_ucvtf(auVar208,4);
            auVar234 = NEON_ucvtf(auVar219,4);
            auVar230 = NEON_ucvtf(auVar214,4);
            auVar233 = NEON_ucvtf(in_q27,4);
            auVar214 = NEON_ucvtf(in_q28,4);
            auVar215 = NEON_ucvtf(in_q29,4);
            auVar219 = NEON_ucvtf(auVar221,4);
            in_q17._0_4_ = auVar234._0_4_ * 0.2126 + auVar230._0_4_ * 0.7152;
            in_q17._4_4_ = auVar234._4_4_ * 0.2126 + auVar230._4_4_ * 0.7152;
            in_q17._8_4_ = auVar234._8_4_ * 0.2126 + auVar230._8_4_ * 0.7152;
            in_q17._12_4_ = auVar234._12_4_ * 0.2126 + auVar230._12_4_ * 0.7152;
            in_q18._0_8_ = CONCAT44(auVar235._4_4_ * 0.2126 + auVar202._4_4_ * 0.7152 +
                                    auVar214._4_4_ * 0.0722,
                                    auVar235._0_4_ * 0.2126 + auVar202._0_4_ * 0.7152 +
                                    auVar214._0_4_ * 0.0722);
            in_q18._8_4_ = auVar235._8_4_ * 0.2126 + auVar202._8_4_ * 0.7152 +
                           auVar214._8_4_ * 0.0722;
            in_q18._12_4_ =
                 auVar235._12_4_ * 0.2126 + auVar202._12_4_ * 0.7152 + auVar214._12_4_ * 0.0722;
            auVar235._0_8_ =
                 CONCAT44(auVar203._4_4_ * 0.2126 + auVar208._4_4_ * 0.7152 +
                          auVar215._4_4_ * 0.0722,
                          auVar203._0_4_ * 0.2126 + auVar208._0_4_ * 0.7152 +
                          auVar215._0_4_ * 0.0722);
            auVar235._8_4_ =
                 auVar203._8_4_ * 0.2126 + auVar208._8_4_ * 0.7152 + auVar215._8_4_ * 0.0722;
            auVar235._12_4_ =
                 auVar203._12_4_ * 0.2126 + auVar208._12_4_ * 0.7152 + auVar215._12_4_ * 0.0722;
            auVar221._0_8_ =
                 CONCAT44(in_q17._4_4_ + auVar219._4_4_ * 0.0722,
                          in_q17._0_4_ + auVar219._0_4_ * 0.0722);
            auVar221._8_4_ = in_q17._8_4_ + auVar219._8_4_ * 0.0722;
            auVar221._12_4_ = in_q17._12_4_ + auVar219._12_4_ * 0.0722;
            puVar128[5] = in_q18._8_8_;
            puVar128[4] = in_q18._0_8_;
            *(float *)(puVar128 + 8) =
                 auVar168._8_4_ * 0.2126 + auVar200._8_4_ * 0.7152 + auVar233._8_4_ * 0.0722;
            *(float *)((long)puVar128 + 0x44) =
                 auVar168._12_4_ * 0.2126 + auVar200._12_4_ * 0.7152 + auVar233._12_4_ * 0.0722;
            *(float *)(puVar128 + 6) =
                 auVar168._0_4_ * 0.2126 + auVar200._0_4_ * 0.7152 + auVar233._0_4_ * 0.0722;
            *(float *)((long)puVar128 + 0x34) =
                 auVar168._4_4_ * 0.2126 + auVar200._4_4_ * 0.7152 + auVar233._4_4_ * 0.0722;
            puVar128[1] = auVar221._8_8_;
            *puVar128 = auVar221._0_8_;
            puVar128[3] = auVar235._8_8_;
            puVar128[2] = auVar235._0_8_;
            puVar128 = puVar128 + 8;
          } while (uVar130 != uVar123);
          if (uVar130 < 9) goto LAB_001397e4;
        }
        uVar98 = _UNK_00119bec;
        uVar97 = _UNK_00119bac;
        uVar130 = 8;
        if (((ulong)pvVar142 & 7) != 0) {
          uVar130 = (ulong)pvVar142 & 7;
        }
        lVar124 = lVar135 * 4;
        lVar144 = uVar130 + lVar135;
        auVar202._8_4_ = _UNK_00119ba8;
        auVar202._0_8_ = _DAT_00119ba0;
        auVar200._8_4_ = _UNK_00119ba8;
        auVar200._0_8_ = _DAT_00119ba0;
        auVar233._8_4_ = _UNK_00119ba8;
        auVar233._0_8_ = _DAT_00119ba0;
        auVar214._8_4_ = _UNK_00119be8;
        auVar214._0_8_ = _DAT_00119be0;
        auVar208._8_4_ = _UNK_00119be8;
        auVar208._0_8_ = _DAT_00119be0;
        auVar203._8_4_ = _UNK_00119be8;
        auVar203._0_8_ = _DAT_00119be0;
        lVar135 = uVar126 - uVar130;
        puVar101 = local_b0 + lVar124;
        lVar144 = lVar144 - uVar126;
        pfVar118 = (float *)((long)puVar104 + lVar124);
        do {
          auVar215[0] = *puVar101;
          auVar182[0] = puVar101[1];
          auVar191[0] = puVar101[2];
          auVar215[1] = puVar101[4];
          auVar182[1] = puVar101[5];
          auVar191[1] = puVar101[6];
          auVar215[2] = puVar101[8];
          auVar182[2] = puVar101[9];
          auVar191[2] = puVar101[10];
          auVar215[3] = puVar101[0xc];
          auVar182[3] = puVar101[0xd];
          auVar191[3] = puVar101[0xe];
          auVar215[4] = puVar101[0x10];
          auVar182[4] = puVar101[0x11];
          auVar191[4] = puVar101[0x12];
          auVar215[5] = puVar101[0x14];
          auVar182[5] = puVar101[0x15];
          auVar191[5] = puVar101[0x16];
          auVar215[6] = puVar101[0x18];
          auVar182[6] = puVar101[0x19];
          auVar191[6] = puVar101[0x1a];
          auVar215._8_8_ = auVar221._8_8_;
          auVar215[7] = puVar101[0x1c];
          auVar182._8_8_ = in_q17._8_8_;
          auVar182[7] = puVar101[0x1d];
          auVar191._8_8_ = in_q18._8_8_;
          auVar191[7] = puVar101[0x1e];
          puVar101 = puVar101 + 0x20;
          lVar144 = lVar144 + 8;
          auVar203._12_4_ = uVar98;
          auVar168 = a64_TBL(ZEXT816(0),auVar215,auVar203);
          auVar208._12_4_ = uVar98;
          auVar170 = a64_TBL(ZEXT816(0),auVar182,auVar208);
          auVar233._12_4_ = uVar97;
          auVar207 = a64_TBL(ZEXT816(0),auVar215,auVar233);
          auVar200._12_4_ = uVar97;
          auVar221 = a64_TBL(ZEXT816(0),auVar182,auVar200);
          auVar214._12_4_ = uVar98;
          auVar232 = a64_TBL(ZEXT816(0),auVar191,auVar214);
          auVar202._12_4_ = uVar97;
          auVar212 = a64_TBL(ZEXT816(0),auVar191,auVar202);
          auVar168 = NEON_ucvtf(auVar168,4);
          auVar170 = NEON_ucvtf(auVar170,4);
          auVar207 = NEON_ucvtf(auVar207,4);
          auVar236 = NEON_ucvtf(auVar221,4);
          auVar232 = NEON_ucvtf(auVar232,4);
          auVar221 = NEON_ucvtf(auVar212,4);
          in_q17._0_4_ = auVar236._0_4_ * 0.7152;
          in_q17._4_4_ = auVar236._4_4_ * 0.7152;
          in_q17._8_4_ = auVar236._8_4_ * 0.7152;
          in_q17._12_4_ = auVar236._12_4_ * 0.7152;
          in_q18._0_4_ = auVar232._0_4_ * 0.0722;
          in_q18._4_4_ = auVar232._4_4_ * 0.0722;
          in_q18._8_4_ = auVar232._8_4_ * 0.0722;
          in_q18._12_4_ = auVar232._12_4_ * 0.0722;
          pfVar118[4] = auVar207._8_4_ * 0.2126 + in_q17._8_4_ + auVar221._8_4_ * 0.0722;
          pfVar118[5] = auVar207._12_4_ * 0.2126 + in_q17._12_4_ + auVar221._12_4_ * 0.0722;
          *pfVar118 = auVar207._0_4_ * 0.2126 + in_q17._0_4_ + auVar221._0_4_ * 0.0722;
          pfVar118[1] = auVar207._4_4_ * 0.2126 + in_q17._4_4_ + auVar221._4_4_ * 0.0722;
          pfVar118[8] = auVar168._8_4_ * 0.2126 + auVar170._8_4_ * 0.7152 + in_q18._8_4_;
          pfVar118[9] = auVar168._12_4_ * 0.2126 + auVar170._12_4_ * 0.7152 + in_q18._12_4_;
          pfVar118[4] = auVar168._0_4_ * 0.2126 + auVar170._0_4_ * 0.7152 + in_q18._0_4_;
          pfVar118[5] = auVar168._4_4_ * 0.2126 + auVar170._4_4_ * 0.7152 + in_q18._4_4_;
          pfVar118 = pfVar118 + 8;
        } while (lVar144 != 0);
      }
LAB_001397e4:
      fVar148 = fVar148 / fVar151;
      lVar144 = uVar126 - lVar135;
      pbVar121 = local_b0 + lVar135 * 4 + 2;
      pfVar118 = (float *)((long)puVar104 + lVar135 * 4);
      do {
        pbVar1 = pbVar121 + -2;
        pbVar4 = pbVar121 + -1;
        lVar144 = lVar144 + -1;
        bVar163 = *pbVar121;
        pbVar121 = pbVar121 + 4;
        fVar151 = (float)NEON_ucvtf((uint)*pbVar1);
        fVar152 = (float)NEON_ucvtf((uint)*pbVar4);
        fVar155 = (float)NEON_ucvtf((uint)bVar163);
        *pfVar118 = fVar151 * 0.2126 + fVar152 * 0.7152 + fVar155 * 0.0722;
        uVar97 = _UNK_00119bac;
        pfVar118 = pfVar118 + 1;
      } while (lVar144 != 0);
      if (uVar99 < 9) {
LAB_00139890:
        lVar135 = 0;
      }
      else {
        puVar128 = (undefined8 *)((long)puVar104 + lVar116 * 4);
        puVar101 = local_b0 + uVar139;
        if ((puVar128 < local_b0 + uVar139 + uVar126 * 4 + -1) &&
           (puVar101 < (undefined *)((long)puVar104 + (lVar116 + uVar126) * 4))) goto LAB_00139890;
        if (uVar99 < 0x11) {
          lVar135 = 0;
LAB_0013abc0:
          uVar97 = _UNK_00119bac;
          uVar130 = 8;
          if (((ulong)pvVar142 & 7) != 0) {
            uVar130 = (ulong)pvVar142 & 7;
          }
          lVar124 = lVar135 * 4;
          auVar50._8_4_ = _UNK_00119ba8;
          auVar50._0_8_ = _DAT_00119ba0;
          auVar49._8_4_ = _UNK_00119ba8;
          auVar49._0_8_ = _DAT_00119ba0;
          auVar48._8_4_ = _UNK_00119ba8;
          auVar48._0_8_ = _DAT_00119ba0;
          lVar144 = uVar130 + lVar135;
          lVar135 = uVar126 - uVar130;
          auVar90._8_4_ = _UNK_00119be8;
          auVar90._0_8_ = _DAT_00119be0;
          auVar90._12_4_ = _UNK_00119bec;
          puVar101 = local_b0 + lVar124 + uVar139;
          lVar144 = lVar144 - uVar126;
          pfVar118 = (float *)((long)puVar104 + lVar124 + lVar116 * 4);
          do {
            auVar175[0] = *puVar101;
            auVar184[0] = puVar101[1];
            auVar193[0] = puVar101[2];
            auVar175[1] = puVar101[4];
            auVar184[1] = puVar101[5];
            auVar193[1] = puVar101[6];
            auVar175[2] = puVar101[8];
            auVar184[2] = puVar101[9];
            auVar193[2] = puVar101[10];
            auVar175[3] = puVar101[0xc];
            auVar184[3] = puVar101[0xd];
            auVar193[3] = puVar101[0xe];
            auVar175[4] = puVar101[0x10];
            auVar184[4] = puVar101[0x11];
            auVar193[4] = puVar101[0x12];
            auVar175[5] = puVar101[0x14];
            auVar184[5] = puVar101[0x15];
            auVar193[5] = puVar101[0x16];
            auVar175[6] = puVar101[0x18];
            auVar184[6] = puVar101[0x19];
            auVar193[6] = puVar101[0x1a];
            auVar175._8_8_ = auVar221._8_8_;
            auVar175[7] = puVar101[0x1c];
            auVar184._8_8_ = in_q17._8_8_;
            auVar184[7] = puVar101[0x1d];
            auVar193._8_8_ = in_q18._8_8_;
            auVar193[7] = puVar101[0x1e];
            puVar101 = puVar101 + 0x20;
            lVar144 = lVar144 + 8;
            auVar168 = a64_TBL(ZEXT816(0),auVar175,auVar90);
            auVar170 = a64_TBL(ZEXT816(0),auVar184,auVar90);
            auVar48._12_4_ = uVar97;
            auVar212 = a64_TBL(ZEXT816(0),auVar175,auVar48);
            auVar49._12_4_ = uVar97;
            auVar221 = a64_TBL(ZEXT816(0),auVar184,auVar49);
            auVar236 = a64_TBL(ZEXT816(0),auVar193,auVar90);
            auVar50._12_4_ = uVar97;
            auVar207 = a64_TBL(ZEXT816(0),auVar193,auVar50);
            auVar168 = NEON_ucvtf(auVar168,4);
            auVar170 = NEON_ucvtf(auVar170,4);
            auVar212 = NEON_ucvtf(auVar212,4);
            auVar221 = NEON_ucvtf(auVar221,4);
            auVar236 = NEON_ucvtf(auVar236,4);
            auVar207 = NEON_ucvtf(auVar207,4);
            in_q17._0_4_ = auVar212._0_4_ * 0.2126;
            in_q17._4_4_ = auVar212._4_4_ * 0.2126;
            in_q17._8_4_ = auVar212._8_4_ * 0.2126;
            in_q17._12_4_ = auVar212._12_4_ * 0.2126;
            in_q18._0_4_ = auVar221._0_4_ * 0.7152;
            in_q18._4_4_ = auVar221._4_4_ * 0.7152;
            in_q18._8_4_ = auVar221._8_4_ * 0.7152;
            in_q18._12_4_ = auVar221._12_4_ * 0.7152;
            auVar221._0_4_ = in_q17._0_4_ + in_q18._0_4_;
            auVar221._4_4_ = in_q17._4_4_ + in_q18._4_4_;
            auVar221._8_4_ = in_q17._8_4_ + in_q18._8_4_;
            auVar221._12_4_ = in_q17._12_4_ + in_q18._12_4_;
            pfVar118[4] = auVar221._8_4_ + auVar207._8_4_ * 0.0722;
            pfVar118[5] = auVar221._12_4_ + auVar207._12_4_ * 0.0722;
            *pfVar118 = auVar221._0_4_ + auVar207._0_4_ * 0.0722;
            pfVar118[1] = auVar221._4_4_ + auVar207._4_4_ * 0.0722;
            pfVar118[8] = auVar168._8_4_ * 0.2126 + auVar170._8_4_ * 0.7152 +
                          auVar236._8_4_ * 0.0722;
            pfVar118[9] = auVar168._12_4_ * 0.2126 + auVar170._12_4_ * 0.7152 +
                          auVar236._12_4_ * 0.0722;
            pfVar118[4] = auVar168._0_4_ * 0.2126 + auVar170._0_4_ * 0.7152 +
                          auVar236._0_4_ * 0.0722;
            pfVar118[5] = auVar168._4_4_ * 0.2126 + auVar170._4_4_ * 0.7152 +
                          auVar236._4_4_ * 0.0722;
            pfVar118 = pfVar118 + 8;
          } while (lVar144 != 0);
        }
        else {
          uVar130 = 0x10;
          if (((ulong)pvVar142 & 0xf) != 0) {
            uVar130 = (ulong)pvVar142 & 0xf;
          }
          auVar53._8_4_ = _UNK_00119ba8;
          auVar53._0_8_ = _DAT_00119ba0;
          auVar52._8_4_ = _UNK_00119ba8;
          auVar52._0_8_ = _DAT_00119ba0;
          auVar51._8_4_ = _UNK_00119ba8;
          auVar51._0_8_ = _DAT_00119ba0;
          auVar89._8_4_ = _UNK_00119be8;
          auVar89._0_8_ = _DAT_00119be0;
          auVar89._12_4_ = _UNK_00119bec;
          auVar85._8_8_ = _UNK_00119bd8;
          auVar85._0_8_ = _DAT_00119bd0;
          auVar81._8_8_ = _UNK_00119b48;
          auVar81._0_8_ = _DAT_00119b40;
          lVar135 = uVar126 - uVar130;
          uVar123 = uVar126;
          do {
            auVar174[0] = *puVar101;
            auVar183[0] = puVar101[1];
            auVar192[0] = puVar101[2];
            auVar174[1] = puVar101[4];
            auVar183[1] = puVar101[5];
            auVar192[1] = puVar101[6];
            auVar174[2] = puVar101[8];
            auVar183[2] = puVar101[9];
            auVar192[2] = puVar101[10];
            auVar174[3] = puVar101[0xc];
            auVar183[3] = puVar101[0xd];
            auVar192[3] = puVar101[0xe];
            auVar174[4] = puVar101[0x10];
            auVar183[4] = puVar101[0x11];
            auVar192[4] = puVar101[0x12];
            auVar174[5] = puVar101[0x14];
            auVar183[5] = puVar101[0x15];
            auVar192[5] = puVar101[0x16];
            auVar174[6] = puVar101[0x18];
            auVar183[6] = puVar101[0x19];
            auVar192[6] = puVar101[0x1a];
            auVar174[7] = puVar101[0x1c];
            auVar183[7] = puVar101[0x1d];
            auVar192[7] = puVar101[0x1e];
            auVar174[8] = puVar101[0x20];
            auVar183[8] = puVar101[0x21];
            auVar192[8] = puVar101[0x22];
            auVar174[9] = puVar101[0x24];
            auVar183[9] = puVar101[0x25];
            auVar192[9] = puVar101[0x26];
            auVar174[10] = puVar101[0x28];
            auVar183[10] = puVar101[0x29];
            auVar192[10] = puVar101[0x2a];
            auVar174[11] = puVar101[0x2c];
            auVar183[11] = puVar101[0x2d];
            auVar192[11] = puVar101[0x2e];
            auVar174[12] = puVar101[0x30];
            auVar183[12] = puVar101[0x31];
            auVar192[12] = puVar101[0x32];
            auVar174[13] = puVar101[0x34];
            auVar183[13] = puVar101[0x35];
            auVar192[13] = puVar101[0x36];
            auVar174[14] = puVar101[0x38];
            auVar183[14] = puVar101[0x39];
            auVar192[14] = puVar101[0x3a];
            auVar174[15] = puVar101[0x3c];
            auVar183[15] = puVar101[0x3d];
            auVar192[15] = puVar101[0x3e];
            puVar101 = puVar101 + 0x40;
            uVar123 = uVar123 - 0x10;
            auVar170 = a64_TBL(ZEXT816(0),auVar174,auVar81);
            auVar207 = a64_TBL(ZEXT816(0),auVar183,auVar81);
            auVar212 = a64_TBL(ZEXT816(0),auVar174,auVar85);
            auVar172 = a64_TBL(ZEXT816(0),auVar183,auVar85);
            auVar206 = a64_TBL(ZEXT816(0),auVar174,auVar89);
            auVar211 = a64_TBL(ZEXT816(0),auVar183,auVar89);
            auVar51._12_4_ = uVar97;
            auVar219 = a64_TBL(ZEXT816(0),auVar174,auVar51);
            auVar52._12_4_ = uVar97;
            auVar234 = a64_TBL(ZEXT816(0),auVar183,auVar52);
            in_q28 = a64_TBL(ZEXT816(0),auVar192,auVar81);
            in_q29 = a64_TBL(ZEXT816(0),auVar192,auVar85);
            auVar230 = a64_TBL(ZEXT816(0),auVar192,auVar89);
            auVar53._12_4_ = uVar97;
            auVar168 = a64_TBL(ZEXT816(0),auVar192,auVar53);
            auVar221 = NEON_ucvtf(auVar170,4);
            auVar236 = NEON_ucvtf(auVar207,4);
            auVar232 = NEON_ucvtf(auVar212,4);
            auVar172 = NEON_ucvtf(auVar172,4);
            auVar206 = NEON_ucvtf(auVar206,4);
            auVar211 = NEON_ucvtf(auVar211,4);
            auVar170 = NEON_ucvtf(auVar219,4);
            auVar207 = NEON_ucvtf(auVar234,4);
            auVar212 = NEON_ucvtf(in_q28,4);
            auVar219 = NEON_ucvtf(in_q29,4);
            in_q27 = NEON_ucvtf(auVar230,4);
            auVar168 = NEON_ucvtf(auVar168,4);
            in_q17._0_4_ = auVar170._0_4_ * 0.2126 + auVar207._0_4_ * 0.7152;
            in_q17._4_4_ = auVar170._4_4_ * 0.2126 + auVar207._4_4_ * 0.7152;
            in_q17._8_4_ = auVar170._8_4_ * 0.2126 + auVar207._8_4_ * 0.7152;
            in_q17._12_4_ = auVar170._12_4_ * 0.2126 + auVar207._12_4_ * 0.7152;
            in_q18._0_8_ = CONCAT44(auVar221._4_4_ * 0.2126 + auVar236._4_4_ * 0.7152 +
                                    auVar212._4_4_ * 0.0722,
                                    auVar221._0_4_ * 0.2126 + auVar236._0_4_ * 0.7152 +
                                    auVar212._0_4_ * 0.0722);
            in_q18._8_4_ = auVar221._8_4_ * 0.2126 + auVar236._8_4_ * 0.7152 +
                           auVar212._8_4_ * 0.0722;
            in_q18._12_4_ =
                 auVar221._12_4_ * 0.2126 + auVar236._12_4_ * 0.7152 + auVar212._12_4_ * 0.0722;
            auVar221._0_8_ =
                 CONCAT44(in_q17._4_4_ + auVar168._4_4_ * 0.0722,
                          in_q17._0_4_ + auVar168._0_4_ * 0.0722);
            auVar221._8_4_ = in_q17._8_4_ + auVar168._8_4_ * 0.0722;
            auVar221._12_4_ = in_q17._12_4_ + auVar168._12_4_ * 0.0722;
            *(float *)(puVar128 + 6) =
                 auVar232._8_4_ * 0.2126 + auVar172._8_4_ * 0.7152 + auVar219._8_4_ * 0.0722;
            *(float *)((long)puVar128 + 0x34) =
                 auVar232._12_4_ * 0.2126 + auVar172._12_4_ * 0.7152 + auVar219._12_4_ * 0.0722;
            *(float *)(puVar128 + 4) =
                 auVar232._0_4_ * 0.2126 + auVar172._0_4_ * 0.7152 + auVar219._0_4_ * 0.0722;
            *(float *)((long)puVar128 + 0x24) =
                 auVar232._4_4_ * 0.2126 + auVar172._4_4_ * 0.7152 + auVar219._4_4_ * 0.0722;
            puVar128[7] = in_q18._8_8_;
            puVar128[6] = in_q18._0_8_;
            puVar128[1] = auVar221._8_8_;
            *puVar128 = auVar221._0_8_;
            *(float *)(puVar128 + 4) =
                 auVar206._8_4_ * 0.2126 + auVar211._8_4_ * 0.7152 + in_q27._8_4_ * 0.0722;
            *(float *)((long)puVar128 + 0x24) =
                 auVar206._12_4_ * 0.2126 + auVar211._12_4_ * 0.7152 + in_q27._12_4_ * 0.0722;
            *(float *)(puVar128 + 2) =
                 auVar206._0_4_ * 0.2126 + auVar211._0_4_ * 0.7152 + in_q27._0_4_ * 0.0722;
            *(float *)((long)puVar128 + 0x14) =
                 auVar206._4_4_ * 0.2126 + auVar211._4_4_ * 0.7152 + in_q27._4_4_ * 0.0722;
            puVar128 = puVar128 + 8;
          } while (uVar130 != uVar123);
          if (8 < uVar130) goto LAB_0013abc0;
        }
      }
      lVar144 = uVar126 - lVar135;
      pbVar121 = local_b0 + lVar135 * 4 + uVar139 + 2;
      pfVar118 = (float *)((long)puVar104 + lVar135 * 4 + lVar116 * 4);
      do {
        pbVar1 = pbVar121 + -2;
        pbVar4 = pbVar121 + -1;
        lVar144 = lVar144 + -1;
        bVar163 = *pbVar121;
        pbVar121 = pbVar121 + 4;
        fVar151 = (float)NEON_ucvtf((uint)*pbVar1);
        fVar152 = (float)NEON_ucvtf((uint)*pbVar4);
        fVar155 = (float)NEON_ucvtf((uint)bVar163);
        *pfVar118 = fVar151 * 0.2126 + fVar152 * 0.7152 + fVar155 * 0.0722;
        uVar97 = _UNK_00119bac;
        pfVar118 = pfVar118 + 1;
      } while (lVar144 != 0);
      uVar139 = (ulong)(local_c0 << 1);
      if (uVar99 < 9) {
LAB_00139948:
        lVar135 = 0;
      }
      else {
        puVar128 = puVar104 + lVar116;
        puVar101 = local_b0 + uVar139;
        if ((puVar128 < local_b0 + uVar139 + uVar120 + -1) &&
           (puVar101 < (undefined *)((long)puVar128 + uVar120))) goto LAB_00139948;
        if (uVar99 < 0x11) {
          lVar135 = 0;
LAB_0013adb4:
          uVar97 = _UNK_00119bac;
          uVar130 = 8;
          if (((ulong)pvVar142 & 7) != 0) {
            uVar130 = (ulong)pvVar142 & 7;
          }
          lVar124 = lVar135 * 4;
          auVar44._8_4_ = _UNK_00119ba8;
          auVar44._0_8_ = _DAT_00119ba0;
          auVar43._8_4_ = _UNK_00119ba8;
          auVar43._0_8_ = _DAT_00119ba0;
          auVar42._8_4_ = _UNK_00119ba8;
          auVar42._0_8_ = _DAT_00119ba0;
          lVar144 = uVar130 + lVar135;
          lVar135 = uVar126 - uVar130;
          auVar92._8_4_ = _UNK_00119be8;
          auVar92._0_8_ = _DAT_00119be0;
          auVar92._12_4_ = _UNK_00119bec;
          puVar101 = local_b0 + uVar139 + lVar124;
          lVar144 = lVar144 - uVar126;
          pfVar118 = (float *)((long)puVar104 + lVar124 + lVar116 * 8);
          do {
            auVar177[0] = *puVar101;
            auVar186[0] = puVar101[1];
            auVar195[0] = puVar101[2];
            auVar177[1] = puVar101[4];
            auVar186[1] = puVar101[5];
            auVar195[1] = puVar101[6];
            auVar177[2] = puVar101[8];
            auVar186[2] = puVar101[9];
            auVar195[2] = puVar101[10];
            auVar177[3] = puVar101[0xc];
            auVar186[3] = puVar101[0xd];
            auVar195[3] = puVar101[0xe];
            auVar177[4] = puVar101[0x10];
            auVar186[4] = puVar101[0x11];
            auVar195[4] = puVar101[0x12];
            auVar177[5] = puVar101[0x14];
            auVar186[5] = puVar101[0x15];
            auVar195[5] = puVar101[0x16];
            auVar177[6] = puVar101[0x18];
            auVar186[6] = puVar101[0x19];
            auVar195[6] = puVar101[0x1a];
            auVar177._8_8_ = auVar221._8_8_;
            auVar177[7] = puVar101[0x1c];
            auVar186._8_8_ = in_q17._8_8_;
            auVar186[7] = puVar101[0x1d];
            auVar195._8_8_ = in_q18._8_8_;
            auVar195[7] = puVar101[0x1e];
            puVar101 = puVar101 + 0x20;
            lVar144 = lVar144 + 8;
            auVar168 = a64_TBL(ZEXT816(0),auVar177,auVar92);
            auVar170 = a64_TBL(ZEXT816(0),auVar186,auVar92);
            auVar42._12_4_ = uVar97;
            auVar212 = a64_TBL(ZEXT816(0),auVar177,auVar42);
            auVar43._12_4_ = uVar97;
            auVar221 = a64_TBL(ZEXT816(0),auVar186,auVar43);
            auVar236 = a64_TBL(ZEXT816(0),auVar195,auVar92);
            auVar44._12_4_ = uVar97;
            auVar207 = a64_TBL(ZEXT816(0),auVar195,auVar44);
            auVar168 = NEON_ucvtf(auVar168,4);
            auVar170 = NEON_ucvtf(auVar170,4);
            auVar212 = NEON_ucvtf(auVar212,4);
            auVar221 = NEON_ucvtf(auVar221,4);
            auVar236 = NEON_ucvtf(auVar236,4);
            auVar207 = NEON_ucvtf(auVar207,4);
            in_q17._0_4_ = auVar212._0_4_ * 0.2126;
            in_q17._4_4_ = auVar212._4_4_ * 0.2126;
            in_q17._8_4_ = auVar212._8_4_ * 0.2126;
            in_q17._12_4_ = auVar212._12_4_ * 0.2126;
            in_q18._0_4_ = auVar221._0_4_ * 0.7152;
            in_q18._4_4_ = auVar221._4_4_ * 0.7152;
            in_q18._8_4_ = auVar221._8_4_ * 0.7152;
            in_q18._12_4_ = auVar221._12_4_ * 0.7152;
            auVar221._0_4_ = in_q17._0_4_ + in_q18._0_4_;
            auVar221._4_4_ = in_q17._4_4_ + in_q18._4_4_;
            auVar221._8_4_ = in_q17._8_4_ + in_q18._8_4_;
            auVar221._12_4_ = in_q17._12_4_ + in_q18._12_4_;
            pfVar118[4] = auVar221._8_4_ + auVar207._8_4_ * 0.0722;
            pfVar118[5] = auVar221._12_4_ + auVar207._12_4_ * 0.0722;
            *pfVar118 = auVar221._0_4_ + auVar207._0_4_ * 0.0722;
            pfVar118[1] = auVar221._4_4_ + auVar207._4_4_ * 0.0722;
            pfVar118[8] = auVar168._8_4_ * 0.2126 + auVar170._8_4_ * 0.7152 +
                          auVar236._8_4_ * 0.0722;
            pfVar118[9] = auVar168._12_4_ * 0.2126 + auVar170._12_4_ * 0.7152 +
                          auVar236._12_4_ * 0.0722;
            pfVar118[4] = auVar168._0_4_ * 0.2126 + auVar170._0_4_ * 0.7152 +
                          auVar236._0_4_ * 0.0722;
            pfVar118[5] = auVar168._4_4_ * 0.2126 + auVar170._4_4_ * 0.7152 +
                          auVar236._4_4_ * 0.0722;
            pfVar118 = pfVar118 + 8;
          } while (lVar144 != 0);
        }
        else {
          uVar130 = 0x10;
          if (((ulong)pvVar142 & 0xf) != 0) {
            uVar130 = (ulong)pvVar142 & 0xf;
          }
          auVar47._8_4_ = _UNK_00119ba8;
          auVar47._0_8_ = _DAT_00119ba0;
          auVar46._8_4_ = _UNK_00119ba8;
          auVar46._0_8_ = _DAT_00119ba0;
          auVar45._8_4_ = _UNK_00119ba8;
          auVar45._0_8_ = _DAT_00119ba0;
          auVar91._8_4_ = _UNK_00119be8;
          auVar91._0_8_ = _DAT_00119be0;
          auVar91._12_4_ = _UNK_00119bec;
          auVar86._8_8_ = _UNK_00119bd8;
          auVar86._0_8_ = _DAT_00119bd0;
          auVar82._8_8_ = _UNK_00119b48;
          auVar82._0_8_ = _DAT_00119b40;
          lVar135 = uVar126 - uVar130;
          uVar123 = uVar126;
          do {
            auVar176[0] = *puVar101;
            auVar185[0] = puVar101[1];
            auVar194[0] = puVar101[2];
            auVar176[1] = puVar101[4];
            auVar185[1] = puVar101[5];
            auVar194[1] = puVar101[6];
            auVar176[2] = puVar101[8];
            auVar185[2] = puVar101[9];
            auVar194[2] = puVar101[10];
            auVar176[3] = puVar101[0xc];
            auVar185[3] = puVar101[0xd];
            auVar194[3] = puVar101[0xe];
            auVar176[4] = puVar101[0x10];
            auVar185[4] = puVar101[0x11];
            auVar194[4] = puVar101[0x12];
            auVar176[5] = puVar101[0x14];
            auVar185[5] = puVar101[0x15];
            auVar194[5] = puVar101[0x16];
            auVar176[6] = puVar101[0x18];
            auVar185[6] = puVar101[0x19];
            auVar194[6] = puVar101[0x1a];
            auVar176[7] = puVar101[0x1c];
            auVar185[7] = puVar101[0x1d];
            auVar194[7] = puVar101[0x1e];
            auVar176[8] = puVar101[0x20];
            auVar185[8] = puVar101[0x21];
            auVar194[8] = puVar101[0x22];
            auVar176[9] = puVar101[0x24];
            auVar185[9] = puVar101[0x25];
            auVar194[9] = puVar101[0x26];
            auVar176[10] = puVar101[0x28];
            auVar185[10] = puVar101[0x29];
            auVar194[10] = puVar101[0x2a];
            auVar176[11] = puVar101[0x2c];
            auVar185[11] = puVar101[0x2d];
            auVar194[11] = puVar101[0x2e];
            auVar176[12] = puVar101[0x30];
            auVar185[12] = puVar101[0x31];
            auVar194[12] = puVar101[0x32];
            auVar176[13] = puVar101[0x34];
            auVar185[13] = puVar101[0x35];
            auVar194[13] = puVar101[0x36];
            auVar176[14] = puVar101[0x38];
            auVar185[14] = puVar101[0x39];
            auVar194[14] = puVar101[0x3a];
            auVar176[15] = puVar101[0x3c];
            auVar185[15] = puVar101[0x3d];
            auVar194[15] = puVar101[0x3e];
            puVar101 = puVar101 + 0x40;
            uVar123 = uVar123 - 0x10;
            auVar170 = a64_TBL(ZEXT816(0),auVar176,auVar82);
            auVar207 = a64_TBL(ZEXT816(0),auVar185,auVar82);
            auVar212 = a64_TBL(ZEXT816(0),auVar176,auVar86);
            auVar172 = a64_TBL(ZEXT816(0),auVar185,auVar86);
            auVar206 = a64_TBL(ZEXT816(0),auVar176,auVar91);
            auVar211 = a64_TBL(ZEXT816(0),auVar185,auVar91);
            auVar45._12_4_ = uVar97;
            auVar219 = a64_TBL(ZEXT816(0),auVar176,auVar45);
            auVar46._12_4_ = uVar97;
            auVar234 = a64_TBL(ZEXT816(0),auVar185,auVar46);
            in_q28 = a64_TBL(ZEXT816(0),auVar194,auVar82);
            in_q29 = a64_TBL(ZEXT816(0),auVar194,auVar86);
            auVar230 = a64_TBL(ZEXT816(0),auVar194,auVar91);
            auVar47._12_4_ = uVar97;
            auVar168 = a64_TBL(ZEXT816(0),auVar194,auVar47);
            auVar221 = NEON_ucvtf(auVar170,4);
            auVar236 = NEON_ucvtf(auVar207,4);
            auVar232 = NEON_ucvtf(auVar212,4);
            auVar172 = NEON_ucvtf(auVar172,4);
            auVar206 = NEON_ucvtf(auVar206,4);
            auVar211 = NEON_ucvtf(auVar211,4);
            auVar170 = NEON_ucvtf(auVar219,4);
            auVar207 = NEON_ucvtf(auVar234,4);
            auVar212 = NEON_ucvtf(in_q28,4);
            auVar219 = NEON_ucvtf(in_q29,4);
            in_q27 = NEON_ucvtf(auVar230,4);
            auVar168 = NEON_ucvtf(auVar168,4);
            in_q17._0_4_ = auVar170._0_4_ * 0.2126 + auVar207._0_4_ * 0.7152;
            in_q17._4_4_ = auVar170._4_4_ * 0.2126 + auVar207._4_4_ * 0.7152;
            in_q17._8_4_ = auVar170._8_4_ * 0.2126 + auVar207._8_4_ * 0.7152;
            in_q17._12_4_ = auVar170._12_4_ * 0.2126 + auVar207._12_4_ * 0.7152;
            in_q18._0_8_ = CONCAT44(auVar221._4_4_ * 0.2126 + auVar236._4_4_ * 0.7152 +
                                    auVar212._4_4_ * 0.0722,
                                    auVar221._0_4_ * 0.2126 + auVar236._0_4_ * 0.7152 +
                                    auVar212._0_4_ * 0.0722);
            in_q18._8_4_ = auVar221._8_4_ * 0.2126 + auVar236._8_4_ * 0.7152 +
                           auVar212._8_4_ * 0.0722;
            in_q18._12_4_ =
                 auVar221._12_4_ * 0.2126 + auVar236._12_4_ * 0.7152 + auVar212._12_4_ * 0.0722;
            auVar221._0_8_ =
                 CONCAT44(in_q17._4_4_ + auVar168._4_4_ * 0.0722,
                          in_q17._0_4_ + auVar168._0_4_ * 0.0722);
            auVar221._8_4_ = in_q17._8_4_ + auVar168._8_4_ * 0.0722;
            auVar221._12_4_ = in_q17._12_4_ + auVar168._12_4_ * 0.0722;
            *(float *)(puVar128 + 6) =
                 auVar232._8_4_ * 0.2126 + auVar172._8_4_ * 0.7152 + auVar219._8_4_ * 0.0722;
            *(float *)((long)puVar128 + 0x34) =
                 auVar232._12_4_ * 0.2126 + auVar172._12_4_ * 0.7152 + auVar219._12_4_ * 0.0722;
            *(float *)(puVar128 + 4) =
                 auVar232._0_4_ * 0.2126 + auVar172._0_4_ * 0.7152 + auVar219._0_4_ * 0.0722;
            *(float *)((long)puVar128 + 0x24) =
                 auVar232._4_4_ * 0.2126 + auVar172._4_4_ * 0.7152 + auVar219._4_4_ * 0.0722;
            puVar128[7] = in_q18._8_8_;
            puVar128[6] = in_q18._0_8_;
            puVar128[1] = auVar221._8_8_;
            *puVar128 = auVar221._0_8_;
            *(float *)(puVar128 + 4) =
                 auVar206._8_4_ * 0.2126 + auVar211._8_4_ * 0.7152 + in_q27._8_4_ * 0.0722;
            *(float *)((long)puVar128 + 0x24) =
                 auVar206._12_4_ * 0.2126 + auVar211._12_4_ * 0.7152 + in_q27._12_4_ * 0.0722;
            *(float *)(puVar128 + 2) =
                 auVar206._0_4_ * 0.2126 + auVar211._0_4_ * 0.7152 + in_q27._0_4_ * 0.0722;
            *(float *)((long)puVar128 + 0x14) =
                 auVar206._4_4_ * 0.2126 + auVar211._4_4_ * 0.7152 + in_q27._4_4_ * 0.0722;
            puVar128 = puVar128 + 8;
          } while (uVar130 != uVar123);
          if (8 < uVar130) goto LAB_0013adb4;
        }
      }
      lVar144 = uVar126 - lVar135;
      pbVar121 = local_b0 + lVar135 * 4 + uVar139 + 2;
      pfVar118 = (float *)((long)puVar104 + lVar135 * 4 + lVar116 * 8);
      do {
        pbVar1 = pbVar121 + -2;
        pbVar4 = pbVar121 + -1;
        lVar144 = lVar144 + -1;
        bVar163 = *pbVar121;
        pbVar121 = pbVar121 + 4;
        fVar151 = (float)NEON_ucvtf((uint)*pbVar1);
        fVar152 = (float)NEON_ucvtf((uint)*pbVar4);
        fVar155 = (float)NEON_ucvtf((uint)bVar163);
        *pfVar118 = fVar151 * 0.2126 + fVar152 * 0.7152 + fVar155 * 0.0722;
        uVar97 = _UNK_00119bac;
        pfVar118 = pfVar118 + 1;
      } while (lVar144 != 0);
      if ((uVar99 < 9) ||
         ((puVar105 < local_e0 + (uVar120 - 1) &&
          (local_e0 < (undefined *)((long)puVar105 + uVar120))))) {
        uVar139 = 0;
      }
      else {
        if (uVar99 < 0x11) {
          uVar139 = 0;
        }
        else {
          auVar41._8_4_ = _UNK_00119ba8;
          auVar41._0_8_ = _DAT_00119ba0;
          auVar40._8_4_ = _UNK_00119ba8;
          auVar40._0_8_ = _DAT_00119ba0;
          auVar39._8_4_ = _UNK_00119ba8;
          auVar39._0_8_ = _DAT_00119ba0;
          uVar130 = 0x10;
          if (((ulong)pvVar142 & 0xf) != 0) {
            uVar130 = (ulong)pvVar142 & 0xf;
          }
          auVar93._8_4_ = _UNK_00119be8;
          auVar93._0_8_ = _DAT_00119be0;
          auVar93._12_4_ = _UNK_00119bec;
          auVar87._8_8_ = _UNK_00119bd8;
          auVar87._0_8_ = _DAT_00119bd0;
          auVar83._8_8_ = _UNK_00119b48;
          auVar83._0_8_ = _DAT_00119b40;
          uVar139 = uVar126 - uVar130;
          uVar123 = uVar126;
          puVar104 = puVar105;
          puVar101 = local_e0;
          do {
            auVar178[0] = *puVar101;
            auVar187[0] = puVar101[1];
            auVar196[0] = puVar101[2];
            auVar178[1] = puVar101[4];
            auVar187[1] = puVar101[5];
            auVar196[1] = puVar101[6];
            auVar178[2] = puVar101[8];
            auVar187[2] = puVar101[9];
            auVar196[2] = puVar101[10];
            auVar178[3] = puVar101[0xc];
            auVar187[3] = puVar101[0xd];
            auVar196[3] = puVar101[0xe];
            auVar178[4] = puVar101[0x10];
            auVar187[4] = puVar101[0x11];
            auVar196[4] = puVar101[0x12];
            auVar178[5] = puVar101[0x14];
            auVar187[5] = puVar101[0x15];
            auVar196[5] = puVar101[0x16];
            auVar178[6] = puVar101[0x18];
            auVar187[6] = puVar101[0x19];
            auVar196[6] = puVar101[0x1a];
            auVar178[7] = puVar101[0x1c];
            auVar187[7] = puVar101[0x1d];
            auVar196[7] = puVar101[0x1e];
            auVar178[8] = puVar101[0x20];
            auVar187[8] = puVar101[0x21];
            auVar196[8] = puVar101[0x22];
            auVar178[9] = puVar101[0x24];
            auVar187[9] = puVar101[0x25];
            auVar196[9] = puVar101[0x26];
            auVar178[10] = puVar101[0x28];
            auVar187[10] = puVar101[0x29];
            auVar196[10] = puVar101[0x2a];
            auVar178[11] = puVar101[0x2c];
            auVar187[11] = puVar101[0x2d];
            auVar196[11] = puVar101[0x2e];
            auVar178[12] = puVar101[0x30];
            auVar187[12] = puVar101[0x31];
            auVar196[12] = puVar101[0x32];
            auVar178[13] = puVar101[0x34];
            auVar187[13] = puVar101[0x35];
            auVar196[13] = puVar101[0x36];
            auVar178[14] = puVar101[0x38];
            auVar187[14] = puVar101[0x39];
            auVar196[14] = puVar101[0x3a];
            auVar178[15] = puVar101[0x3c];
            auVar187[15] = puVar101[0x3d];
            auVar196[15] = puVar101[0x3e];
            puVar101 = puVar101 + 0x40;
            uVar123 = uVar123 - 0x10;
            auVar170 = a64_TBL(ZEXT816(0),auVar178,auVar83);
            auVar207 = a64_TBL(ZEXT816(0),auVar187,auVar83);
            auVar212 = a64_TBL(ZEXT816(0),auVar178,auVar87);
            auVar172 = a64_TBL(ZEXT816(0),auVar187,auVar87);
            auVar206 = a64_TBL(ZEXT816(0),auVar178,auVar93);
            auVar211 = a64_TBL(ZEXT816(0),auVar187,auVar93);
            auVar39._12_4_ = uVar97;
            auVar219 = a64_TBL(ZEXT816(0),auVar178,auVar39);
            auVar40._12_4_ = uVar97;
            auVar234 = a64_TBL(ZEXT816(0),auVar187,auVar40);
            in_q28 = a64_TBL(ZEXT816(0),auVar196,auVar83);
            in_q29 = a64_TBL(ZEXT816(0),auVar196,auVar87);
            auVar230 = a64_TBL(ZEXT816(0),auVar196,auVar93);
            auVar41._12_4_ = uVar97;
            auVar168 = a64_TBL(ZEXT816(0),auVar196,auVar41);
            auVar221 = NEON_ucvtf(auVar170,4);
            auVar236 = NEON_ucvtf(auVar207,4);
            auVar232 = NEON_ucvtf(auVar212,4);
            auVar172 = NEON_ucvtf(auVar172,4);
            auVar206 = NEON_ucvtf(auVar206,4);
            auVar211 = NEON_ucvtf(auVar211,4);
            auVar170 = NEON_ucvtf(auVar219,4);
            auVar207 = NEON_ucvtf(auVar234,4);
            auVar212 = NEON_ucvtf(in_q28,4);
            auVar219 = NEON_ucvtf(in_q29,4);
            in_q27 = NEON_ucvtf(auVar230,4);
            auVar168 = NEON_ucvtf(auVar168,4);
            in_q17._0_4_ = auVar170._0_4_ * 0.2126 + auVar207._0_4_ * 0.7152;
            in_q17._4_4_ = auVar170._4_4_ * 0.2126 + auVar207._4_4_ * 0.7152;
            in_q17._8_4_ = auVar170._8_4_ * 0.2126 + auVar207._8_4_ * 0.7152;
            in_q17._12_4_ = auVar170._12_4_ * 0.2126 + auVar207._12_4_ * 0.7152;
            in_q18._0_8_ = CONCAT44(auVar221._4_4_ * 0.2126 + auVar236._4_4_ * 0.7152 +
                                    auVar212._4_4_ * 0.0722,
                                    auVar221._0_4_ * 0.2126 + auVar236._0_4_ * 0.7152 +
                                    auVar212._0_4_ * 0.0722);
            in_q18._8_4_ = auVar221._8_4_ * 0.2126 + auVar236._8_4_ * 0.7152 +
                           auVar212._8_4_ * 0.0722;
            in_q18._12_4_ =
                 auVar221._12_4_ * 0.2126 + auVar236._12_4_ * 0.7152 + auVar212._12_4_ * 0.0722;
            auVar221._0_8_ =
                 CONCAT44(in_q17._4_4_ + auVar168._4_4_ * 0.0722,
                          in_q17._0_4_ + auVar168._0_4_ * 0.0722);
            auVar221._8_4_ = in_q17._8_4_ + auVar168._8_4_ * 0.0722;
            auVar221._12_4_ = in_q17._12_4_ + auVar168._12_4_ * 0.0722;
            *(float *)(puVar104 + 6) =
                 auVar232._8_4_ * 0.2126 + auVar172._8_4_ * 0.7152 + auVar219._8_4_ * 0.0722;
            *(float *)((long)puVar104 + 0x34) =
                 auVar232._12_4_ * 0.2126 + auVar172._12_4_ * 0.7152 + auVar219._12_4_ * 0.0722;
            *(float *)(puVar104 + 4) =
                 auVar232._0_4_ * 0.2126 + auVar172._0_4_ * 0.7152 + auVar219._0_4_ * 0.0722;
            *(float *)((long)puVar104 + 0x24) =
                 auVar232._4_4_ * 0.2126 + auVar172._4_4_ * 0.7152 + auVar219._4_4_ * 0.0722;
            puVar104[7] = in_q18._8_8_;
            puVar104[6] = in_q18._0_8_;
            puVar104[1] = auVar221._8_8_;
            *puVar104 = auVar221._0_8_;
            *(float *)(puVar104 + 4) =
                 auVar206._8_4_ * 0.2126 + auVar211._8_4_ * 0.7152 + in_q27._8_4_ * 0.0722;
            *(float *)((long)puVar104 + 0x24) =
                 auVar206._12_4_ * 0.2126 + auVar211._12_4_ * 0.7152 + in_q27._12_4_ * 0.0722;
            *(float *)(puVar104 + 2) =
                 auVar206._0_4_ * 0.2126 + auVar211._0_4_ * 0.7152 + in_q27._0_4_ * 0.0722;
            *(float *)((long)puVar104 + 0x14) =
                 auVar206._4_4_ * 0.2126 + auVar211._4_4_ * 0.7152 + in_q27._4_4_ * 0.0722;
            puVar104 = puVar104 + 8;
          } while (uVar130 != uVar123);
          if (uVar130 < 9) goto LAB_001399f8;
        }
        uVar97 = _UNK_00119bac;
        uVar130 = 8;
        if (((ulong)pvVar142 & 7) != 0) {
          uVar130 = (ulong)pvVar142 & 7;
        }
        lVar144 = uVar139 * 4;
        lVar135 = uVar130 + uVar139;
        auVar80._8_4_ = _UNK_00119ba8;
        auVar80._0_8_ = _DAT_00119ba0;
        auVar79._8_4_ = _UNK_00119ba8;
        auVar79._0_8_ = _DAT_00119ba0;
        auVar78._8_4_ = _UNK_00119ba8;
        auVar78._0_8_ = _DAT_00119ba0;
        auVar94._8_4_ = _UNK_00119be8;
        auVar94._0_8_ = _DAT_00119be0;
        auVar94._12_4_ = _UNK_00119bec;
        uVar139 = uVar126 - uVar130;
        puVar101 = local_e0 + lVar144;
        lVar135 = lVar135 - uVar126;
        pfVar118 = (float *)((long)puVar105 + lVar144);
        do {
          auVar179[0] = *puVar101;
          auVar188[0] = puVar101[1];
          auVar197[0] = puVar101[2];
          auVar179[1] = puVar101[4];
          auVar188[1] = puVar101[5];
          auVar197[1] = puVar101[6];
          auVar179[2] = puVar101[8];
          auVar188[2] = puVar101[9];
          auVar197[2] = puVar101[10];
          auVar179[3] = puVar101[0xc];
          auVar188[3] = puVar101[0xd];
          auVar197[3] = puVar101[0xe];
          auVar179[4] = puVar101[0x10];
          auVar188[4] = puVar101[0x11];
          auVar197[4] = puVar101[0x12];
          auVar179[5] = puVar101[0x14];
          auVar188[5] = puVar101[0x15];
          auVar197[5] = puVar101[0x16];
          auVar179[6] = puVar101[0x18];
          auVar188[6] = puVar101[0x19];
          auVar197[6] = puVar101[0x1a];
          auVar179._8_8_ = auVar221._8_8_;
          auVar179[7] = puVar101[0x1c];
          auVar188._8_8_ = in_q17._8_8_;
          auVar188[7] = puVar101[0x1d];
          auVar197._8_8_ = in_q18._8_8_;
          auVar197[7] = puVar101[0x1e];
          puVar101 = puVar101 + 0x20;
          lVar135 = lVar135 + 8;
          auVar168 = a64_TBL(ZEXT816(0),auVar179,auVar94);
          auVar170 = a64_TBL(ZEXT816(0),auVar188,auVar94);
          auVar78._12_4_ = uVar97;
          auVar212 = a64_TBL(ZEXT816(0),auVar179,auVar78);
          auVar79._12_4_ = uVar97;
          auVar221 = a64_TBL(ZEXT816(0),auVar188,auVar79);
          auVar236 = a64_TBL(ZEXT816(0),auVar197,auVar94);
          auVar80._12_4_ = uVar97;
          auVar207 = a64_TBL(ZEXT816(0),auVar197,auVar80);
          auVar168 = NEON_ucvtf(auVar168,4);
          auVar170 = NEON_ucvtf(auVar170,4);
          auVar212 = NEON_ucvtf(auVar212,4);
          auVar221 = NEON_ucvtf(auVar221,4);
          auVar236 = NEON_ucvtf(auVar236,4);
          auVar207 = NEON_ucvtf(auVar207,4);
          in_q17._0_4_ = auVar212._0_4_ * 0.2126;
          in_q17._4_4_ = auVar212._4_4_ * 0.2126;
          in_q17._8_4_ = auVar212._8_4_ * 0.2126;
          in_q17._12_4_ = auVar212._12_4_ * 0.2126;
          in_q18._0_4_ = auVar221._0_4_ * 0.7152;
          in_q18._4_4_ = auVar221._4_4_ * 0.7152;
          in_q18._8_4_ = auVar221._8_4_ * 0.7152;
          in_q18._12_4_ = auVar221._12_4_ * 0.7152;
          auVar221._0_4_ = in_q17._0_4_ + in_q18._0_4_;
          auVar221._4_4_ = in_q17._4_4_ + in_q18._4_4_;
          auVar221._8_4_ = in_q17._8_4_ + in_q18._8_4_;
          auVar221._12_4_ = in_q17._12_4_ + in_q18._12_4_;
          pfVar118[4] = auVar221._8_4_ + auVar207._8_4_ * 0.0722;
          pfVar118[5] = auVar221._12_4_ + auVar207._12_4_ * 0.0722;
          *pfVar118 = auVar221._0_4_ + auVar207._0_4_ * 0.0722;
          pfVar118[1] = auVar221._4_4_ + auVar207._4_4_ * 0.0722;
          pfVar118[8] = auVar168._8_4_ * 0.2126 + auVar170._8_4_ * 0.7152 + auVar236._8_4_ * 0.0722;
          pfVar118[9] = auVar168._12_4_ * 0.2126 + auVar170._12_4_ * 0.7152 +
                        auVar236._12_4_ * 0.0722;
          pfVar118[4] = auVar168._0_4_ * 0.2126 + auVar170._0_4_ * 0.7152 + auVar236._0_4_ * 0.0722;
          pfVar118[5] = auVar168._4_4_ * 0.2126 + auVar170._4_4_ * 0.7152 + auVar236._4_4_ * 0.0722;
          pfVar118 = pfVar118 + 8;
        } while (lVar135 != 0);
      }
LAB_001399f8:
      pbVar121 = local_e0 + uVar139 * 4 + 2;
      do {
        pbVar1 = pbVar121 + -2;
        pbVar4 = pbVar121 + -1;
        bVar163 = *pbVar121;
        pbVar121 = pbVar121 + 4;
        fVar151 = (float)NEON_ucvtf((uint)*pbVar1);
        fVar152 = (float)NEON_ucvtf((uint)*pbVar4);
        fVar155 = (float)NEON_ucvtf((uint)bVar163);
        *(float *)((long)puVar105 + uVar139 * 4) =
             fVar151 * 0.2126 + fVar152 * 0.7152 + fVar155 * 0.0722;
        uVar97 = _UNK_00119bac;
        uVar139 = uVar139 + 1;
      } while (uVar126 != uVar139);
      uVar139 = (ulong)local_f0;
      if (uVar99 < 9) {
LAB_00139a9c:
        lVar135 = 0;
      }
      else {
        puVar104 = (undefined8 *)((long)puVar105 + lVar116 * 4);
        puVar101 = local_e0 + uVar139;
        if ((puVar104 < local_e0 + uVar139 + uVar126 * 4 + -1) &&
           (puVar101 < (undefined *)((long)puVar105 + (lVar116 + uVar126) * 4))) goto LAB_00139a9c;
        if (uVar99 < 0x11) {
          lVar135 = 0;
LAB_0013b19c:
          uVar97 = _UNK_00119bac;
          uVar130 = 8;
          if (((ulong)pvVar142 & 7) != 0) {
            uVar130 = (ulong)pvVar142 & 7;
          }
          lVar124 = lVar135 * 4;
          auVar35._8_4_ = _UNK_00119ba8;
          auVar35._0_8_ = _DAT_00119ba0;
          auVar34._8_4_ = _UNK_00119ba8;
          auVar34._0_8_ = _DAT_00119ba0;
          auVar33._8_4_ = _UNK_00119ba8;
          auVar33._0_8_ = _DAT_00119ba0;
          lVar144 = uVar130 + lVar135;
          lVar135 = uVar126 - uVar130;
          auVar96._8_4_ = _UNK_00119be8;
          auVar96._0_8_ = _DAT_00119be0;
          auVar96._12_4_ = _UNK_00119bec;
          puVar101 = local_e0 + lVar124 + uVar139;
          lVar144 = lVar144 - uVar126;
          pfVar118 = (float *)((long)puVar105 + lVar124 + lVar116 * 4);
          do {
            auVar181[0] = *puVar101;
            auVar190[0] = puVar101[1];
            auVar199[0] = puVar101[2];
            auVar181[1] = puVar101[4];
            auVar190[1] = puVar101[5];
            auVar199[1] = puVar101[6];
            auVar181[2] = puVar101[8];
            auVar190[2] = puVar101[9];
            auVar199[2] = puVar101[10];
            auVar181[3] = puVar101[0xc];
            auVar190[3] = puVar101[0xd];
            auVar199[3] = puVar101[0xe];
            auVar181[4] = puVar101[0x10];
            auVar190[4] = puVar101[0x11];
            auVar199[4] = puVar101[0x12];
            auVar181[5] = puVar101[0x14];
            auVar190[5] = puVar101[0x15];
            auVar199[5] = puVar101[0x16];
            auVar181[6] = puVar101[0x18];
            auVar190[6] = puVar101[0x19];
            auVar199[6] = puVar101[0x1a];
            auVar181._8_8_ = auVar221._8_8_;
            auVar181[7] = puVar101[0x1c];
            auVar190._8_8_ = in_q17._8_8_;
            auVar190[7] = puVar101[0x1d];
            auVar199._8_8_ = in_q18._8_8_;
            auVar199[7] = puVar101[0x1e];
            puVar101 = puVar101 + 0x20;
            lVar144 = lVar144 + 8;
            auVar168 = a64_TBL(ZEXT816(0),auVar181,auVar96);
            auVar170 = a64_TBL(ZEXT816(0),auVar190,auVar96);
            auVar33._12_4_ = uVar97;
            auVar212 = a64_TBL(ZEXT816(0),auVar181,auVar33);
            auVar34._12_4_ = uVar97;
            auVar221 = a64_TBL(ZEXT816(0),auVar190,auVar34);
            auVar236 = a64_TBL(ZEXT816(0),auVar199,auVar96);
            auVar35._12_4_ = uVar97;
            auVar207 = a64_TBL(ZEXT816(0),auVar199,auVar35);
            auVar168 = NEON_ucvtf(auVar168,4);
            auVar170 = NEON_ucvtf(auVar170,4);
            auVar212 = NEON_ucvtf(auVar212,4);
            auVar221 = NEON_ucvtf(auVar221,4);
            auVar236 = NEON_ucvtf(auVar236,4);
            auVar207 = NEON_ucvtf(auVar207,4);
            in_q17._0_4_ = auVar212._0_4_ * 0.2126;
            in_q17._4_4_ = auVar212._4_4_ * 0.2126;
            in_q17._8_4_ = auVar212._8_4_ * 0.2126;
            in_q17._12_4_ = auVar212._12_4_ * 0.2126;
            in_q18._0_4_ = auVar221._0_4_ * 0.7152;
            in_q18._4_4_ = auVar221._4_4_ * 0.7152;
            in_q18._8_4_ = auVar221._8_4_ * 0.7152;
            in_q18._12_4_ = auVar221._12_4_ * 0.7152;
            auVar221._0_4_ = in_q17._0_4_ + in_q18._0_4_;
            auVar221._4_4_ = in_q17._4_4_ + in_q18._4_4_;
            auVar221._8_4_ = in_q17._8_4_ + in_q18._8_4_;
            auVar221._12_4_ = in_q17._12_4_ + in_q18._12_4_;
            pfVar118[4] = auVar221._8_4_ + auVar207._8_4_ * 0.0722;
            pfVar118[5] = auVar221._12_4_ + auVar207._12_4_ * 0.0722;
            *pfVar118 = auVar221._0_4_ + auVar207._0_4_ * 0.0722;
            pfVar118[1] = auVar221._4_4_ + auVar207._4_4_ * 0.0722;
            pfVar118[8] = auVar168._8_4_ * 0.2126 + auVar170._8_4_ * 0.7152 +
                          auVar236._8_4_ * 0.0722;
            pfVar118[9] = auVar168._12_4_ * 0.2126 + auVar170._12_4_ * 0.7152 +
                          auVar236._12_4_ * 0.0722;
            pfVar118[4] = auVar168._0_4_ * 0.2126 + auVar170._0_4_ * 0.7152 +
                          auVar236._0_4_ * 0.0722;
            pfVar118[5] = auVar168._4_4_ * 0.2126 + auVar170._4_4_ * 0.7152 +
                          auVar236._4_4_ * 0.0722;
            pfVar118 = pfVar118 + 8;
          } while (lVar144 != 0);
        }
        else {
          uVar130 = 0x10;
          if (((ulong)pvVar142 & 0xf) != 0) {
            uVar130 = (ulong)pvVar142 & 0xf;
          }
          auVar38._8_4_ = _UNK_00119ba8;
          auVar38._0_8_ = _DAT_00119ba0;
          auVar37._8_4_ = _UNK_00119ba8;
          auVar37._0_8_ = _DAT_00119ba0;
          auVar36._8_4_ = _UNK_00119ba8;
          auVar36._0_8_ = _DAT_00119ba0;
          auVar95._8_4_ = _UNK_00119be8;
          auVar95._0_8_ = _DAT_00119be0;
          auVar95._12_4_ = _UNK_00119bec;
          auVar88._8_8_ = _UNK_00119bd8;
          auVar88._0_8_ = _DAT_00119bd0;
          auVar84._8_8_ = _UNK_00119b48;
          auVar84._0_8_ = _DAT_00119b40;
          lVar135 = uVar126 - uVar130;
          uVar123 = uVar126;
          do {
            auVar180[0] = *puVar101;
            auVar189[0] = puVar101[1];
            auVar198[0] = puVar101[2];
            auVar180[1] = puVar101[4];
            auVar189[1] = puVar101[5];
            auVar198[1] = puVar101[6];
            auVar180[2] = puVar101[8];
            auVar189[2] = puVar101[9];
            auVar198[2] = puVar101[10];
            auVar180[3] = puVar101[0xc];
            auVar189[3] = puVar101[0xd];
            auVar198[3] = puVar101[0xe];
            auVar180[4] = puVar101[0x10];
            auVar189[4] = puVar101[0x11];
            auVar198[4] = puVar101[0x12];
            auVar180[5] = puVar101[0x14];
            auVar189[5] = puVar101[0x15];
            auVar198[5] = puVar101[0x16];
            auVar180[6] = puVar101[0x18];
            auVar189[6] = puVar101[0x19];
            auVar198[6] = puVar101[0x1a];
            auVar180[7] = puVar101[0x1c];
            auVar189[7] = puVar101[0x1d];
            auVar198[7] = puVar101[0x1e];
            auVar180[8] = puVar101[0x20];
            auVar189[8] = puVar101[0x21];
            auVar198[8] = puVar101[0x22];
            auVar180[9] = puVar101[0x24];
            auVar189[9] = puVar101[0x25];
            auVar198[9] = puVar101[0x26];
            auVar180[10] = puVar101[0x28];
            auVar189[10] = puVar101[0x29];
            auVar198[10] = puVar101[0x2a];
            auVar180[11] = puVar101[0x2c];
            auVar189[11] = puVar101[0x2d];
            auVar198[11] = puVar101[0x2e];
            auVar180[12] = puVar101[0x30];
            auVar189[12] = puVar101[0x31];
            auVar198[12] = puVar101[0x32];
            auVar180[13] = puVar101[0x34];
            auVar189[13] = puVar101[0x35];
            auVar198[13] = puVar101[0x36];
            auVar180[14] = puVar101[0x38];
            auVar189[14] = puVar101[0x39];
            auVar198[14] = puVar101[0x3a];
            auVar180[15] = puVar101[0x3c];
            auVar189[15] = puVar101[0x3d];
            auVar198[15] = puVar101[0x3e];
            puVar101 = puVar101 + 0x40;
            uVar123 = uVar123 - 0x10;
            auVar170 = a64_TBL(ZEXT816(0),auVar180,auVar84);
            auVar207 = a64_TBL(ZEXT816(0),auVar189,auVar84);
            auVar212 = a64_TBL(ZEXT816(0),auVar180,auVar88);
            auVar172 = a64_TBL(ZEXT816(0),auVar189,auVar88);
            auVar206 = a64_TBL(ZEXT816(0),auVar180,auVar95);
            auVar211 = a64_TBL(ZEXT816(0),auVar189,auVar95);
            auVar36._12_4_ = uVar97;
            auVar219 = a64_TBL(ZEXT816(0),auVar180,auVar36);
            auVar37._12_4_ = uVar97;
            auVar234 = a64_TBL(ZEXT816(0),auVar189,auVar37);
            in_q28 = a64_TBL(ZEXT816(0),auVar198,auVar84);
            in_q29 = a64_TBL(ZEXT816(0),auVar198,auVar88);
            auVar230 = a64_TBL(ZEXT816(0),auVar198,auVar95);
            auVar38._12_4_ = uVar97;
            auVar168 = a64_TBL(ZEXT816(0),auVar198,auVar38);
            auVar221 = NEON_ucvtf(auVar170,4);
            auVar236 = NEON_ucvtf(auVar207,4);
            auVar232 = NEON_ucvtf(auVar212,4);
            auVar172 = NEON_ucvtf(auVar172,4);
            auVar206 = NEON_ucvtf(auVar206,4);
            auVar211 = NEON_ucvtf(auVar211,4);
            auVar170 = NEON_ucvtf(auVar219,4);
            auVar207 = NEON_ucvtf(auVar234,4);
            auVar212 = NEON_ucvtf(in_q28,4);
            auVar219 = NEON_ucvtf(in_q29,4);
            in_q27 = NEON_ucvtf(auVar230,4);
            auVar168 = NEON_ucvtf(auVar168,4);
            in_q17._0_4_ = auVar170._0_4_ * 0.2126 + auVar207._0_4_ * 0.7152;
            in_q17._4_4_ = auVar170._4_4_ * 0.2126 + auVar207._4_4_ * 0.7152;
            in_q17._8_4_ = auVar170._8_4_ * 0.2126 + auVar207._8_4_ * 0.7152;
            in_q17._12_4_ = auVar170._12_4_ * 0.2126 + auVar207._12_4_ * 0.7152;
            in_q18._0_8_ = CONCAT44(auVar221._4_4_ * 0.2126 + auVar236._4_4_ * 0.7152 +
                                    auVar212._4_4_ * 0.0722,
                                    auVar221._0_4_ * 0.2126 + auVar236._0_4_ * 0.7152 +
                                    auVar212._0_4_ * 0.0722);
            in_q18._8_4_ = auVar221._8_4_ * 0.2126 + auVar236._8_4_ * 0.7152 +
                           auVar212._8_4_ * 0.0722;
            in_q18._12_4_ =
                 auVar221._12_4_ * 0.2126 + auVar236._12_4_ * 0.7152 + auVar212._12_4_ * 0.0722;
            auVar221._0_8_ =
                 CONCAT44(in_q17._4_4_ + auVar168._4_4_ * 0.0722,
                          in_q17._0_4_ + auVar168._0_4_ * 0.0722);
            auVar221._8_4_ = in_q17._8_4_ + auVar168._8_4_ * 0.0722;
            auVar221._12_4_ = in_q17._12_4_ + auVar168._12_4_ * 0.0722;
            *(float *)(puVar104 + 6) =
                 auVar232._8_4_ * 0.2126 + auVar172._8_4_ * 0.7152 + auVar219._8_4_ * 0.0722;
            *(float *)((long)puVar104 + 0x34) =
                 auVar232._12_4_ * 0.2126 + auVar172._12_4_ * 0.7152 + auVar219._12_4_ * 0.0722;
            *(float *)(puVar104 + 4) =
                 auVar232._0_4_ * 0.2126 + auVar172._0_4_ * 0.7152 + auVar219._0_4_ * 0.0722;
            *(float *)((long)puVar104 + 0x24) =
                 auVar232._4_4_ * 0.2126 + auVar172._4_4_ * 0.7152 + auVar219._4_4_ * 0.0722;
            puVar104[7] = in_q18._8_8_;
            puVar104[6] = in_q18._0_8_;
            puVar104[1] = auVar221._8_8_;
            *puVar104 = auVar221._0_8_;
            *(float *)(puVar104 + 4) =
                 auVar206._8_4_ * 0.2126 + auVar211._8_4_ * 0.7152 + in_q27._8_4_ * 0.0722;
            *(float *)((long)puVar104 + 0x24) =
                 auVar206._12_4_ * 0.2126 + auVar211._12_4_ * 0.7152 + in_q27._12_4_ * 0.0722;
            *(float *)(puVar104 + 2) =
                 auVar206._0_4_ * 0.2126 + auVar211._0_4_ * 0.7152 + in_q27._0_4_ * 0.0722;
            *(float *)((long)puVar104 + 0x14) =
                 auVar206._4_4_ * 0.2126 + auVar211._4_4_ * 0.7152 + in_q27._4_4_ * 0.0722;
            puVar104 = puVar104 + 8;
          } while (uVar130 != uVar123);
          if (8 < uVar130) goto LAB_0013b19c;
        }
      }
      lVar144 = lVar135 * 4 + lVar116 * 4;
      lVar124 = uVar126 - lVar135;
      pbVar121 = local_e0 + lVar135 * 4 + uVar139 + 2;
      do {
        pbVar1 = pbVar121 + -2;
        pbVar4 = pbVar121 + -1;
        lVar124 = lVar124 + -1;
        bVar163 = *pbVar121;
        pbVar121 = pbVar121 + 4;
        fVar151 = (float)NEON_ucvtf((uint)*pbVar1);
        fVar152 = (float)NEON_ucvtf((uint)*pbVar4);
        fVar155 = (float)NEON_ucvtf((uint)bVar163);
        *(float *)((long)puVar105 + lVar144) =
             fVar151 * 0.2126 + fVar152 * 0.7152 + fVar155 * 0.0722;
        uVar98 = _UNK_00119bec;
        uVar26 = _DAT_00119bd0;
        uVar97 = _UNK_00119bac;
        uVar108 = _DAT_00119b40;
        lVar144 = lVar144 + 4;
      } while (lVar124 != 0);
      if ((int)uVar100 < 1) {
LAB_0013a7e0:
        operator_delete(puVar105);
      }
      else {
        lVar135 = lVar116 * 4;
        uVar114 = uVar99 - 1;
        uVar139 = 0x10;
        if (((ulong)pvVar142 & 0xf) != 0) {
          uVar139 = (ulong)pvVar142 & 0xf;
        }
        lVar144 = uVar126 - uVar139;
        uVar130 = 8;
        if (((ulong)pvVar142 & 7) != 0) {
          uVar130 = (ulong)pvVar142 & 7;
        }
        auVar56._8_4_ = _UNK_00119ba8;
        auVar56._0_8_ = _DAT_00119ba0;
        auVar55._8_4_ = _UNK_00119ba8;
        auVar55._0_8_ = _DAT_00119ba0;
        auVar54._8_4_ = _UNK_00119ba8;
        auVar54._0_8_ = _DAT_00119ba0;
        auVar59._8_4_ = _UNK_00119ba8;
        auVar59._0_8_ = _DAT_00119ba0;
        auVar58._8_4_ = _UNK_00119ba8;
        auVar58._0_8_ = _DAT_00119ba0;
        auVar57._8_4_ = _UNK_00119ba8;
        auVar57._0_8_ = _DAT_00119ba0;
        auVar62._8_4_ = _UNK_00119ba8;
        auVar62._0_8_ = _DAT_00119ba0;
        auVar61._8_4_ = _UNK_00119ba8;
        auVar61._0_8_ = _DAT_00119ba0;
        auVar60._8_4_ = _UNK_00119ba8;
        auVar60._0_8_ = _DAT_00119ba0;
        auVar65._8_4_ = _UNK_00119ba8;
        auVar65._0_8_ = _DAT_00119ba0;
        auVar64._8_4_ = _UNK_00119ba8;
        auVar64._0_8_ = _DAT_00119ba0;
        auVar63._8_4_ = _UNK_00119ba8;
        auVar63._0_8_ = _DAT_00119ba0;
        auVar68._8_4_ = _UNK_00119be8;
        auVar68._0_8_ = _DAT_00119be0;
        auVar67._8_4_ = _UNK_00119be8;
        auVar67._0_8_ = _DAT_00119be0;
        auVar66._8_4_ = _UNK_00119be8;
        auVar66._0_8_ = _DAT_00119be0;
        auVar71._8_4_ = _UNK_00119be8;
        auVar71._0_8_ = _DAT_00119be0;
        auVar70._8_4_ = _UNK_00119be8;
        auVar70._0_8_ = _DAT_00119be0;
        auVar69._8_4_ = _UNK_00119be8;
        auVar69._0_8_ = _DAT_00119be0;
        auVar74._8_4_ = _UNK_00119be8;
        auVar74._0_8_ = _DAT_00119be0;
        auVar73._8_4_ = _UNK_00119be8;
        auVar73._0_8_ = _DAT_00119be0;
        auVar72._8_4_ = _UNK_00119be8;
        auVar72._0_8_ = _DAT_00119be0;
        auVar77._8_4_ = _UNK_00119be8;
        auVar77._0_8_ = _DAT_00119be0;
        auVar76._8_4_ = _UNK_00119be8;
        auVar76._0_8_ = _DAT_00119be0;
        auVar75._8_4_ = _UNK_00119be8;
        auVar75._0_8_ = _DAT_00119be0;
        uVar149 = (undefined4)_UNK_00119bd8;
        uVar150 = (undefined4)((ulong)_UNK_00119bd8 >> 0x20);
        uVar153 = (undefined4)_UNK_00119b48;
        uVar154 = (undefined4)((ulong)_UNK_00119b48 >> 0x20);
        uVar122 = 0;
        uVar123 = 2;
        uVar111 = 1;
        do {
          uVar119 = (uint)uVar122;
          uVar110 = uVar119 + 2;
          if ((int)uVar110 < (int)uVar100) {
            auVar16._8_8_ = 0;
            auVar16._0_8_ = uVar123;
            lVar124 = lVar135 * (uVar123 -
                                (uVar123 / 5 +
                                (SUB168(auVar16 * ZEXT816(0xcccccccccccccccd),8) &
                                0xfffffffffffffffc)));
            iVar141 = (int)uVar123;
            if ((uVar99 < 9) ||
               (((undefined *)
                 ((long)local_138 +
                 (ulong)(uVar110 -
                        (uVar110 / 5 + ((uint)((ulong)uVar110 * 0xcccccccd >> 0x20) & 0xfffffffc)))
                 * lVar116 * 4) < local_b0 + local_c0 * uVar110 + uVar120 + -1 &&
                (uVar131 = uVar122 + 2, auVar17._8_8_ = 0, auVar17._0_8_ = uVar131,
                local_b0 + local_c0 * uVar110 <
                (undefined *)
                ((long)local_138 +
                lVar135 * (uVar131 -
                          (uVar131 / 5 +
                          (SUB168(auVar17 * ZEXT816(0xcccccccccccccccd),8) & 0xfffffffffffffffc))) +
                uVar120))))) {
              lVar137 = 0;
            }
            else {
              if (uVar99 < 0x11) {
                lVar137 = 0;
              }
              else {
                puVar101 = local_b0 + local_c0 * iVar141;
                lVar137 = lVar144;
                puVar104 = (undefined8 *)((long)local_138 + lVar124);
                do {
                  auVar167[0] = *puVar101;
                  auVar169[0] = puVar101[1];
                  auVar171[0] = puVar101[2];
                  auVar167[1] = puVar101[4];
                  auVar169[1] = puVar101[5];
                  auVar171[1] = puVar101[6];
                  auVar167[2] = puVar101[8];
                  auVar169[2] = puVar101[9];
                  auVar171[2] = puVar101[10];
                  auVar167[3] = puVar101[0xc];
                  auVar169[3] = puVar101[0xd];
                  auVar171[3] = puVar101[0xe];
                  auVar167[4] = puVar101[0x10];
                  auVar169[4] = puVar101[0x11];
                  auVar171[4] = puVar101[0x12];
                  auVar167[5] = puVar101[0x14];
                  auVar169[5] = puVar101[0x15];
                  auVar171[5] = puVar101[0x16];
                  auVar167[6] = puVar101[0x18];
                  auVar169[6] = puVar101[0x19];
                  auVar171[6] = puVar101[0x1a];
                  auVar167[7] = puVar101[0x1c];
                  auVar169[7] = puVar101[0x1d];
                  auVar171[7] = puVar101[0x1e];
                  auVar167[8] = puVar101[0x20];
                  auVar169[8] = puVar101[0x21];
                  auVar171[8] = puVar101[0x22];
                  auVar167[9] = puVar101[0x24];
                  auVar169[9] = puVar101[0x25];
                  auVar171[9] = puVar101[0x26];
                  auVar167[10] = puVar101[0x28];
                  auVar169[10] = puVar101[0x29];
                  auVar171[10] = puVar101[0x2a];
                  auVar167[11] = puVar101[0x2c];
                  auVar169[11] = puVar101[0x2d];
                  auVar171[11] = puVar101[0x2e];
                  auVar167[12] = puVar101[0x30];
                  auVar169[12] = puVar101[0x31];
                  auVar171[12] = puVar101[0x32];
                  auVar167[13] = puVar101[0x34];
                  auVar169[13] = puVar101[0x35];
                  auVar171[13] = puVar101[0x36];
                  auVar167[14] = puVar101[0x38];
                  auVar169[14] = puVar101[0x39];
                  auVar171[14] = puVar101[0x3a];
                  auVar167[15] = puVar101[0x3c];
                  auVar169[15] = puVar101[0x3d];
                  auVar171[15] = puVar101[0x3e];
                  puVar101 = puVar101 + 0x40;
                  lVar137 = lVar137 + -0x10;
                  auVar30._8_4_ = uVar153;
                  auVar30._0_8_ = uVar108;
                  auVar30._12_4_ = uVar154;
                  auVar219 = a64_TBL(ZEXT816(0),auVar167,auVar30);
                  auVar31._8_4_ = uVar153;
                  auVar31._0_8_ = uVar108;
                  auVar31._12_4_ = uVar154;
                  auVar234 = a64_TBL(ZEXT816(0),auVar169,auVar31);
                  auVar23._8_4_ = uVar149;
                  auVar23._0_8_ = uVar26;
                  auVar23._12_4_ = uVar150;
                  auVar170 = a64_TBL(ZEXT816(0),auVar167,auVar23);
                  auVar24._8_4_ = uVar149;
                  auVar24._0_8_ = uVar26;
                  auVar24._12_4_ = uVar150;
                  auVar207 = a64_TBL(ZEXT816(0),auVar169,auVar24);
                  auVar75._12_4_ = uVar98;
                  auVar212 = a64_TBL(ZEXT816(0),auVar167,auVar75);
                  auVar76._12_4_ = uVar98;
                  auVar221 = a64_TBL(ZEXT816(0),auVar169,auVar76);
                  auVar63._12_4_ = uVar97;
                  auVar236 = a64_TBL(ZEXT816(0),auVar167,auVar63);
                  auVar64._12_4_ = uVar97;
                  auVar232 = a64_TBL(ZEXT816(0),auVar169,auVar64);
                  auVar32._8_4_ = uVar153;
                  auVar32._0_8_ = uVar108;
                  auVar32._12_4_ = uVar154;
                  auVar172 = a64_TBL(ZEXT816(0),auVar171,auVar32);
                  auVar25._8_4_ = uVar149;
                  auVar25._0_8_ = uVar26;
                  auVar25._12_4_ = uVar150;
                  auVar206 = a64_TBL(ZEXT816(0),auVar171,auVar25);
                  auVar77._12_4_ = uVar98;
                  auVar211 = a64_TBL(ZEXT816(0),auVar171,auVar77);
                  auVar65._12_4_ = uVar97;
                  auVar168 = a64_TBL(ZEXT816(0),auVar171,auVar65);
                  auVar219 = NEON_ucvtf(auVar219,4);
                  auVar234 = NEON_ucvtf(auVar234,4);
                  auVar170 = NEON_ucvtf(auVar170,4);
                  auVar207 = NEON_ucvtf(auVar207,4);
                  auVar212 = NEON_ucvtf(auVar212,4);
                  auVar221 = NEON_ucvtf(auVar221,4);
                  auVar236 = NEON_ucvtf(auVar236,4);
                  auVar232 = NEON_ucvtf(auVar232,4);
                  auVar172 = NEON_ucvtf(auVar172,4);
                  auVar206 = NEON_ucvtf(auVar206,4);
                  auVar211 = NEON_ucvtf(auVar211,4);
                  auVar168 = NEON_ucvtf(auVar168,4);
                  in_q29._0_4_ = auVar211._0_4_ * 0.0722;
                  in_q29._4_4_ = auVar211._4_4_ * 0.0722;
                  in_q29._8_4_ = auVar211._8_4_ * 0.0722;
                  in_q29._12_4_ = auVar211._12_4_ * 0.0722;
                  in_q27._0_8_ = CONCAT44(auVar170._4_4_ * 0.2126 + auVar207._4_4_ * 0.7152 +
                                          auVar206._4_4_ * 0.0722,
                                          auVar170._0_4_ * 0.2126 + auVar207._0_4_ * 0.7152 +
                                          auVar206._0_4_ * 0.0722);
                  in_q27._8_4_ = auVar170._8_4_ * 0.2126 + auVar207._8_4_ * 0.7152 +
                                 auVar206._8_4_ * 0.0722;
                  in_q27._12_4_ =
                       auVar170._12_4_ * 0.2126 + auVar207._12_4_ * 0.7152 +
                       auVar206._12_4_ * 0.0722;
                  in_q28._0_8_ = CONCAT44(auVar212._4_4_ * 0.2126 + auVar221._4_4_ * 0.7152 +
                                          in_q29._4_4_,
                                          auVar212._0_4_ * 0.2126 + auVar221._0_4_ * 0.7152 +
                                          in_q29._0_4_);
                  in_q28._8_4_ = auVar212._8_4_ * 0.2126 + auVar221._8_4_ * 0.7152 + in_q29._8_4_;
                  in_q28._12_4_ =
                       auVar212._12_4_ * 0.2126 + auVar221._12_4_ * 0.7152 + in_q29._12_4_;
                  puVar104[5] = in_q27._8_8_;
                  puVar104[4] = in_q27._0_8_;
                  *(float *)(puVar104 + 8) =
                       auVar219._8_4_ * 0.2126 + auVar234._8_4_ * 0.7152 + auVar172._8_4_ * 0.0722;
                  *(float *)((long)puVar104 + 0x44) =
                       auVar219._12_4_ * 0.2126 + auVar234._12_4_ * 0.7152 +
                       auVar172._12_4_ * 0.0722;
                  *(float *)(puVar104 + 6) =
                       auVar219._0_4_ * 0.2126 + auVar234._0_4_ * 0.7152 + auVar172._0_4_ * 0.0722;
                  *(float *)((long)puVar104 + 0x34) =
                       auVar219._4_4_ * 0.2126 + auVar234._4_4_ * 0.7152 + auVar172._4_4_ * 0.0722;
                  *(float *)(puVar104 + 2) =
                       auVar236._8_4_ * 0.2126 + auVar232._8_4_ * 0.7152 + auVar168._8_4_ * 0.0722;
                  *(float *)((long)puVar104 + 0x14) =
                       auVar236._12_4_ * 0.2126 + auVar232._12_4_ * 0.7152 +
                       auVar168._12_4_ * 0.0722;
                  *(float *)puVar104 =
                       auVar236._0_4_ * 0.2126 + auVar232._0_4_ * 0.7152 + auVar168._0_4_ * 0.0722;
                  *(float *)((long)puVar104 + 4) =
                       auVar236._4_4_ * 0.2126 + auVar232._4_4_ * 0.7152 + auVar168._4_4_ * 0.0722;
                  puVar104[3] = in_q28._8_8_;
                  puVar104[2] = in_q28._0_8_;
                  puVar104 = puVar104 + 8;
                } while (lVar137 != 0);
                lVar137 = lVar144;
                if (uVar139 < 9) goto LAB_00139cdc;
              }
              puVar101 = local_b0 + (ulong)(local_c0 * iVar141) + lVar137 * 4;
              lVar127 = (uVar130 - uVar126) + lVar137;
              pfVar118 = (float *)((long)local_138 + lVar124 + lVar137 * 4);
              do {
                auVar217[0] = *puVar101;
                auVar223[0] = puVar101[1];
                auVar228[0] = puVar101[2];
                auVar217[1] = puVar101[4];
                auVar223[1] = puVar101[5];
                auVar228[1] = puVar101[6];
                auVar217[2] = puVar101[8];
                auVar223[2] = puVar101[9];
                auVar228[2] = puVar101[10];
                auVar217[3] = puVar101[0xc];
                auVar223[3] = puVar101[0xd];
                auVar228[3] = puVar101[0xe];
                auVar217[4] = puVar101[0x10];
                auVar223[4] = puVar101[0x11];
                auVar228[4] = puVar101[0x12];
                auVar217[5] = puVar101[0x14];
                auVar223[5] = puVar101[0x15];
                auVar228[5] = puVar101[0x16];
                auVar217[6] = puVar101[0x18];
                auVar223[6] = puVar101[0x19];
                auVar228[6] = puVar101[0x1a];
                auVar217._8_8_ = in_q27._8_8_;
                auVar217[7] = puVar101[0x1c];
                auVar223._8_8_ = in_q28._8_8_;
                auVar223[7] = puVar101[0x1d];
                auVar228._8_8_ = in_q29._8_8_;
                auVar228[7] = puVar101[0x1e];
                puVar101 = puVar101 + 0x20;
                lVar127 = lVar127 + 8;
                auVar72._12_4_ = uVar98;
                auVar207 = a64_TBL(ZEXT816(0),auVar217,auVar72);
                auVar73._12_4_ = uVar98;
                auVar212 = a64_TBL(ZEXT816(0),auVar223,auVar73);
                auVar60._12_4_ = uVar97;
                auVar236 = a64_TBL(ZEXT816(0),auVar217,auVar60);
                auVar61._12_4_ = uVar97;
                auVar168 = a64_TBL(ZEXT816(0),auVar223,auVar61);
                auVar74._12_4_ = uVar98;
                auVar170 = a64_TBL(ZEXT816(0),auVar228,auVar74);
                auVar62._12_4_ = uVar97;
                auVar221 = a64_TBL(ZEXT816(0),auVar228,auVar62);
                auVar207 = NEON_ucvtf(auVar207,4);
                auVar212 = NEON_ucvtf(auVar212,4);
                auVar236 = NEON_ucvtf(auVar236,4);
                auVar232 = NEON_ucvtf(auVar168,4);
                auVar170 = NEON_ucvtf(auVar170,4);
                auVar168 = NEON_ucvtf(auVar221,4);
                in_q28._0_4_ = auVar236._0_4_ * 0.2126;
                in_q28._4_4_ = auVar236._4_4_ * 0.2126;
                in_q28._8_4_ = auVar236._8_4_ * 0.2126;
                in_q28._12_4_ = auVar236._12_4_ * 0.2126;
                in_q29._0_4_ = auVar232._0_4_ * 0.7152;
                in_q29._4_4_ = auVar232._4_4_ * 0.7152;
                in_q29._8_4_ = auVar232._8_4_ * 0.7152;
                in_q29._12_4_ = auVar232._12_4_ * 0.7152;
                in_q27._0_4_ = in_q28._0_4_ + in_q29._0_4_;
                in_q27._4_4_ = in_q28._4_4_ + in_q29._4_4_;
                in_q27._8_4_ = in_q28._8_4_ + in_q29._8_4_;
                in_q27._12_4_ = in_q28._12_4_ + in_q29._12_4_;
                pfVar118[4] = in_q27._8_4_ + auVar168._8_4_ * 0.0722;
                pfVar118[5] = in_q27._12_4_ + auVar168._12_4_ * 0.0722;
                *pfVar118 = in_q27._0_4_ + auVar168._0_4_ * 0.0722;
                pfVar118[1] = in_q27._4_4_ + auVar168._4_4_ * 0.0722;
                pfVar118[8] = auVar207._8_4_ * 0.2126 + auVar212._8_4_ * 0.7152 +
                              auVar170._8_4_ * 0.0722;
                pfVar118[9] = auVar207._12_4_ * 0.2126 + auVar212._12_4_ * 0.7152 +
                              auVar170._12_4_ * 0.0722;
                pfVar118[4] = auVar207._0_4_ * 0.2126 + auVar212._0_4_ * 0.7152 +
                              auVar170._0_4_ * 0.0722;
                pfVar118[5] = auVar207._4_4_ * 0.2126 + auVar212._4_4_ * 0.7152 +
                              auVar170._4_4_ * 0.0722;
                lVar137 = uVar126 - uVar130;
                pfVar118 = pfVar118 + 8;
              } while (lVar127 != 0);
            }
LAB_00139cdc:
            lVar127 = uVar126 - lVar137;
            pbVar121 = local_b0 + (ulong)(local_c0 * iVar141) + lVar137 * 4 + 1;
            pfVar118 = (float *)((long)local_138 + lVar124 + lVar137 * 4);
            do {
              in_q29 = ZEXT416(0x3f371759);
              pbVar1 = pbVar121 + 1;
              lVar127 = lVar127 + -1;
              fVar151 = (float)NEON_ucvtf((uint)pbVar121[-1]);
              fVar152 = (float)NEON_ucvtf((uint)*pbVar121);
              pbVar121 = pbVar121 + 4;
              fVar155 = (float)NEON_ucvtf((uint)*pbVar1);
              in_q27 = ZEXT416((uint)fVar155);
              in_q28 = ZEXT416(0x3d93dd98);
              *pfVar118 = fVar151 * 0.2126 + fVar152 * 0.7152 + fVar155 * 0.0722;
              pfVar118 = pfVar118 + 1;
            } while (lVar127 != 0);
          }
          uVar122 = uVar122 + 1;
          uVar110 = (uint)uVar122;
          if ((int)uVar110 < (int)uVar100) {
            auVar18._8_8_ = 0;
            auVar18._0_8_ = uVar111;
            lVar124 = lVar135 * (uVar111 -
                                (uVar111 / 3 +
                                (SUB168(auVar18 * ZEXT816(0xaaaaaaaaaaaaaaab),8) &
                                0xfffffffffffffffe)));
            iVar141 = (int)uVar111;
            if ((uVar99 < 9) ||
               (((undefined *)
                 ((long)puVar105 +
                 (ulong)(uVar110 -
                        ((int)((uVar122 & 0xffffffff) / 3) +
                        ((uint)((uVar122 & 0xffffffff) * 0xaaaaaaab >> 0x20) & 0xfffffffe))) *
                 lVar116 * 4) < local_e0 + local_f0 * uVar110 + uVar120 + -1 &&
                (auVar19._8_8_ = 0, auVar19._0_8_ = uVar122,
                local_e0 + local_f0 * uVar110 <
                (undefined *)
                ((long)puVar105 +
                lVar135 * (uVar122 -
                          (uVar122 / 3 +
                          (SUB168(auVar19 * ZEXT816(0xaaaaaaaaaaaaaaab),8) & 0xfffffffffffffffe))) +
                uVar120))))) {
              lVar137 = 0;
            }
            else {
              if (uVar99 < 0x11) {
                lVar137 = 0;
              }
              else {
                puVar101 = local_e0 + local_f0 * iVar141;
                puVar104 = (undefined8 *)((long)puVar105 + lVar124);
                lVar137 = lVar144;
                do {
                  auVar218[0] = *puVar101;
                  auVar224[0] = puVar101[1];
                  auVar229[0] = puVar101[2];
                  auVar218[1] = puVar101[4];
                  auVar224[1] = puVar101[5];
                  auVar229[1] = puVar101[6];
                  auVar218[2] = puVar101[8];
                  auVar224[2] = puVar101[9];
                  auVar229[2] = puVar101[10];
                  auVar218[3] = puVar101[0xc];
                  auVar224[3] = puVar101[0xd];
                  auVar229[3] = puVar101[0xe];
                  auVar218[4] = puVar101[0x10];
                  auVar224[4] = puVar101[0x11];
                  auVar229[4] = puVar101[0x12];
                  auVar218[5] = puVar101[0x14];
                  auVar224[5] = puVar101[0x15];
                  auVar229[5] = puVar101[0x16];
                  auVar218[6] = puVar101[0x18];
                  auVar224[6] = puVar101[0x19];
                  auVar229[6] = puVar101[0x1a];
                  auVar218[7] = puVar101[0x1c];
                  auVar224[7] = puVar101[0x1d];
                  auVar229[7] = puVar101[0x1e];
                  auVar218[8] = puVar101[0x20];
                  auVar224[8] = puVar101[0x21];
                  auVar229[8] = puVar101[0x22];
                  auVar218[9] = puVar101[0x24];
                  auVar224[9] = puVar101[0x25];
                  auVar229[9] = puVar101[0x26];
                  auVar218[10] = puVar101[0x28];
                  auVar224[10] = puVar101[0x29];
                  auVar229[10] = puVar101[0x2a];
                  auVar218[11] = puVar101[0x2c];
                  auVar224[11] = puVar101[0x2d];
                  auVar229[11] = puVar101[0x2e];
                  auVar218[12] = puVar101[0x30];
                  auVar224[12] = puVar101[0x31];
                  auVar229[12] = puVar101[0x32];
                  auVar218[13] = puVar101[0x34];
                  auVar224[13] = puVar101[0x35];
                  auVar229[13] = puVar101[0x36];
                  auVar218[14] = puVar101[0x38];
                  auVar224[14] = puVar101[0x39];
                  auVar229[14] = puVar101[0x3a];
                  auVar218[15] = puVar101[0x3c];
                  auVar224[15] = puVar101[0x3d];
                  auVar229[15] = puVar101[0x3e];
                  puVar101 = puVar101 + 0x40;
                  lVar137 = lVar137 + -0x10;
                  auVar27._8_4_ = uVar153;
                  auVar27._0_8_ = uVar108;
                  auVar27._12_4_ = uVar154;
                  auVar206 = a64_TBL(ZEXT816(0),auVar218,auVar27);
                  auVar28._8_4_ = uVar153;
                  auVar28._0_8_ = uVar108;
                  auVar28._12_4_ = uVar154;
                  auVar211 = a64_TBL(ZEXT816(0),auVar224,auVar28);
                  auVar20._8_4_ = uVar149;
                  auVar20._0_8_ = uVar26;
                  auVar20._12_4_ = uVar150;
                  auVar234 = a64_TBL(ZEXT816(0),auVar218,auVar20);
                  auVar21._8_4_ = uVar149;
                  auVar21._0_8_ = uVar26;
                  auVar21._12_4_ = uVar150;
                  auVar168 = a64_TBL(ZEXT816(0),auVar224,auVar21);
                  auVar69._12_4_ = uVar98;
                  auVar170 = a64_TBL(ZEXT816(0),auVar218,auVar69);
                  auVar70._12_4_ = uVar98;
                  auVar207 = a64_TBL(ZEXT816(0),auVar224,auVar70);
                  auVar57._12_4_ = uVar97;
                  auVar212 = a64_TBL(ZEXT816(0),auVar218,auVar57);
                  auVar58._12_4_ = uVar97;
                  auVar221 = a64_TBL(ZEXT816(0),auVar224,auVar58);
                  auVar29._8_4_ = uVar153;
                  auVar29._0_8_ = uVar108;
                  auVar29._12_4_ = uVar154;
                  auVar236 = a64_TBL(ZEXT816(0),auVar229,auVar29);
                  auVar22._8_4_ = uVar149;
                  auVar22._0_8_ = uVar26;
                  auVar22._12_4_ = uVar150;
                  auVar232 = a64_TBL(ZEXT816(0),auVar229,auVar22);
                  auVar71._12_4_ = uVar98;
                  auVar172 = a64_TBL(ZEXT816(0),auVar229,auVar71);
                  auVar59._12_4_ = uVar97;
                  auVar219 = a64_TBL(ZEXT816(0),auVar229,auVar59);
                  auVar206 = NEON_ucvtf(auVar206,4);
                  auVar211 = NEON_ucvtf(auVar211,4);
                  auVar235 = NEON_ucvtf(auVar234,4);
                  auVar168 = NEON_ucvtf(auVar168,4);
                  auVar170 = NEON_ucvtf(auVar170,4);
                  auVar207 = NEON_ucvtf(auVar207,4);
                  auVar234 = NEON_ucvtf(auVar212,4);
                  auVar230 = NEON_ucvtf(auVar221,4);
                  auVar233 = NEON_ucvtf(auVar236,4);
                  auVar212 = NEON_ucvtf(auVar232,4);
                  auVar221 = NEON_ucvtf(auVar172,4);
                  auVar236 = NEON_ucvtf(auVar219,4);
                  in_q28._0_4_ = auVar234._0_4_ * 0.2126 + auVar230._0_4_ * 0.7152;
                  in_q28._4_4_ = auVar234._4_4_ * 0.2126 + auVar230._4_4_ * 0.7152;
                  in_q28._8_4_ = auVar234._8_4_ * 0.2126 + auVar230._8_4_ * 0.7152;
                  in_q28._12_4_ = auVar234._12_4_ * 0.2126 + auVar230._12_4_ * 0.7152;
                  in_q29._0_8_ = CONCAT44(auVar170._4_4_ * 0.2126 + auVar207._4_4_ * 0.7152 +
                                          auVar221._4_4_ * 0.0722,
                                          auVar170._0_4_ * 0.2126 + auVar207._0_4_ * 0.7152 +
                                          auVar221._0_4_ * 0.0722);
                  in_q29._8_4_ = auVar170._8_4_ * 0.2126 + auVar207._8_4_ * 0.7152 +
                                 auVar221._8_4_ * 0.0722;
                  in_q29._12_4_ =
                       auVar170._12_4_ * 0.2126 + auVar207._12_4_ * 0.7152 +
                       auVar221._12_4_ * 0.0722;
                  in_q27._0_8_ = CONCAT44(in_q28._4_4_ + auVar236._4_4_ * 0.0722,
                                          in_q28._0_4_ + auVar236._0_4_ * 0.0722);
                  in_q27._8_4_ = in_q28._8_4_ + auVar236._8_4_ * 0.0722;
                  in_q27._12_4_ = in_q28._12_4_ + auVar236._12_4_ * 0.0722;
                  *(float *)(puVar104 + 6) =
                       auVar235._8_4_ * 0.2126 + auVar168._8_4_ * 0.7152 + auVar212._8_4_ * 0.0722;
                  *(float *)((long)puVar104 + 0x34) =
                       auVar235._12_4_ * 0.2126 + auVar168._12_4_ * 0.7152 +
                       auVar212._12_4_ * 0.0722;
                  *(float *)(puVar104 + 4) =
                       auVar235._0_4_ * 0.2126 + auVar168._0_4_ * 0.7152 + auVar212._0_4_ * 0.0722;
                  *(float *)((long)puVar104 + 0x24) =
                       auVar235._4_4_ * 0.2126 + auVar168._4_4_ * 0.7152 + auVar212._4_4_ * 0.0722;
                  *(float *)(puVar104 + 8) =
                       auVar206._8_4_ * 0.2126 + auVar211._8_4_ * 0.7152 + auVar233._8_4_ * 0.0722;
                  *(float *)((long)puVar104 + 0x44) =
                       auVar206._12_4_ * 0.2126 + auVar211._12_4_ * 0.7152 +
                       auVar233._12_4_ * 0.0722;
                  *(float *)(puVar104 + 6) =
                       auVar206._0_4_ * 0.2126 + auVar211._0_4_ * 0.7152 + auVar233._0_4_ * 0.0722;
                  *(float *)((long)puVar104 + 0x34) =
                       auVar206._4_4_ * 0.2126 + auVar211._4_4_ * 0.7152 + auVar233._4_4_ * 0.0722;
                  puVar104[1] = in_q27._8_8_;
                  *puVar104 = in_q27._0_8_;
                  puVar104[3] = in_q29._8_8_;
                  puVar104[2] = in_q29._0_8_;
                  puVar104 = puVar104 + 8;
                } while (lVar137 != 0);
                lVar137 = lVar144;
                if (uVar139 < 9) goto LAB_00139df8;
              }
              puVar101 = local_e0 + (ulong)(local_f0 * iVar141) + lVar137 * 4;
              lVar127 = (uVar130 - uVar126) + lVar137;
              pfVar118 = (float *)((long)puVar105 + lVar124 + lVar137 * 4);
              do {
                auVar220[0] = *puVar101;
                auVar225[0] = puVar101[1];
                auVar231[0] = puVar101[2];
                auVar220[1] = puVar101[4];
                auVar225[1] = puVar101[5];
                auVar231[1] = puVar101[6];
                auVar220[2] = puVar101[8];
                auVar225[2] = puVar101[9];
                auVar231[2] = puVar101[10];
                auVar220[3] = puVar101[0xc];
                auVar225[3] = puVar101[0xd];
                auVar231[3] = puVar101[0xe];
                auVar220[4] = puVar101[0x10];
                auVar225[4] = puVar101[0x11];
                auVar231[4] = puVar101[0x12];
                auVar220[5] = puVar101[0x14];
                auVar225[5] = puVar101[0x15];
                auVar231[5] = puVar101[0x16];
                auVar220[6] = puVar101[0x18];
                auVar225[6] = puVar101[0x19];
                auVar231[6] = puVar101[0x1a];
                auVar220._8_8_ = in_q27._8_8_;
                auVar220[7] = puVar101[0x1c];
                auVar225._8_8_ = in_q28._8_8_;
                auVar225[7] = puVar101[0x1d];
                auVar231._8_8_ = in_q29._8_8_;
                auVar231[7] = puVar101[0x1e];
                puVar101 = puVar101 + 0x20;
                lVar127 = lVar127 + 8;
                auVar66._12_4_ = uVar98;
                auVar207 = a64_TBL(ZEXT816(0),auVar220,auVar66);
                auVar67._12_4_ = uVar98;
                auVar212 = a64_TBL(ZEXT816(0),auVar225,auVar67);
                auVar54._12_4_ = uVar97;
                auVar236 = a64_TBL(ZEXT816(0),auVar220,auVar54);
                auVar55._12_4_ = uVar97;
                auVar168 = a64_TBL(ZEXT816(0),auVar225,auVar55);
                auVar68._12_4_ = uVar98;
                auVar170 = a64_TBL(ZEXT816(0),auVar231,auVar68);
                auVar56._12_4_ = uVar97;
                auVar221 = a64_TBL(ZEXT816(0),auVar231,auVar56);
                auVar207 = NEON_ucvtf(auVar207,4);
                auVar212 = NEON_ucvtf(auVar212,4);
                auVar236 = NEON_ucvtf(auVar236,4);
                auVar232 = NEON_ucvtf(auVar168,4);
                auVar170 = NEON_ucvtf(auVar170,4);
                auVar168 = NEON_ucvtf(auVar221,4);
                in_q28._0_4_ = auVar236._0_4_ * 0.2126;
                in_q28._4_4_ = auVar236._4_4_ * 0.2126;
                in_q28._8_4_ = auVar236._8_4_ * 0.2126;
                in_q28._12_4_ = auVar236._12_4_ * 0.2126;
                in_q29._0_4_ = auVar232._0_4_ * 0.7152;
                in_q29._4_4_ = auVar232._4_4_ * 0.7152;
                in_q29._8_4_ = auVar232._8_4_ * 0.7152;
                in_q29._12_4_ = auVar232._12_4_ * 0.7152;
                in_q27._0_4_ = in_q28._0_4_ + in_q29._0_4_;
                in_q27._4_4_ = in_q28._4_4_ + in_q29._4_4_;
                in_q27._8_4_ = in_q28._8_4_ + in_q29._8_4_;
                in_q27._12_4_ = in_q28._12_4_ + in_q29._12_4_;
                pfVar118[4] = in_q27._8_4_ + auVar168._8_4_ * 0.0722;
                pfVar118[5] = in_q27._12_4_ + auVar168._12_4_ * 0.0722;
                *pfVar118 = in_q27._0_4_ + auVar168._0_4_ * 0.0722;
                pfVar118[1] = in_q27._4_4_ + auVar168._4_4_ * 0.0722;
                pfVar118[8] = auVar207._8_4_ * 0.2126 + auVar212._8_4_ * 0.7152 +
                              auVar170._8_4_ * 0.0722;
                pfVar118[9] = auVar207._12_4_ * 0.2126 + auVar212._12_4_ * 0.7152 +
                              auVar170._12_4_ * 0.0722;
                pfVar118[4] = auVar207._0_4_ * 0.2126 + auVar212._0_4_ * 0.7152 +
                              auVar170._0_4_ * 0.0722;
                pfVar118[5] = auVar207._4_4_ * 0.2126 + auVar212._4_4_ * 0.7152 +
                              auVar170._4_4_ * 0.0722;
                lVar137 = uVar126 - uVar130;
                pfVar118 = pfVar118 + 8;
              } while (lVar127 != 0);
            }
LAB_00139df8:
            lVar127 = uVar126 - lVar137;
            pbVar121 = local_e0 + (ulong)(local_f0 * iVar141) + lVar137 * 4 + 1;
            pfVar118 = (float *)((long)puVar105 + lVar124 + lVar137 * 4);
            do {
              in_q29 = ZEXT416(0x3f371759);
              pbVar1 = pbVar121 + 1;
              lVar127 = lVar127 + -1;
              fVar151 = (float)NEON_ucvtf((uint)pbVar121[-1]);
              fVar152 = (float)NEON_ucvtf((uint)*pbVar121);
              pbVar121 = pbVar121 + 4;
              fVar155 = (float)NEON_ucvtf((uint)*pbVar1);
              in_q27 = ZEXT416((uint)fVar155);
              in_q28 = ZEXT416(0x3d93dd98);
              *pfVar118 = fVar151 * 0.2126 + fVar152 * 0.7152 + fVar155 * 0.0722;
              pfVar118 = pfVar118 + 1;
            } while (lVar127 != 0);
          }
          if (0 < (int)uVar99) {
            uVar131 = 0;
            uVar112 = uVar12;
            if ((int)uVar119 <= (int)uVar12) {
              uVar112 = uVar119;
            }
            uVar112 = uVar112 & ((int)uVar112 >> 0x1f ^ 0xffffffffU);
            uVar5 = uVar12;
            if ((int)(uVar119 - 1) <= (int)uVar12) {
              uVar5 = uVar119 - 1;
            }
            uVar5 = uVar5 & ((int)uVar5 >> 0x1f ^ 0xffffffffU);
            lVar124 = (ulong)(uVar112 + (uint)((ulong)uVar112 * 0x66666667 >> 0x21) * -5) * lVar116;
            lVar137 = (ulong)(uVar112 + (int)((ulong)uVar112 * 0x55555556 >> 0x20) * -3) * lVar116;
            uVar112 = uVar12;
            if ((int)uVar110 <= (int)uVar12) {
              uVar112 = uVar110;
            }
            lVar127 = (ulong)(uVar5 + (uint)((ulong)uVar5 * 0x66666667 >> 0x21) * -5) * lVar116;
            uVar112 = uVar112 & ((int)uVar112 >> 0x1f ^ 0xffffffffU);
            uVar6 = uVar12;
            if ((int)(uVar119 - 2) <= (int)uVar12) {
              uVar6 = uVar119 - 2;
            }
            uVar6 = uVar6 & ((int)uVar6 >> 0x1f ^ 0xffffffffU);
            lVar109 = (ulong)(uVar5 + (int)((ulong)uVar5 * 0x55555556 >> 0x20) * -3) * lVar116;
            uVar5 = uVar12;
            if ((int)(uVar119 + 2) <= (int)uVar12) {
              uVar5 = uVar119 + 2;
            }
            uVar5 = uVar5 & ((int)uVar5 >> 0x1f ^ 0xffffffffU);
            lVar129 = (ulong)(uVar112 + (uint)((ulong)uVar112 * 0x66666667 >> 0x21) * -5) * lVar116;
            lVar140 = (ulong)(uVar112 + (int)((ulong)uVar112 * 0x55555556 >> 0x20) * -3) * lVar116;
            lVar143 = (ulong)(uVar6 + (uint)((ulong)uVar6 * 0x66666667 >> 0x21) * -5) * lVar116;
            lVar125 = (ulong)(uVar5 + (uint)((ulong)uVar5 * 0x66666667 >> 0x21) * -5) * lVar116;
            uVar112 = 0;
            do {
              uVar5 = uVar114;
              if ((int)(uVar112 - 1) <= (int)uVar114) {
                uVar5 = uVar112 - 1;
              }
              uVar147 = (ulong)(uVar5 & ((int)uVar5 >> 0x1f ^ 0xffffffffU));
              uVar5 = uVar114;
              if ((int)uVar112 <= (int)uVar114) {
                uVar5 = uVar112;
              }
              uVar132 = (ulong)(uVar5 & ((int)uVar5 >> 0x1f ^ 0xffffffffU));
              uVar5 = uVar114;
              if ((int)(uVar112 + 1) <= (int)uVar114) {
                uVar5 = uVar112 + 1;
              }
              lVar14 = uVar147 * 4;
              uVar145 = (ulong)(uVar5 & ((int)uVar5 >> 0x1f ^ 0xffffffffU));
              lVar15 = uVar132 * 4;
              lVar113 = uVar145 * 4;
              fVar152 = *(float *)((long)local_138 + lVar15 + lVar124 * 4);
              fVar151 = *(float *)((long)local_138 + lVar113 + lVar129 * 4);
              in_q27 = ZEXT416((uint)fVar151);
              fVar151 = *(float *)((long)local_138 + lVar14 + lVar127 * 4) * 0.0625 + 0.0 +
                        *(float *)((long)local_138 + lVar15 + lVar127 * 4) * 0.125 +
                        *(float *)((long)local_138 + lVar113 + lVar127 * 4) * 0.0625 +
                        *(float *)((long)local_138 + lVar14 + lVar124 * 4) * 0.125 + fVar152 * 0.25
                        + *(float *)((long)local_138 + lVar113 + lVar124 * 4) * 0.125 +
                        *(float *)((long)local_138 + lVar14 + lVar129 * 4) * 0.0625 +
                        *(float *)((long)local_138 + lVar15 + lVar129 * 4) * 0.125 +
                        fVar151 * 0.0625;
              if (fVar148 * 0.8 + 0.75 < ABS(fVar152 - fVar151)) {
                fVar155 = *(float *)((long)puVar105 + lVar15 + lVar137 * 4);
                fVar158 = *(float *)((long)puVar105 + lVar14 + lVar109 * 4) * 0.0625 + 0.0 +
                          *(float *)((long)puVar105 + lVar15 + lVar109 * 4) * 0.125 +
                          *(float *)((long)puVar105 + lVar113 + lVar109 * 4) * 0.0625 +
                          *(float *)((long)puVar105 + lVar14 + lVar137 * 4) * 0.125 + fVar155 * 0.25
                          + *(float *)((long)puVar105 + lVar113 + lVar137 * 4) * 0.125 +
                          *(float *)((long)puVar105 + lVar14 + lVar140 * 4) * 0.0625 +
                          *(float *)((long)puVar105 + lVar15 + lVar140 * 4) * 0.125 +
                          *(float *)((long)puVar105 + lVar113 + lVar140 * 4) * 0.0625;
                fVar156 = fVar151 * (255.0 - fVar151);
                fVar157 = fVar158 * (255.0 - fVar158);
                in_q28 = ZEXT416((uint)fVar157);
                if (fVar156 <= 64.0) {
                  fVar156 = 64.0;
                }
                fVar155 = fVar155 - fVar158;
                fVar156 = (float)NEON_fminnm(fVar157 / fVar156,0x3fc00000);
                if (fVar156 <= 0.5) {
                  fVar156 = 0.5;
                }
                fVar156 = fVar156 * (fVar152 - fVar151);
                in_q27 = ZEXT416((uint)(fVar156 * fVar155));
                if (ABS(fVar155) + 0.5 < ABS(fVar156) && -0.25 <= fVar156 * fVar155) {
                  lVar133 = uVar132 * 4;
                  lVar134 = uVar147 * 4;
                  lVar113 = uVar145 * 4;
                  fVar161 = *(float *)((long)local_138 + lVar134 + lVar124 * 4);
                  fVar157 = *(float *)((long)local_138 + lVar113 + lVar127 * 4);
                  fVar226 = *(float *)((long)local_138 + lVar134 + lVar127 * 4);
                  fVar209 = fVar161 - *(float *)((long)local_138 + lVar134 + lVar143 * 4);
                  fVar160 = *(float *)((long)local_138 + lVar113 + lVar124 * 4);
                  uVar205 = NEON_smin(CONCAT44(uVar114,uVar114),
                                      CONCAT44(uVar112 + (int)((ulong)DAT_00119af8 >> 0x20),
                                               uVar112 + (int)DAT_00119af8),4);
                  fVar222 = fVar152 - *(float *)((long)local_138 + lVar133 + lVar143 * 4);
                  fVar162 = fVar157 - fVar226;
                  fVar165 = fVar160 - *(float *)((long)local_138 + lVar113 + lVar143 * 4);
                  fVar164 = *(float *)((long)local_138 + lVar134 + lVar129 * 4);
                  fVar226 = fVar164 - fVar226;
                  uVar147 = NEON_smax(uVar205,0,4);
                  lVar14 = (uVar147 & 0xffffffff) * 4;
                  fVar204 = *(float *)((long)local_138 + lVar133 + lVar127 * 4);
                  fVar216 = fVar204 - *(float *)((long)local_138 + lVar14 + lVar127 * 4);
                  lVar15 = (uVar147 >> 0x20) * 4;
                  fVar151 = *(float *)((long)local_138 + lVar15 + lVar127 * 4) - fVar204;
                  fVar210 = fVar152 - *(float *)((long)local_138 + lVar14 + lVar124 * 4);
                  fVar159 = *(float *)((long)local_138 + lVar133 + lVar129 * 4);
                  fVar166 = fVar160 - fVar161;
                  fVar204 = fVar159 - fVar204;
                  fVar213 = *(float *)((long)local_138 + lVar113 + lVar129 * 4);
                  fVar227 = *(float *)((long)local_138 + lVar134 + lVar125 * 4);
                  in_q29 = ZEXT416((uint)fVar227);
                  fVar157 = fVar213 - fVar157;
                  fVar152 = *(float *)((long)local_138 + lVar15 + lVar124 * 4) - fVar152;
                  fVar227 = fVar227 - fVar161;
                  fVar213 = fVar213 - fVar164;
                  fVar173 = fVar159 - *(float *)((long)local_138 + lVar14 + lVar129 * 4);
                  fVar164 = *(float *)((long)local_138 + lVar133 + lVar125 * 4) -
                            *(float *)((long)local_138 + lVar133 + lVar124 * 4);
                  in_q27 = ZEXT416((uint)(fVar227 * fVar227));
                  fVar160 = *(float *)((long)local_138 + lVar113 + lVar125 * 4) - fVar160;
                  in_q28 = ZEXT416((uint)(fVar213 * fVar213));
                  fVar159 = *(float *)((long)local_138 + lVar15 + lVar129 * 4) - fVar159;
                  fVar201 = fVar209 * fVar209 + fVar222 * fVar222 + fVar165 * fVar165 +
                            fVar226 * fVar226 + fVar204 * fVar204 + fVar157 * fVar157 +
                            fVar227 * fVar227 + fVar164 * fVar164 + fVar160 * fVar160;
                  fVar161 = fVar216 * fVar216 + fVar162 * fVar162 + fVar151 * fVar151 +
                            fVar210 * fVar210 + fVar166 * fVar166 + fVar152 * fVar152 +
                            fVar173 * fVar173 + fVar213 * fVar213 + fVar159 * fVar159;
                  fVar152 = fVar216 * fVar209 + 0.0 + fVar162 * fVar222 + fVar151 * fVar165 +
                            fVar210 * fVar226 + fVar166 * fVar204 + fVar152 * fVar157 +
                            fVar173 * fVar227 + fVar213 * fVar164 + fVar159 * fVar160;
                  fVar157 = fVar161 - fVar201;
                  fVar155 = (float)NEON_fminnm(fVar156 - fVar155,0x41400000);
                  fVar151 = (255.0 - fVar158) * 0.0625;
                  pbVar121 = local_e0 + (ulong)(local_f0 * uVar119) + (uVar131 & 0xfffffffc);
                  bVar163 = pbVar121[2];
                  bVar8 = pbVar121[1];
                  bVar9 = *pbVar121;
                  if (fVar158 * 0.0625 <= fVar151) {
                    fVar151 = fVar158 * 0.0625;
                  }
                  uVar5 = (uint)bVar163;
                  if ((uint)bVar8 <= (uint)bVar163) {
                    uVar5 = (uint)bVar8;
                  }
                  fVar152 = (float)NEON_fminnm((SQRT(fVar157 * fVar157 + fVar152 * fVar152 * 4.0) /
                                                (fVar148 * fVar148 * 36.0 + fVar161 + fVar201 + 1.0)
                                               + -0.35) / 0.4,0x3f800000);
                  if (bVar9 <= uVar5) {
                    uVar5 = (uint)bVar9;
                  }
                  fVar151 = (float)NEON_fminnm(fVar151,0x3f800000);
                  uVar6 = (uint)bVar8;
                  if ((uint)bVar8 <= (uint)bVar163) {
                    uVar6 = (uint)bVar163;
                  }
                  uVar115 = (uint)bVar9;
                  if (fVar152 <= 0.0) {
                    fVar152 = 0.0;
                  }
                  uVar7 = uVar115;
                  if (uVar115 <= uVar6) {
                    uVar7 = uVar6;
                  }
                  if (fVar151 <= 0.0) {
                    fVar151 = 0.0;
                  }
                  fVar151 = fVar151 * fVar155 * fVar152 * fVar152 * (3.0 - (fVar152 + fVar152));
                  if ((float)(ulong)(uVar7 ^ 0xff) <= fVar151) {
                    fVar151 = (float)(ulong)(uVar7 ^ 0xff);
                  }
                  if (fVar151 <= (float)-uVar5) {
                    fVar151 = (float)-uVar5;
                  }
                  fVar152 = ABS(fVar151 + (float)(ulong)uVar115);
                  if ((INFINITY <= fVar152) && (fVar152 <= INFINITY)) {
LAB_0013a4ac:
                    prVar106 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013a4b8 to 0013a4c3 has its CatchHandler @ 0013b350 */
                    std::runtime_error::runtime_error(prVar106,"Non-finite image sample");
                    /* try { // try from 0013b27c to 0013b293 has its CatchHandler @ 0013b344 */
                    /* WARNING: Subroutine does not return */
                    __cxa_throw(prVar106,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
                  }
                  fVar152 = (float)NEON_fminnm((int)(fVar151 + (float)(ulong)uVar115),0x437f0000);
                  if (fVar152 <= 0.0) {
                    fVar152 = 0.0;
                  }
                  *pbVar121 = (byte)(int)fVar152;
                  if (ABS(fVar151 + (float)(ulong)bVar8) == INFINITY) goto LAB_0013a4ac;
                  fVar152 = (float)NEON_fminnm((int)(fVar151 + (float)(ulong)bVar8),0x437f0000);
                  if (fVar152 <= 0.0) {
                    fVar152 = 0.0;
                  }
                  pbVar121[1] = (byte)(int)fVar152;
                  if (ABS(fVar151 + (float)(ulong)bVar163) == INFINITY) goto LAB_0013a4ac;
                  fVar151 = (float)NEON_fminnm((int)(fVar151 + (float)(ulong)bVar163),0x437f0000);
                  if (fVar151 <= 0.0) {
                    fVar151 = 0.0;
                  }
                  pbVar121[2] = (byte)(int)fVar151;
                }
              }
              uVar131 = uVar131 + 4;
              uVar112 = uVar112 + 1;
            } while (uVar120 != uVar131);
          }
          uVar123 = uVar123 + 1;
          uVar111 = uVar111 + 1;
        } while (uVar110 != uVar100);
        if (puVar105 != (undefined8 *)0x0) goto LAB_0013a7e0;
      }
      if (local_138 != (undefined8 *)0x0) {
        local_130 = local_138;
        operator_delete(local_138);
      }
      if (local_120 != (float *)0x0) {
        local_118 = local_120;
        operator_delete(local_120);
      }
LAB_0013a80c:
      if (local_e0 != (undefined *)0x0) {
                    /* try { // try from 0013a818 to 0013a81b has its CatchHandler @ 0013b2fc */
        AndroidBitmap_unlockPixels(local_108,uStack_100);
      }
      if (local_b0 == (undefined *)0x0) {
        return;
      }
                    /* try { // try from 0013a828 to 0013a82b has its CatchHandler @ 0013b2f8 */
      AndroidBitmap_unlockPixels(local_d8,local_d0);
      return;
    }
  }
  else {
                    /* try { // try from 0013b2c4 to 0013b2cb has its CatchHandler @ 0013b314 */
    std::__ndk1::vector<float,std::__ndk1::allocator<float>>::__throw_length_error_abi_ne180000_();
  }
                    /* try { // try from 0013b2cc to 0013b2d3 has its CatchHandler @ 0013b300 */
  auVar237 = std::__ndk1::vector<float,std::__ndk1::allocator<float>>::
             __throw_length_error_abi_ne180000_();
                    /* catch() { ... } // from try @ 001396f8 with catch @ 0013b2d4 */
                    /* catch() { ... } // from try @ 001395c8 with catch @ 0013b38c */
  if (local_120 != (float *)0x0) {
    local_118 = local_120;
    operator_delete(local_120);
  }
  if (local_e0 != (undefined *)0x0) {
                    /* try { // try from 0013b3c0 to 0013b3c3 has its CatchHandler @ 0013b4bc */
    AndroidBitmap_unlockPixels(local_108,uStack_100);
  }
  if (local_b0 != (undefined *)0x0) {
                    /* try { // try from 0013b3d0 to 0013b3d3 has its CatchHandler @ 0013b4c0 */
    AndroidBitmap_unlockPixels(local_d8,local_d0);
  }
  if (auVar237._8_4_ != 1) {
                    /* WARNING: Subroutine does not return */
    _Unwind_Resume(auVar237._0_8_);
  }
  plVar107 = (long *)__cxa_begin_catch(auVar237._0_8_);
  __s = (char *)(**(code **)(*plVar107 + 0x10))();
  __n = strlen(__s);
  if (0xffffffffffffffef < __n) {
                    /* try { // try from 0013b4b4 to 0013b4bb has its CatchHandler @ 0013b4c4 */
                    /* WARNING: Subroutine does not return */
    std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>::
    __throw_length_error_abi_ne180000_();
  }
  if (__n < 0x17) {
    pvVar142 = (void *)((ulong)&local_d8 | 1);
    local_d8 = CONCAT71(local_d8._1_7_,(char)((int)__n << 1));
    if (__n == 0) goto LAB_0013b454;
  }
  else {
    uVar126 = (__n | 0xf) + 1;
                    /* try { // try from 0013b42c to 0013b433 has its CatchHandler @ 0013b4c4 */
    pvVar142 = operator_new(uVar126);
    local_d8 = uVar126 | 1;
    local_d0 = __n;
    local_c8 = pvVar142;
  }
  memmove(pvVar142,__s,__n);
LAB_0013b454:
  *(undefined *)((long)pvVar142 + __n) = 0;
                    /* try { // try from 0013b460 to 0013b49b has its CatchHandler @ 0013b4cc */
  uVar108 = (**(code **)(*param_1 + 0x30))(param_1,"java/io/IOException");
  pvVar142 = (void *)((ulong)&local_d8 | 1);
  if ((local_d8 & 1) != 0) {
    pvVar142 = local_c8;
  }
  (**(code **)(*param_1 + 0x70))(param_1,uVar108,pvVar142);
  if ((local_d8 & 1) != 0) {
    operator_delete(local_c8);
  }
  __cxa_end_catch();
  return;
}



/* 0013b4f0 Java_com_codex_fullm9_NativeM9_frameRecover */

void Java_com_codex_fullm9_NativeM9_frameRecover
               (_JNIEnv *param_1,undefined8 param_2,uint *param_3,_jobject *param_4)

{
  int iVar1;
  long lVar2;
  undefined *puVar3;
  undefined uVar4;
  runtime_error *this;
  int iVar5;
  ulong uVar6;
  long lVar7;
  int iVar8;
  long lVar9;
  undefined8 local_60;
  undefined8 uStack_58;
  uint local_50;
  uint local_4c;
  int local_48;
  long local_38;
  
                    /* try { // try from 0013b50c to 0013b51b has its CatchHandler @ 0013b694 */
  Pixels::Pixels((Pixels *)&local_60,param_1,param_4);
  uVar6 = (ulong)local_50;
  if (local_50 == *param_3) {
    if (local_4c == param_3[1]) {
      if ((0 < (int)local_4c) && (0 < (int)local_50)) {
        iVar5 = 0;
        do {
          if (0 < (int)uVar6) {
            lVar7 = 0;
            lVar9 = 0;
            do {
              iVar8 = (int)lVar9;
              iVar1 = iVar8 + param_3[2] + (iVar5 + param_3[3]) * 0x1000;
              lVar2 = local_38 + lVar7;
              lVar7 = lVar7 + 4;
              puVar3 = (undefined *)(lVar2 + (ulong)(uint)(iVar5 * local_48));
              *puVar3 = *(undefined *)(*(long *)(param_3 + 0x16) + (long)iVar1 + (long)iVar1 * 2);
              puVar3[1] = *(undefined *)
                           (*(long *)(param_3 + 0x16) +
                            (long)(int)((iVar8 + param_3[2] + (iVar5 + param_3[3]) * 0x1000) * 3) +
                           1);
              lVar9 = lVar9 + 1;
              uVar4 = *(undefined *)
                       (*(long *)(param_3 + 0x16) +
                        (long)(int)((iVar8 + param_3[2] + (iVar5 + param_3[3]) * 0x1000) * 3) + 2);
              puVar3[3] = 0xff;
              puVar3[2] = uVar4;
              uVar6 = (ulong)(int)*param_3;
            } while (lVar9 < (long)uVar6);
            local_4c = param_3[1];
          }
          iVar5 = iVar5 + 1;
        } while (iVar5 < (int)local_4c);
      }
      if (local_38 != 0) {
                    /* try { // try from 0013b620 to 0013b623 has its CatchHandler @ 0013b668 */
        AndroidBitmap_unlockPixels(local_60,uStack_58);
      }
      return;
    }
  }
  this = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013b644 to 0013b64f has its CatchHandler @ 0013b678 */
  std::runtime_error::runtime_error(this,"Recover dimensions");
                    /* try { // try from 0013b650 to 0013b667 has its CatchHandler @ 0013b66c */
                    /* WARNING: Subroutine does not return */
  __cxa_throw(this,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
}



/* 0013b75c Java_com_codex_fullm9_NativeM9_applyFilter */

void Java_com_codex_fullm9_NativeM9_applyFilter
               (long *param_1,undefined8 param_2,_jobject *param_3,undefined8 param_4,
               undefined8 param_5)

{
  int iVar1;
  uint uVar2;
  void *__s;
  undefined8 *puVar3;
  runtime_error *this;
  long *plVar4;
  undefined8 uVar5;
  uint *puVar6;
  undefined8 *puVar7;
  ulong uVar8;
  ulong uVar9;
  undefined8 *puVar10;
  ulong uVar11;
  undefined8 *puVar12;
  undefined8 *puVar13;
  long lVar14;
  undefined8 *this_00;
  undefined8 uVar15;
  undefined8 uVar16;
  undefined auVar17 [12];
  Pixels *local_180;
  void **ppvStack_178;
  undefined *local_170;
  undefined auStack_168 [32];
  void *local_148;
  void *local_140;
  void *local_138;
  Pixels local_130;
  undefined7 uStack_12f;
  undefined8 uStack_128;
  int local_120;
  undefined4 uStack_11c;
  uint uStack_118;
  long local_108;
  exception_ptr aeStack_100 [12];
  uint local_f4;
  undefined8 *local_f0;
  undefined8 *local_e8;
  undefined8 *local_e0;
  Pixels **local_d8;
  uint *puStack_d0;
  uint *local_c8;
  undefined8 *puStack_c0;
  long *local_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 local_90;
  long local_88;
  uint local_80;
  uint local_7c;
  void *local_78;
  undefined8 *local_70;
  undefined8 *local_68;
  undefined8 *local_60;
  undefined8 **local_58;
  
                    /* try { // try from 0013b784 to 0013b78f has its CatchHandler @ 0013bb70 */
  Pixels::Pixels(&local_130,(_JNIEnv *)param_1,param_3);
                    /* try { // try from 0013b798 to 0013b7c3 has its CatchHandler @ 0013bb88 */
  iVar1 = (**(code **)(*param_1 + 0x558))(param_1,param_4);
  if ((iVar1 != 0x3993) || (iVar1 = (**(code **)(*param_1 + 0x558))(param_1,param_5), iVar1 != 8)) {
    this = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013bb2c to 0013bb37 has its CatchHandler @ 0013bb5c */
    std::runtime_error::runtime_error(this,"Filter parameters");
                    /* try { // try from 0013bb38 to 0013bb4f has its CatchHandler @ 0013bb88 */
                    /* WARNING: Subroutine does not return */
    __cxa_throw(this,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
  }
                    /* try { // try from 0013b7cc to 0013b7d3 has its CatchHandler @ 0013bb58 */
  __s = operator_new(0x3993);
  local_148 = __s;
  local_138 = (void *)((long)__s + 0x3993);
  memset(__s,0,0x3993);
  local_140 = (void *)((long)__s + 0x3993);
                    /* try { // try from 0013b800 to 0013b83b has its CatchHandler @ 0013bb7c */
  (**(code **)(*param_1 + 0x640))(param_1,param_4,0,0x3993,__s);
  puVar6 = (uint *)0x8;
  (**(code **)(*param_1 + 0x668))(param_1,param_5,0,8,auStack_168);
  local_180 = &local_130;
  ppvStack_178 = &local_148;
  local_7c = uStack_118;
  local_80 = uStack_118;
  local_170 = auStack_168;
  if ((ulong)((long)local_120 * (long)(int)uStack_118) < 1000000) {
    if (uStack_118 != 0) {
      local_80 = 1;
    }
    uVar2 = local_80 - 1;
    if (local_80 != 0 && uVar2 != 0) goto LAB_0013b894;
  }
  else {
    uVar2 = std::__ndk1::thread::hardware_concurrency();
    if (uVar2 < 2) {
      uVar2 = 1;
    }
    if (3 < uVar2) {
      uVar2 = 4;
    }
    if (uVar2 <= uStack_118) {
      local_80 = uVar2;
    }
    uVar2 = local_80 - 1;
    if (local_80 != 0 && uVar2 != 0) {
LAB_0013b894:
      puStack_d0 = &local_7c;
      local_c8 = &local_80;
      puStack_c0 = &local_b0;
      local_b8 = &local_88;
      local_90 = 0;
      local_88 = 0;
      uStack_a8 = 0;
      local_b0 = 0;
      uStack_98 = 0;
      uStack_a0 = 0;
      local_f0 = (undefined8 *)0x0;
      local_e8 = (undefined8 *)0x0;
      local_e0 = (undefined8 *)0x0;
      local_d8 = &local_180;
                    /* try { // try from 0013b8cc to 0013b8cf has its CatchHandler @ 0013bb50 */
      puVar3 = (undefined8 *)operator_new((ulong)uVar2 << 3);
      local_e0 = puVar3 + uVar2;
      local_f4 = 1;
      local_f0 = puVar3;
      do {
        local_e8 = puVar3;
        if (puVar3 < local_e0) {
                    /* try { // try from 0013b924 to 0013b933 has its CatchHandler @ 0013bbac */
          std::__ndk1::allocator_traits<std::__ndk1::allocator<std::__ndk1::thread>>::
          construct_abi_ne180000_<std::__ndk1::thread,parallelRows<Java_com_codex_fullm9_NativeM9_applyFilter::__0>(int,int,Java_com_codex_fullm9_NativeM9_applyFilter::__0)::_lambda(unsigned_int)_1_&,unsigned_int&,void>
                    ((allocator *)puVar3,(thread *)&local_d8,(_lambda_unsigned_int__1_ *)&local_f4,
                     puVar6);
          puVar3 = puVar3 + 1;
        }
        else {
          lVar14 = (long)puVar3 - (long)local_f0 >> 3;
          uVar9 = lVar14 + 1;
          if (uVar9 >> 0x3d != 0) {
                    /* try { // try from 0013bb14 to 0013bb1f has its CatchHandler @ 0013bbbc */
            std::__ndk1::vector<std::__ndk1::thread,std::__ndk1::allocator<std::__ndk1::thread>>::
            __throw_length_error_abi_ne180000_();
LAB_0013bb1c:
                    /* WARNING: Subroutine does not return */
            std::__throw_bad_array_new_length_abi_ne180000_();
          }
          uVar8 = (long)local_e0 - (long)local_f0 >> 2;
          if (uVar8 <= uVar9) {
            uVar8 = uVar9;
          }
          if (0x7ffffffffffffff7 < (ulong)((long)local_e0 - (long)local_f0)) {
            uVar8 = 0x1fffffffffffffff;
          }
          local_58 = &local_e0;
          if (uVar8 == 0) {
            local_78 = (void *)0x0;
          }
          else {
            if (uVar8 >> 0x3d != 0) goto LAB_0013bb1c;
                    /* try { // try from 0013b980 to 0013b983 has its CatchHandler @ 0013bb94 */
            local_78 = operator_new(uVar8 << 3);
          }
          local_70 = (undefined8 *)((long)local_78 + lVar14 * 8);
          local_60 = (undefined8 *)((long)local_78 + uVar8 * 8);
                    /* try { // try from 0013b99c to 0013b9ab has its CatchHandler @ 0013bb98 */
          local_68 = local_70;
          std::__ndk1::allocator_traits<std::__ndk1::allocator<std::__ndk1::thread>>::
          construct_abi_ne180000_<std::__ndk1::thread,parallelRows<Java_com_codex_fullm9_NativeM9_applyFilter::__0>(int,int,Java_com_codex_fullm9_NativeM9_applyFilter::__0)::_lambda(unsigned_int)_1_&,unsigned_int&,void>
                    ((allocator *)local_70,(thread *)&local_d8,(_lambda_unsigned_int__1_ *)&local_f4
                     ,puVar6);
          puVar13 = local_f0;
          puVar3 = local_68 + 1;
          puVar10 = local_70;
          puVar12 = puVar3;
          local_e0 = local_60;
          puVar7 = local_e8;
          if ((long)local_e8 - (long)local_f0 != 0) {
            uVar9 = ((long)local_e8 - (long)local_f0) - 8;
            puVar10 = local_70;
            if ((uVar9 < 0x48) ||
               ((uVar8 = (long)local_e8 + (-8 - (long)local_f0) & 0xfffffffffffffff8,
                (undefined8 *)((long)local_70 + (-8 - uVar8)) < local_e8 &&
                ((undefined8 *)((long)local_e8 + (-8 - uVar8)) < local_70)))) {
LAB_0013ba68:
              do {
                puVar7 = puVar7 + -1;
                puVar10 = puVar10 + -1;
                *puVar10 = *puVar7;
                *puVar7 = 0;
              } while (puVar7 != local_f0);
            }
            else {
              puVar12 = local_e8 + -2;
              uVar9 = (uVar9 >> 3) + 1;
              uVar11 = uVar9 & 0x3ffffffffffffffc;
              puVar10 = local_70 + -uVar11;
              puVar7 = local_70 + -2;
              uVar8 = uVar11;
              do {
                uVar16 = puVar12[-2];
                uVar15 = puVar12[1];
                uVar5 = *puVar12;
                uVar8 = uVar8 - 4;
                puVar7[-1] = puVar12[-1];
                puVar7[-2] = uVar16;
                puVar7[1] = uVar15;
                *puVar7 = uVar5;
                puVar7 = puVar7 + -4;
                puVar12[-1] = 0;
                puVar12[-2] = 0;
                puVar12[1] = 0;
                *puVar12 = 0;
                puVar12 = puVar12 + -4;
              } while (uVar8 != 0);
              puVar7 = local_e8 + -uVar11;
              if (uVar9 != uVar11) goto LAB_0013ba68;
            }
            this_00 = local_e8;
            local_f0 = puVar10;
            local_e8 = puVar3;
            do {
              this_00 = this_00 + -1;
              std::__ndk1::thread::~thread((thread *)this_00);
              puVar10 = local_f0;
              puVar12 = local_e8;
              puVar7 = puVar13;
            } while (this_00 != puVar13);
          }
          local_e8 = puVar12;
          local_f0 = puVar10;
          if (puVar7 != (undefined8 *)0x0) {
            operator_delete(puVar7);
          }
        }
        local_f4 = local_f4 + 1;
      } while (local_f4 < local_80);
                    /* try { // try from 0013bbd8 to 0013bbe3 has its CatchHandler @ 0013bcb8 */
      local_e8 = puVar3;
      parallelRows<Java_com_codex_fullm9_NativeM9_applyFilter::$_0>(int,int,Java_com_codex_fullm9_NativeM9_applyFilter::$_0)
      ::{lambda(unsigned_int)#1}::operator()((_lambda_unsigned_int__1_ *)&local_d8,0);
      uVar2 = local_f4;
      puVar3 = local_f0;
      puVar7 = local_f0;
      puVar13 = local_e8;
      if (local_f4 < local_80) {
        do {
                    /* try { // try from 0013bbf4 to 0013bbff has its CatchHandler @ 0013bcbc */
          parallelRows<Java_com_codex_fullm9_NativeM9_applyFilter::$_0>(int,int,Java_com_codex_fullm9_NativeM9_applyFilter::$_0)
          ::{lambda(unsigned_int)#1}::operator()((_lambda_unsigned_int__1_ *)&local_d8,uVar2);
          uVar2 = uVar2 + 1;
          puVar3 = local_f0;
          puVar7 = local_f0;
          puVar13 = local_e8;
        } while (uVar2 < local_80);
      }
      for (; puVar10 = local_e8, local_f0 = puVar7, puVar3 != local_e8; puVar3 = puVar3 + 1) {
        local_e8 = puVar13;
                    /* try { // try from 0013bc1c to 0013bc23 has its CatchHandler @ 0013bcc0 */
        std::__ndk1::thread::join();
        puVar7 = local_f0;
        puVar13 = local_e8;
        local_e8 = puVar10;
      }
      if (local_88 != 0) {
        local_e8 = puVar13;
        std::exception_ptr::exception_ptr(aeStack_100,(exception_ptr *)&local_88);
                    /* try { // try from 0013bc98 to 0013bc9f has its CatchHandler @ 0013bca4 */
        auVar17 = std::rethrow_exception(aeStack_100);
                    /* catch() { ... } // from try @ 0013bbd4 with catch @ 0013bca0 */
                    /* catch() { ... } // from try @ 0013bc1c with catch @ 0013bcc0 */
        std::__ndk1::vector<std::__ndk1::thread,std::__ndk1::allocator<std::__ndk1::thread>>::
        ~vector_abi_ne180000_
                  ((vector<std::__ndk1::thread,std::__ndk1::allocator<std::__ndk1::thread>> *)
                   &local_f0);
        std::__ndk1::mutex::~mutex((mutex *)&local_b0);
        std::exception_ptr::~exception_ptr((exception_ptr *)&local_88);
        if (local_148 != (void *)0x0) {
          local_140 = local_148;
          operator_delete(local_148);
        }
        Pixels::~Pixels(&local_130);
        if (auVar17._8_4_ == 1) {
          plVar4 = (long *)__cxa_begin_catch(auVar17._0_8_);
          uVar5 = (**(code **)(*plVar4 + 0x10))();
                    /* try { // try from 0013bd18 to 0013bd1f has its CatchHandler @ 0013bd7c */
          _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2B8ne180000ILi0EEEPKc
                    (&local_130,uVar5);
                    /* try { // try from 0013bd28 to 0013bd63 has its CatchHandler @ 0013bd84 */
          uVar5 = (**(code **)(*param_1 + 0x30))(param_1,"java/io/IOException");
          uVar9 = (ulong)&local_130 | 1;
          if (((byte)local_130 & 1) != 0) {
            uVar9 = CONCAT44(uStack_11c,local_120);
          }
          (**(code **)(*param_1 + 0x70))(param_1,uVar5,uVar9);
          if (((byte)local_130 & 1) != 0) {
            operator_delete((void *)CONCAT44(uStack_11c,local_120));
          }
          __cxa_end_catch();
          return;
        }
                    /* WARNING: Subroutine does not return */
        _Unwind_Resume(auVar17._0_8_);
      }
      local_88 = 0;
      local_e8 = puVar13;
      if (puVar7 != (undefined8 *)0x0) {
        while (puVar13 != puVar7) {
          puVar13 = puVar13 + -1;
          std::__ndk1::thread::~thread((thread *)puVar13);
        }
        local_e8 = puVar7;
        operator_delete(local_f0);
      }
      std::__ndk1::mutex::~mutex((mutex *)&local_b0);
      std::exception_ptr::~exception_ptr((exception_ptr *)&local_88);
      goto joined_r0x0013badc;
    }
  }
                    /* try { // try from 0013bac8 to 0013bad7 has its CatchHandler @ 0013bb7c */
  Java_com_codex_fullm9_NativeM9_applyFilter::$_0::operator()((__0 *)&local_180,0,uStack_118);
joined_r0x0013badc:
  if (local_148 != (void *)0x0) {
    local_140 = local_148;
    operator_delete(local_148);
  }
  if (local_108 != 0) {
                    /* try { // try from 0013baf4 to 0013baf7 has its CatchHandler @ 0013bb54 */
    AndroidBitmap_unlockPixels(CONCAT71(uStack_12f,local_130),uStack_128);
  }
  return;
}



/* 0013bda8 Java_com_codex_fullm9_NativeM9_rawNeutral */

undefined8
Java_com_codex_fullm9_NativeM9_rawNeutral(long *param_1,undefined8 param_2,undefined8 param_3)

{
  uint uVar1;
  int iVar2;
  void *__s;
  long lVar3;
  runtime_error *prVar4;
  ulong __n;
  undefined4 uVar5;
  float fVar6;
  float fVar7;
  undefined8 uVar8;
  undefined8 local_58;
  float local_50;
  
  if (((Java_com_codex_fullm9_NativeM9_rawNeutral::a & 1) == 0) &&
     (iVar2 = __cxa_guard_acquire(&Java_com_codex_fullm9_NativeM9_rawNeutral::a), iVar2 != 0)) {
                    /* try { // try from 0013bfbc to 0013bfc7 has its CatchHandler @ 0013c03c */
    RawApi::RawApi((RawApi *)Java_com_codex_fullm9_NativeM9_rawNeutral::a);
    __cxa_guard_release(&Java_com_codex_fullm9_NativeM9_rawNeutral::a);
  }
                    /* try { // try from 0013bde0 to 0013bdeb has its CatchHandler @ 0013c098 */
  uVar1 = (**(code **)(*param_1 + 0x558))(param_1,param_3);
  __n = (ulong)uVar1;
  if (0xf000000e < uVar1 + 0xefffffff) {
                    /* try { // try from 0013be0c to 0013be13 has its CatchHandler @ 0013c094 */
    __s = operator_new(__n);
    memset(__s,0,__n);
                    /* try { // try from 0013be2c to 0013be7f has its CatchHandler @ 0013c0b8 */
    (**(code **)(*param_1 + 0x640))(param_1,param_3,0,__n,__s);
    lVar3 = (*(code *)Java_com_codex_fullm9_NativeM9_rawNeutral::a._8_8_)(0);
    if ((lVar3 != 0) &&
       (iVar2 = (*(code *)Java_com_codex_fullm9_NativeM9_rawNeutral::a._16_8_)(lVar3,__s,__n),
       iVar2 == 0)) {
                    /* try { // try from 0013be8c to 0013bebf has its CatchHandler @ 0013c0ac */
      uVar5 = (*(code *)Java_com_codex_fullm9_NativeM9_rawNeutral::a._120_8_)(lVar3,0);
      fVar6 = (float)(*(code *)Java_com_codex_fullm9_NativeM9_rawNeutral::a._120_8_)(lVar3,1);
      fVar7 = (float)(*(code *)Java_com_codex_fullm9_NativeM9_rawNeutral::a._120_8_)(lVar3,2);
      if (0.0 < fVar6) {
        uVar8 = NEON_fcmgt(0x358637bd358637bd,CONCAT44(fVar6,uVar5),4);
        uVar8 = NEON_bif(0x358637bd358637bd,CONCAT44(fVar6,uVar5),uVar8,1);
        local_58 = CONCAT44(fVar6 / (float)((ulong)uVar8 >> 0x20),fVar6 / (float)uVar8);
        local_50 = 1e-06;
        if (1e-06 <= fVar7) {
          local_50 = fVar7;
        }
        local_50 = fVar6 / local_50;
                    /* try { // try from 0013bf10 to 0013bf4f has its CatchHandler @ 0013c0a8 */
        uVar8 = (**(code **)(*param_1 + 0x5a8))(param_1,3);
        (**(code **)(*param_1 + 0x6a8))(param_1,uVar8,0,3,&local_58);
        (*(code *)Java_com_codex_fullm9_NativeM9_rawNeutral::a._56_8_)(lVar3);
        operator_delete(__s);
        return uVar8;
      }
      prVar4 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013c018 to 0013c023 has its CatchHandler @ 0013c064 */
      std::runtime_error::runtime_error(prVar4,"RAW white point is unavailable");
                    /* try { // try from 0013c024 to 0013c03b has its CatchHandler @ 0013c060 */
                    /* WARNING: Subroutine does not return */
      __cxa_throw(prVar4,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
    }
    prVar4 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013bf80 to 0013bf8b has its CatchHandler @ 0013c080 */
    std::runtime_error::runtime_error(prVar4,"Cannot read RAW white balance");
                    /* try { // try from 0013bf8c to 0013bfa7 has its CatchHandler @ 0013c0b8 */
                    /* WARNING: Subroutine does not return */
    __cxa_throw(prVar4,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
  }
  prVar4 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013bfe4 to 0013bfef has its CatchHandler @ 0013c068 */
  std::runtime_error::runtime_error(prVar4,"RAW metadata input size");
                    /* try { // try from 0013bff0 to 0013c007 has its CatchHandler @ 0013c098 */
                    /* WARNING: Subroutine does not return */
  __cxa_throw(prVar4,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
}



/* 0013c1b8 operator() */

/* Java_com_codex_fullm9_NativeM9_applyFilter::$_0::TEMPNAMEPLACEHOLDERVALUE(int, int) const */

void __thiscall
Java_com_codex_fullm9_NativeM9_applyFilter::$_0::operator()(__0 *this,int param_1,int param_2)

{
  uchar *puVar1;
  runtime_error *this_00;
  uint uVar2;
  long lVar3;
  uint uVar4;
  int iVar5;
  float fVar6;
  float local_6c;
  float local_68;
  float local_64;
  
  if ((param_1 < param_2) && (lVar3 = *(long *)this, *(int *)(lVar3 + 0x10) != 0)) {
    do {
      uVar2 = *(uint *)(lVar3 + 0x10);
      if (uVar2 != 0) {
        iVar5 = 0;
        uVar4 = 0;
        do {
          puVar1 = (uchar *)(*(long *)(lVar3 + 0x28) +
                             (ulong)(uint)(*(int *)(lVar3 + 0x18) * param_1) + (long)iVar5);
          m9::leicaPixel(puVar1,**(uchar ***)(this + 8),*(float **)(this + 0x10),uVar4,param_1,uVar2
                         ,*(int *)(lVar3 + 0x14),&local_6c);
          fVar6 = ABS(local_6c * 255.0);
          if ((INFINITY <= fVar6) && (fVar6 <= INFINITY)) {
LAB_0013c31c:
            this_00 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013c328 to 0013c333 has its CatchHandler @ 0013c370 */
            std::runtime_error::runtime_error(this_00,"Non-finite image sample");
                    /* WARNING: Subroutine does not return */
            __cxa_throw(this_00,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
          }
          fVar6 = (float)NEON_fminnm((int)(local_6c * 255.0),0x437f0000);
          if (fVar6 <= 0.0) {
            fVar6 = 0.0;
          }
          *puVar1 = (uchar)(int)fVar6;
          if (ABS(local_68 * 255.0) == INFINITY) goto LAB_0013c31c;
          fVar6 = (float)NEON_fminnm((int)(local_68 * 255.0),0x437f0000);
          if (fVar6 <= 0.0) {
            fVar6 = 0.0;
          }
          puVar1[1] = (uchar)(int)fVar6;
          if (ABS(local_64 * 255.0) == INFINITY) goto LAB_0013c31c;
          puVar1[3] = 0xff;
          uVar4 = uVar4 + 1;
          iVar5 = iVar5 + 4;
          fVar6 = (float)NEON_fminnm((int)(local_64 * 255.0),0x437f0000);
          if (fVar6 <= 0.0) {
            fVar6 = 0.0;
          }
          puVar1[2] = (uchar)(int)fVar6;
          lVar3 = *(long *)this;
          uVar2 = *(uint *)(lVar3 + 0x10);
        } while (uVar4 < uVar2);
      }
      param_1 = param_1 + 1;
    } while (param_1 != param_2);
  }
  return;
}



/* 0013c384 operator() */

/* parallelRows<Java_com_codex_fullm9_NativeM9_applyFilter::$_0>(int, int,
   Java_com_codex_fullm9_NativeM9_applyFilter::$_0)::{lambda(unsigned
   int)#1}::TEMPNAMEPLACEHOLDERVALUE(unsigned int) const */

void __thiscall
parallelRows<Java_com_codex_fullm9_NativeM9_applyFilter::$_0>(int,int,Java_com_codex_fullm9_NativeM9_applyFilter::$_0)
::{lambda(unsigned_int)#1}::operator()(_lambda_unsigned_int__1_ *this,uint param_1)

{
  int iVar1;
  int iVar2;
  ulong uVar3;
  
  uVar3 = (ulong)**(uint **)(this + 0x10);
  iVar1 = 0;
  if (uVar3 != 0) {
    iVar1 = (int)(((long)**(int **)(this + 8) * (ulong)param_1) / uVar3);
  }
  iVar2 = 0;
  if (uVar3 != 0) {
    iVar2 = (int)(((long)**(int **)(this + 8) * (ulong)(param_1 + 1)) / uVar3);
  }
                    /* try { // try from 0013c3c0 to 0013c3c7 has its CatchHandler @ 0013c3d8 */
  Java_com_codex_fullm9_NativeM9_applyFilter::$_0::operator()(*(__0 **)this,iVar1,iVar2);
  return;
}



/* 0013c440 construct[abi:ne180000]<std::__ndk1::thread,parallelRows<Java_com_codex_fullm9_NativeM9_applyFilter::$_0>(int,int,Java_com_codex_fullm9_NativeM9_applyFilter::$_0)::{lambda(unsigned_int)#1}&,unsigned_int&,void> */

/* void std::__ndk1::allocator_traits<std::__ndk1::allocator<std::__ndk1::thread>
   >::construct[abi:ne180000]<std::__ndk1::thread,
   parallelRows<Java_com_codex_fullm9_NativeM9_applyFilter::$_0>(int, int,
   Java_com_codex_fullm9_NativeM9_applyFilter::$_0)::{lambda(unsigned int)#1}&, unsigned int&,
   void>(std::__ndk1::allocator<std::__ndk1::thread>&, std::__ndk1::thread*,
   parallelRows<Java_com_codex_fullm9_NativeM9_applyFilter::$_0>(int, int,
   Java_com_codex_fullm9_NativeM9_applyFilter::$_0)::{lambda(unsigned int)#1}&, unsigned int&) */

void std::__ndk1::allocator_traits<std::__ndk1::allocator<std::__ndk1::thread>>::
     construct_abi_ne180000_<std::__ndk1::thread,parallelRows<Java_com_codex_fullm9_NativeM9_applyFilter::__0>(int,int,Java_com_codex_fullm9_NativeM9_applyFilter::__0)::_lambda(unsigned_int)_1_&,unsigned_int&,void>
               (allocator *param_1,thread *param_2,_lambda_unsigned_int__1_ *param_3,uint *param_4)

{
  undefined4 uVar1;
  int iVar2;
  __thread_struct *this;
  __thread_struct **__arg;
  __thread_struct *p_Var3;
  __thread_struct *p_Var4;
  __thread_struct *p_Var5;
  __thread_struct *p_Var6;
  __thread_struct *p_Var7;
  
  this = (__thread_struct *)operator_new(8);
                    /* try { // try from 0013c46c to 0013c46f has its CatchHandler @ 0013c4f0 */
  __thread_struct::__thread_struct(this);
                    /* try { // try from 0013c474 to 0013c47b has its CatchHandler @ 0013c4dc */
  __arg = (__thread_struct **)operator_new(0x38);
  p_Var5 = *(__thread_struct **)(param_2 + 8);
  p_Var4 = *(__thread_struct **)param_2;
  p_Var7 = *(__thread_struct **)(param_2 + 0x18);
  p_Var6 = *(__thread_struct **)(param_2 + 0x10);
  p_Var3 = *(__thread_struct **)(param_2 + 0x20);
  uVar1 = *(undefined4 *)param_3;
  *__arg = this;
  __arg[2] = p_Var5;
  __arg[1] = p_Var4;
  __arg[4] = p_Var7;
  __arg[3] = p_Var6;
  __arg[5] = p_Var3;
  *(undefined4 *)(__arg + 6) = uVar1;
                    /* try { // try from 0013c4a4 to 0013c4db has its CatchHandler @ 0013c504 */
  iVar2 = pthread_create((pthread_t *)param_1,(pthread_attr_t *)0x0,
                         __thread_proxy_abi_ne180000_<std::__ndk1::tuple<std::__ndk1::unique_ptr<std::__ndk1::__thread_struct,std::__ndk1::default_delete<std::__ndk1::__thread_struct>>,parallelRows<Java_com_codex_fullm9_NativeM9_applyFilter::__0>(int,int,Java_com_codex_fullm9_NativeM9_applyFilter::__0)::_lambda(unsigned_int)_1_,unsigned_int>>
                         ,__arg);
  if (iVar2 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __throw_system_error(iVar2,"thread constructor failed");
}



/* 0013c520 __thread_proxy[abi:ne180000]<std::__ndk1::tuple<std::__ndk1::unique_ptr<std::__ndk1::__thread_struct,std::__ndk1::default_delete<std::__ndk1::__thread_struct>>,parallelRows<Java_com_codex_fullm9_NativeM9_applyFilter::$_0>(int,int,Java_com_codex_fullm9_NativeM9_applyFilter::$_0)::{lambda(unsigned_int)#1},unsigned_int>> */

/* void* 
   std::__ndk1::__thread_proxy[abi:ne180000]<std::__ndk1::tuple<std::__ndk1::unique_ptr<std::__ndk1::__thread_struct,
   std::__ndk1::default_delete<std::__ndk1::__thread_struct> >,
   parallelRows<Java_com_codex_fullm9_NativeM9_applyFilter::$_0>(int, int,
   Java_com_codex_fullm9_NativeM9_applyFilter::$_0)::{lambda(unsigned int)#1}, unsigned int>
   >(void*) */

void * std::__ndk1::
       __thread_proxy_abi_ne180000_<std::__ndk1::tuple<std::__ndk1::unique_ptr<std::__ndk1::__thread_struct,std::__ndk1::default_delete<std::__ndk1::__thread_struct>>,parallelRows<Java_com_codex_fullm9_NativeM9_applyFilter::__0>(int,int,Java_com_codex_fullm9_NativeM9_applyFilter::__0)::_lambda(unsigned_int)_1_,unsigned_int>>
                 (void *param_1)

{
  pthread_key_t __key;
  pthread_key_t *ppVar1;
  void *__pointer;
  __thread_struct *this;
  
                    /* try { // try from 0013c538 to 0013c557 has its CatchHandler @ 0013c590 */
  ppVar1 = (pthread_key_t *)__thread_local_data();
                    /* WARNING: Load size is inaccurate */
  __pointer = *param_1;
  __key = *ppVar1;
  *(undefined8 *)param_1 = 0;
  pthread_setspecific(__key,__pointer);
  parallelRows<Java_com_codex_fullm9_NativeM9_applyFilter::$_0>(int,int,Java_com_codex_fullm9_NativeM9_applyFilter::$_0)
  ::{lambda(unsigned_int)#1}::operator()
            ((_lambda_unsigned_int__1_ *)((long)param_1 + 8),*(uint *)((long)param_1 + 0x30));
                    /* WARNING: Load size is inaccurate */
  this = *param_1;
  *(undefined8 *)param_1 = 0;
  if (this != (__thread_struct *)0x0) {
    __thread_struct::~__thread_struct(this);
    operator_delete(this);
  }
  operator_delete(param_1);
  return (void *)0x0;
}



/* 0013c5a4 ~unique_ptr[abi:ne180000] */

/* std::__ndk1::unique_ptr<std::__ndk1::tuple<std::__ndk1::unique_ptr<std::__ndk1::__thread_struct,
   std::__ndk1::default_delete<std::__ndk1::__thread_struct> >,
   parallelRows<Java_com_codex_fullm9_NativeM9_applyFilter::$_0>(int, int,
   Java_com_codex_fullm9_NativeM9_applyFilter::$_0)::{lambda(unsigned int)#1}, unsigned int>,
   std::__ndk1::default_delete<std::__ndk1::tuple<std::__ndk1::unique_ptr<std::__ndk1::__thread_struct,
   std::__ndk1::default_delete<std::__ndk1::__thread_struct> >,
   parallelRows<Java_com_codex_fullm9_NativeM9_applyFilter::$_0>(int, int,
   Java_com_codex_fullm9_NativeM9_applyFilter::$_0)::{lambda(unsigned int)#1}, unsigned int> >
   >::~unique_ptr[abi:ne180000]() */

void __thiscall
std::__ndk1::
unique_ptr<std::__ndk1::tuple<std::__ndk1::unique_ptr<std::__ndk1::__thread_struct,std::__ndk1::default_delete<std::__ndk1::__thread_struct>>,parallelRows<Java_com_codex_fullm9_NativeM9_applyFilter::$_0>(int,int,Java_com_codex_fullm9_NativeM9_applyFilter::$_0)::{lambda(unsigned_int)#1},unsigned_int>,std::__ndk1::default_delete<std::__ndk1::tuple<std::__ndk1::unique_ptr<std::__ndk1::__thread_struct,std::__ndk1::default_delete<std::__ndk1::__thread_struct>>,parallelRows<Java_com_codex_fullm9_NativeM9_applyFilter::$_0>(int,int,Java_com_codex_fullm9_NativeM9_applyFilter::$_0)::{lambda(unsigned_int)#1},unsigned_int>>>
::~unique_ptr_abi_ne180000_
          (unique_ptr<std::__ndk1::tuple<std::__ndk1::unique_ptr<std::__ndk1::__thread_struct,std::__ndk1::default_delete<std::__ndk1::__thread_struct>>,parallelRows<Java_com_codex_fullm9_NativeM9_applyFilter::__0>(int,int,Java_com_codex_fullm9_NativeM9_applyFilter::__0)::_lambda(unsigned_int)_1_,unsigned_int>,std::__ndk1::default_delete<std::__ndk1::tuple<std::__ndk1::unique_ptr<std::__ndk1::__thread_struct,std::__ndk1::default_delete<std::__ndk1::__thread_struct>>,parallelRows<Java_com_codex_fullm9_NativeM9_applyFilter::__0>(int,int,Java_com_codex_fullm9_NativeM9_applyFilter::__0)::_lambda(unsigned_int)_1_,unsigned_int>>>
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
      __thread_struct::~__thread_struct(this_00);
      operator_delete(this_00);
    }
    operator_delete(pp_Var1);
    return;
  }
  return;
}



/* 0013c5f4 Pixels */

/* Pixels::Pixels(_JNIEnv*, _jobject*) */

void __thiscall Pixels::Pixels(Pixels *this,_JNIEnv *param_1,_jobject *param_2)

{
  int iVar1;
  runtime_error *this_00;
  
  *(_JNIEnv **)this = param_1;
  *(_jobject **)(this + 8) = param_2;
  *(undefined8 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x20) = 0;
  *(undefined8 *)(this + 0x28) = 0;
  *(undefined8 *)(this + 0x10) = 0;
  iVar1 = AndroidBitmap_getInfo(param_1,param_2);
  if (((iVar1 == 0) && (*(int *)(this + 0x1c) == 1)) &&
     (iVar1 = AndroidBitmap_lockPixels(*(undefined8 *)this,*(undefined8 *)(this + 8),this + 0x28),
     iVar1 == 0)) {
    return;
  }
  this_00 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013c668 to 0013c673 has its CatchHandler @ 0013c68c */
  std::runtime_error::runtime_error(this_00,"Bitmap pixels unavailable");
                    /* WARNING: Subroutine does not return */
  __cxa_throw(this_00,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
}



/* 0013c6a0 ~Pixels */

/* Pixels::~Pixels() */

void __thiscall Pixels::~Pixels(Pixels *this)

{
  if (*(long *)(this + 0x28) != 0) {
                    /* try { // try from 0013c6b4 to 0013c6bb has its CatchHandler @ 0013c6c4 */
    AndroidBitmap_unlockPixels(*(undefined8 *)this,*(undefined8 *)(this + 8));
  }
  return;
}



/* 0013c6c8 _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2B8ne180000ILi0EEEPKc */

void _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2B8ne180000ILi0EEEPKc
               (long *param_1,char *param_2)

{
  size_t __n;
  undefined *__dest;
  
  __n = strlen(param_2);
  if (0xffffffffffffffef < __n) {
                    /* WARNING: Subroutine does not return */
    std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>::
    __throw_length_error_abi_ne180000_();
  }
  if (__n < 0x17) {
    __dest = (undefined *)((long)param_1 + 1);
    *(char *)param_1 = (char)((int)__n << 1);
    if (__n == 0) {
      *__dest = 0;
      return;
    }
  }
  else {
    __dest = (undefined *)operator_new((__n | 0xf) + 1);
    param_1[1] = __n;
    param_1[2] = (long)__dest;
    *param_1 = (__n | 0xf) + 2;
  }
  memmove(__dest,param_2,__n);
  __dest[__n] = 0;
  return;
}



/* 0013c764 __clang_call_terminate */

void __clang_call_terminate(void)

{
  __cxa_begin_catch();
                    /* WARNING: Subroutine does not return */
  std::terminate();
}



/* 0013c774 Frame */

/* m9::Frame::Frame(int, int) */

void __thiscall m9::Frame::Frame(Frame *this,int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  void *pvVar3;
  runtime_error *this_00;
  
  iVar1 = 0x1001 - param_1;
  if (param_1 < 0x1001) {
    iVar1 = 0x1000 - param_1;
  }
  iVar2 = 0xc01 - param_2;
  if (param_2 < 0xc01) {
    iVar2 = 0xc00 - param_2;
  }
  *(int *)this = param_1;
  *(int *)(this + 4) = param_2;
  *(undefined8 *)(this + 0x18) = 0;
  *(undefined8 *)(this + 0x20) = 0;
  *(int *)(this + 8) = iVar1 >> 1;
  *(int *)(this + 0xc) = iVar2 >> 1;
  *(void **)(this + 0x10) = (void *)0x0;
  pvVar3 = operator_new(0x2400000);
  *(void **)(this + 0x10) = pvVar3;
  *(long *)(this + 0x20) = (long)pvVar3 + 0x2400000;
  memset(pvVar3,0,0x2400000);
  *(long *)(this + 0x18) = (long)pvVar3 + 0x2400000;
  *(undefined8 *)(this + 0x28) = 0;
  *(undefined8 *)(this + 0x30) = 0;
  *(undefined8 *)(this + 0x38) = 0;
                    /* try { // try from 0013c810 to 0013c817 has its CatchHandler @ 0013c98c */
  pvVar3 = operator_new(0x240000);
  *(void **)(this + 0x28) = pvVar3;
  *(long *)(this + 0x38) = (long)pvVar3 + 0x240000;
  memset(pvVar3,0,0x240000);
  *(undefined8 *)(this + 0x40) = 0;
  *(long *)(this + 0x30) = (long)pvVar3 + 0x240000;
  *(undefined8 *)(this + 0x48) = 0;
  *(undefined8 *)(this + 0x50) = 0;
                    /* try { // try from 0013c840 to 0013c847 has its CatchHandler @ 0013c96c */
  pvVar3 = operator_new(0x240000);
  *(void **)(this + 0x40) = pvVar3;
  *(long *)(this + 0x50) = (long)pvVar3 + 0x240000;
  memset(pvVar3,0,0x240000);
  *(undefined8 *)(this + 0x58) = 0;
  *(long *)(this + 0x48) = (long)pvVar3 + 0x240000;
  *(undefined8 *)(this + 0x60) = 0;
  *(undefined8 *)(this + 0x68) = 0;
                    /* try { // try from 0013c870 to 0013c877 has its CatchHandler @ 0013c94c */
  pvVar3 = operator_new(0x2400000);
  *(void **)(this + 0x58) = pvVar3;
  *(long *)(this + 0x68) = (long)pvVar3 + 0x2400000;
  memset(pvVar3,0,0x2400000);
  *(long *)(this + 0x60) = (long)pvVar3 + 0x2400000;
  if ((0xffffefff < param_1 - 0x1001U) && (0xfffff3ff < param_2 - 0xc01U)) {
    return;
  }
  this_00 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013c8d8 to 0013c8e3 has its CatchHandler @ 0013c904 */
  std::runtime_error::runtime_error(this_00,"M9 frame dimensions");
                    /* try { // try from 0013c8e4 to 0013c8fb has its CatchHandler @ 0013c8fc */
                    /* WARNING: Subroutine does not return */
  __cxa_throw(this_00,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
}



/* 0013c9a8 prepare */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* m9::Frame::prepare() */

void m9::Frame::prepare(void)

{
  byte *pbVar1;
  long in_x0;
  runtime_error *this;
  long lVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  long lVar12;
  long lVar13;
  long lVar14;
  long lVar15;
  float fVar16;
  
  lVar13 = 0;
  lVar4 = 0;
  lVar2 = 0;
  lVar5 = 0x9003;
  lVar6 = 0x9004;
  lVar7 = 0x9007;
  lVar8 = 0x900b;
  lVar9 = 0x9009;
  lVar10 = 0x900a;
  lVar11 = 0x9006;
  do {
    lVar12 = 0;
    lVar14 = lVar13;
    do {
      lVar15 = *(long *)(in_x0 + 0x10);
      pbVar1 = (byte *)(lVar15 + lVar4 + lVar12);
      fVar16 = (float)((uint)*pbVar1 + (uint)pbVar1[3] + (uint)pbVar1[6] + (uint)pbVar1[9] +
                       (uint)pbVar1[0x3000] + (uint)pbVar1[0x3003] +
                       (uint)pbVar1[0x3006] + (uint)pbVar1[0x3009] + (uint)pbVar1[0x6000] +
                       (uint)pbVar1[0x6003] + (uint)pbVar1[0x6006] + (uint)pbVar1[0x6009] +
                       (uint)pbVar1[0x9000] + (uint)*(byte *)(lVar15 + lVar5 + lVar12) +
                      (uint)*(byte *)(lVar15 + lVar11 + lVar12) +
                      (uint)*(byte *)(lVar15 + lVar9 + lVar12)) / 16.0;
      if (ABS(fVar16) == INFINITY) {
LAB_0013ccd8:
        this = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013cce4 to 0013ccef has its CatchHandler @ 0013cd28 */
        std::runtime_error::runtime_error(this,"Non-finite image sample");
                    /* WARNING: Subroutine does not return */
        __cxa_throw(this,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
      }
      fVar16 = (float)NEON_fminnm((int)fVar16,0x437f0000);
      if (fVar16 <= 0.0) {
        fVar16 = 0.0;
      }
      *(char *)(*(long *)(in_x0 + 0x28) + lVar14) = (char)(int)fVar16;
      lVar3 = *(long *)(in_x0 + 0x10);
      lVar15 = lVar3 + lVar4 + lVar12;
      fVar16 = (float)((uint)*(byte *)(lVar15 + 1) + (uint)*(byte *)(lVar15 + 4) +
                       (uint)*(byte *)(lVar15 + 7) + (uint)*(byte *)(lVar15 + 10) +
                       (uint)*(byte *)(lVar15 + 0x3001) + (uint)*(byte *)(lVar15 + 0x3004) +
                       (uint)*(byte *)(lVar15 + 0x3007) + (uint)*(byte *)(lVar15 + 0x300a) +
                       (uint)*(byte *)(lVar15 + 0x6001) +
                       (uint)*(byte *)(lVar15 + 0x6004) + (uint)*(byte *)(lVar15 + 0x6007) +
                       (uint)*(byte *)(lVar15 + 0x600a) + (uint)*(byte *)(lVar15 + 0x9001) +
                      (uint)*(byte *)(lVar3 + lVar6 + lVar12) +
                      (uint)*(byte *)(lVar3 + lVar7 + lVar12) +
                      (uint)*(byte *)(lVar3 + lVar10 + lVar12)) / 16.0;
      if (ABS(fVar16) == INFINITY) goto LAB_0013ccd8;
      fVar16 = (float)NEON_fminnm((int)fVar16,0x437f0000);
      if (fVar16 <= 0.0) {
        fVar16 = 0.0;
      }
      *(char *)(*(long *)(in_x0 + 0x28) + lVar14 + 1) = (char)(int)fVar16;
      lVar15 = *(long *)(in_x0 + 0x10) + lVar4 + lVar12;
      pbVar1 = (byte *)(*(long *)(in_x0 + 0x10) + lVar8 + lVar12);
      fVar16 = (float)((uint)*(byte *)(lVar15 + 2) + (uint)*(byte *)(lVar15 + 5) +
                       (uint)*(byte *)(lVar15 + 8) + (uint)*(byte *)(lVar15 + 0xb) +
                       (uint)*(byte *)(lVar15 + 0x3002) + (uint)*(byte *)(lVar15 + 0x3005) +
                       (uint)*(byte *)(lVar15 + 0x3008) + (uint)*(byte *)(lVar15 + 0x300b) +
                       (uint)*(byte *)(lVar15 + 0x6002) +
                       (uint)*(byte *)(lVar15 + 0x6005) + (uint)*(byte *)(lVar15 + 0x6008) +
                       (uint)*(byte *)(lVar15 + 0x600b) + (uint)pbVar1[-9] +
                      (uint)pbVar1[-6] + (uint)pbVar1[-3] + (uint)*pbVar1) / 16.0;
      if (ABS(fVar16) == INFINITY) goto LAB_0013ccd8;
      lVar12 = lVar12 + 0xc;
      lVar15 = *(long *)(in_x0 + 0x28) + lVar14;
      lVar14 = lVar14 + 3;
      fVar16 = (float)NEON_fminnm((int)fVar16,0x437f0000);
      if (fVar16 <= 0.0) {
        fVar16 = 0.0;
      }
      *(char *)(lVar15 + 2) = (char)(int)fVar16;
    } while (lVar12 != 0x3000);
    lVar4 = lVar4 + 0xc000;
    lVar5 = lVar5 + 0xc000;
    lVar6 = lVar6 + 0xc000;
    lVar7 = lVar7 + 0xc000;
    lVar8 = lVar8 + 0xc000;
    lVar9 = lVar9 + 0xc000;
    lVar10 = lVar10 + 0xc000;
    lVar2 = lVar2 + 1;
    lVar13 = lVar13 + 0xc00;
    lVar11 = lVar11 + 0xc000;
    if (lVar2 == 0x300) {
      return;
    }
  } while( true );
}



/* 0013cd3c ~unique_ptr[abi:ne180000] */

/* std::__ndk1::unique_ptr<m9::Frame, std::__ndk1::default_delete<m9::Frame>
   >::~unique_ptr[abi:ne180000]() */

void __thiscall
std::__ndk1::unique_ptr<m9::Frame,std::__ndk1::default_delete<m9::Frame>>::~unique_ptr_abi_ne180000_
          (unique_ptr<m9::Frame,std::__ndk1::default_delete<m9::Frame>> *this)

{
  void *pvVar1;
  void *pvVar2;
  
  pvVar2 = *(void **)this;
  *(undefined8 *)this = 0;
  if (pvVar2 != (void *)0x0) {
    pvVar1 = *(void **)((long)pvVar2 + 0x58);
    if (pvVar1 != (void *)0x0) {
      *(void **)((long)pvVar2 + 0x60) = pvVar1;
      operator_delete(pvVar1);
    }
    pvVar1 = *(void **)((long)pvVar2 + 0x40);
    if (pvVar1 != (void *)0x0) {
      *(void **)((long)pvVar2 + 0x48) = pvVar1;
      operator_delete(pvVar1);
    }
    pvVar1 = *(void **)((long)pvVar2 + 0x28);
    if (pvVar1 != (void *)0x0) {
      *(void **)((long)pvVar2 + 0x30) = pvVar1;
      operator_delete(pvVar1);
    }
    pvVar1 = *(void **)((long)pvVar2 + 0x10);
    if (pvVar1 != (void *)0x0) {
      *(void **)((long)pvVar2 + 0x18) = pvVar1;
      operator_delete(pvVar1);
    }
    operator_delete(pvVar2);
    return;
  }
  return;
}



/* 0013cdb0 styleInput */

/* m9::Frame::styleInput(float*) */

void __thiscall m9::Frame::styleInput(Frame *this,float *param_1)

{
  long lVar1;
  uint uVar2;
  long lVar3;
  int iVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  long lVar8;
  long lVar9;
  byte bVar10;
  float fVar11;
  
  lVar9 = *(long *)(this + 0x28);
  lVar8 = 0;
  do {
    uVar5 = (uint)(lVar8 - 0x30U);
    if (uVar5 < 0x300) {
      lVar6 = 0;
      do {
        for (uVar2 = (int)lVar6 - 0x30; 0x3ff < uVar2; uVar2 = iVar4 - uVar2) {
          iVar4 = 0x7ff;
          if ((int)uVar2 < 0) {
            iVar4 = -1;
          }
        }
        lVar1 = lVar6 + lVar8 * 0x460;
        lVar3 = (ulong)(uVar2 | uVar5 << 10) * 3;
        lVar6 = lVar6 + 1;
        fVar11 = (float)NEON_ucvtf((uint)*(byte *)(lVar9 + lVar3));
        param_1[lVar1] = (fVar11 + -128.0) / 127.5;
        fVar11 = (float)NEON_ucvtf((uint)*(byte *)(lVar9 + 1 + lVar3));
        param_1[lVar1 + 0xec400] = (fVar11 + -128.0) / 127.5;
        bVar10 = *(byte *)(lVar9 + 2 + lVar3);
        param_1[lVar1 + 0x2c4c00] = -1.003922;
        fVar11 = (float)NEON_ucvtf((uint)bVar10);
        param_1[lVar1 + 0x1d8800] = (fVar11 + -128.0) / 127.5;
      } while (lVar6 != 0x460);
    }
    else {
      lVar6 = 0;
      do {
        uVar7 = lVar8 - 0x30U & 0xffffffff;
        do {
          iVar4 = 0x5ff;
          if ((int)uVar7 < 0) {
            iVar4 = -1;
          }
          uVar5 = iVar4 - (int)uVar7;
          uVar7 = (ulong)uVar5;
        } while (0x2ff < uVar5);
        for (uVar2 = (int)lVar6 - 0x30; 0x3ff < uVar2; uVar2 = iVar4 - uVar2) {
          iVar4 = 0x7ff;
          if ((int)uVar2 < 0) {
            iVar4 = -1;
          }
        }
        lVar1 = lVar6 + lVar8 * 0x460;
        lVar6 = lVar6 + 1;
        lVar3 = (ulong)(uVar2 | uVar5 * 0x400) * 3;
        fVar11 = (float)NEON_ucvtf((uint)*(byte *)(lVar9 + lVar3));
        param_1[lVar1] = (fVar11 + -128.0) / 127.5;
        fVar11 = (float)NEON_ucvtf((uint)*(byte *)(lVar9 + 1 + lVar3));
        param_1[lVar1 + 0xec400] = (fVar11 + -128.0) / 127.5;
        bVar10 = *(byte *)(lVar9 + 2 + lVar3);
        param_1[lVar1 + 0x2c4c00] = -1.003922;
        fVar11 = (float)NEON_ucvtf((uint)bVar10);
        param_1[lVar1 + 0x1d8800] = (fVar11 + -128.0) / 127.5;
      } while (lVar6 != 0x460);
    }
    lVar8 = lVar8 + 1;
  } while (lVar8 != 0x360);
  return;
}



/* 0013cf4c styleOutput */

/* m9::Frame::styleOutput(float const*) */

void __thiscall m9::Frame::styleOutput(Frame *this,float *param_1)

{
  long lVar1;
  runtime_error *this_00;
  long lVar2;
  long lVar3;
  float *pfVar4;
  float *pfVar5;
  float *pfVar6;
  long lVar7;
  long lVar8;
  float fVar9;
  
  lVar2 = 0;
  lVar3 = 0;
  pfVar4 = param_1 + 0x1e5a30;
  pfVar5 = param_1 + 0xf9630;
  pfVar6 = param_1 + 0xd230;
  do {
    lVar7 = -0x1000;
    lVar8 = lVar2;
    do {
      fVar9 = *(float *)((long)pfVar6 + lVar7 + 0x1000) * 127.5 + 128.0;
      if (ABS(fVar9) == INFINITY) {
LAB_0013d090:
        this_00 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013d09c to 0013d0a7 has its CatchHandler @ 0013d0cc */
        std::runtime_error::runtime_error(this_00,"Non-finite image sample");
                    /* WARNING: Subroutine does not return */
        __cxa_throw(this_00,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
      }
      fVar9 = (float)NEON_fminnm((int)fVar9,0x437f0000);
      if (fVar9 <= 0.0) {
        fVar9 = 0.0;
      }
      *(char *)(*(long *)(this + 0x40) + lVar8) = (char)(int)fVar9;
      fVar9 = *(float *)((long)pfVar5 + lVar7 + 0x1000) * 127.5 + 128.0;
      if (ABS(fVar9) == INFINITY) goto LAB_0013d090;
      fVar9 = (float)NEON_fminnm((int)fVar9,0x437f0000);
      if (fVar9 <= 0.0) {
        fVar9 = 0.0;
      }
      *(char *)(*(long *)(this + 0x40) + lVar8 + 1) = (char)(int)fVar9;
      fVar9 = *(float *)((long)pfVar4 + lVar7 + 0x1000) * 127.5 + 128.0;
      if (ABS(fVar9) == INFINITY) goto LAB_0013d090;
      lVar7 = lVar7 + 4;
      lVar1 = *(long *)(this + 0x40) + lVar8;
      lVar8 = lVar8 + 3;
      fVar9 = (float)NEON_fminnm((int)fVar9,0x437f0000);
      if (fVar9 <= 0.0) {
        fVar9 = 0.0;
      }
      *(char *)(lVar1 + 2) = (char)(int)fVar9;
    } while (lVar7 != 0);
    lVar3 = lVar3 + 1;
    pfVar4 = pfVar4 + 0x460;
    pfVar5 = pfVar5 + 0x460;
    pfVar6 = pfVar6 + 0x460;
    lVar2 = lVar2 + 0xc00;
    if (lVar3 == 0x300) {
      return;
    }
  } while( true );
}



/* 0013d0e0 tileInput */

/* m9::Frame::tileInput(int, float*) */

void __thiscall m9::Frame::tileInput(Frame *this,int param_1,float *param_2)

{
  byte *pbVar1;
  long lVar2;
  int iVar3;
  byte *pbVar4;
  float *pfVar5;
  int iVar6;
  uint uVar7;
  long lVar8;
  uint uVar9;
  long lVar10;
  uint uVar11;
  float fVar12;
  float fVar13;
  
  iVar6 = param_1 + 7;
  if (-1 < param_1) {
    iVar6 = param_1;
  }
  lVar10 = 0;
  do {
    iVar3 = (iVar6 >> 3) * 0x200 + (int)lVar10;
    uVar7 = iVar3 - 0x10;
    if (uVar7 < 0xc00) {
      lVar8 = 0;
      uVar9 = (param_1 * 0x200 + (iVar6 >> 3) * -0x1000 + -0x10010 + iVar3 * 0x1000) * 3;
      do {
        uVar11 = (param_1 % 8) * 0x200 + -0x10 + (int)lVar8;
        pfVar5 = param_2 + lVar8;
        if (uVar11 < 0x1000) {
          pbVar1 = (byte *)(*(long *)(this + 0x10) + (ulong)uVar9);
          pbVar4 = (byte *)(*(long *)(this + 0x40) +
                           (ulong)(uVar7 * 0x100 & 0xfffc00 | uVar11 >> 2) * 3);
          fVar12 = (float)NEON_ucvtf((uint)*pbVar1);
          fVar13 = (float)NEON_ucvtf((uint)*pbVar4);
          pfVar5[0xd8c00] = (fVar12 + -128.0) / 127.5;
          *pfVar5 = (fVar13 + -128.0) / 127.5;
          fVar12 = (float)NEON_ucvtf((uint)pbVar4[1]);
          fVar13 = (float)NEON_ucvtf((uint)pbVar1[1]);
          pfVar5[0x48400] = (fVar12 + -128.0) / 127.5;
          pfVar5[0x121000] = (fVar13 + -128.0) / 127.5;
          fVar13 = (float)NEON_ucvtf((uint)pbVar4[2]);
          fVar12 = (float)NEON_ucvtf((uint)pbVar1[2]);
          fVar12 = (fVar12 + -128.0) / 127.5;
          pfVar5[0x90800] = (fVar13 + -128.0) / 127.5;
        }
        else {
          fVar12 = -1.003922;
          pfVar5[0xd8c00] = -1.003922;
          pfVar5[0x121000] = -1.003922;
          *pfVar5 = -1.003922;
          pfVar5[0x48400] = -1.003922;
          pfVar5[0x90800] = -1.003922;
        }
        lVar8 = lVar8 + 1;
        uVar9 = uVar9 + 3;
        pfVar5[0x169400] = fVar12;
      } while (lVar8 != 0x220);
    }
    else {
      lVar8 = -0x880;
      do {
        lVar2 = lVar8 + 0x20;
        *(undefined8 *)((long)param_2 + lVar8 + 0x888) = 0xbf808081bf808081;
        *(undefined8 *)((long)param_2 + lVar8 + 0x880) = 0xbf808081bf808081;
        *(undefined8 *)((long)param_2 + lVar8 + 0x898) = 0xbf808081bf808081;
        *(undefined8 *)((long)param_2 + lVar8 + 0x890) = 0xbf808081bf808081;
        *(undefined8 *)((long)param_2 + lVar8 + 0x363888) = 0xbf808081bf808081;
        *(undefined8 *)((long)param_2 + lVar8 + 0x363880) = 0xbf808081bf808081;
        *(undefined8 *)((long)param_2 + lVar8 + 0x363898) = 0xbf808081bf808081;
        *(undefined8 *)((long)param_2 + lVar8 + 0x363890) = 0xbf808081bf808081;
        *(undefined8 *)((long)param_2 + (long)&fde_table_entry_00121884.data_loc + lVar8) =
             0xbf808081bf808081;
        *(undefined8 *)((long)param_2 + (long)&fde_table_entry_0012187c.data_loc + lVar8) =
             0xbf808081bf808081;
        *(undefined8 *)((long)param_2 + lVar8 + 0x121898) = 0xbf808081bf808081;
        *(undefined8 *)((long)param_2 + lVar8 + 0x121890) = 0xbf808081bf808081;
        *(undefined8 *)((long)param_2 + lVar8 + 0x484888) = 0xbf808081bf808081;
        *(undefined8 *)((long)param_2 + lVar8 + 0x484880) = 0xbf808081bf808081;
        *(undefined8 *)
         ((long)param_2 + (long)&(&fde_table_entry_00121884)[0x6c602].data_loc + lVar8) =
             0xbf808081bf808081;
        *(undefined8 *)
         ((long)param_2 + (long)&(&fde_table_entry_0012187c)[0x6c602].data_loc + lVar8) =
             0xbf808081bf808081;
        *(undefined8 *)((long)param_2 + lVar8 + 0x242888) = 0xbf808081bf808081;
        *(undefined8 *)((long)param_2 + lVar8 + 0x242880) = 0xbf808081bf808081;
        *(undefined8 *)((long)param_2 + lVar8 + 0x242898) = 0xbf808081bf808081;
        *(undefined8 *)((long)param_2 + lVar8 + 0x242890) = 0xbf808081bf808081;
        *(undefined8 *)((long)param_2 + lVar8 + 0x5a5888) = 0xbf808081bf808081;
        *(undefined8 *)((long)param_2 + lVar8 + 0x5a5880) = 0xbf808081bf808081;
        *(undefined8 *)((long)param_2 + lVar8 + 0x5a5898) = 0xbf808081bf808081;
        *(undefined8 *)((long)param_2 + lVar8 + 0x5a5890) = 0xbf808081bf808081;
        lVar8 = lVar2;
      } while (lVar2 != 0);
    }
    lVar10 = lVar10 + 1;
    param_2 = param_2 + 0x220;
  } while (lVar10 != 0x220);
  return;
}



/* 0013d314 tileOutput */

/* m9::Frame::tileOutput(int, float const*) */

void __thiscall m9::Frame::tileOutput(Frame *this,int param_1,float *param_2)

{
  long lVar1;
  runtime_error *this_00;
  long lVar2;
  int iVar3;
  float *pfVar4;
  float *pfVar5;
  float *pfVar6;
  long lVar7;
  long lVar8;
  float fVar9;
  
  iVar3 = param_1 + 7;
  if (-1 < param_1) {
    iVar3 = param_1;
  }
  lVar2 = 0;
  pfVar4 = param_2 + 0x2210;
  pfVar5 = param_2 + 0x92a10;
  pfVar6 = param_2 + 0x4a610;
  iVar3 = (iVar3 >> 3) * 0x1ff000 + param_1 * 0x200;
  do {
    lVar8 = -0x800;
    lVar7 = (long)iVar3 + (long)iVar3 * 2;
    do {
      fVar9 = *(float *)((long)pfVar4 + lVar8 + 0x800) * 127.5 + 128.0;
      if (ABS(fVar9) == INFINITY) {
LAB_0013d470:
        this_00 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013d47c to 0013d487 has its CatchHandler @ 0013d4ac */
        std::runtime_error::runtime_error(this_00,"Non-finite image sample");
                    /* WARNING: Subroutine does not return */
        __cxa_throw(this_00,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
      }
      fVar9 = (float)NEON_fminnm((int)fVar9,0x437f0000);
      if (fVar9 <= 0.0) {
        fVar9 = 0.0;
      }
      *(char *)(*(long *)(this + 0x58) + lVar7) = (char)(int)fVar9;
      fVar9 = *(float *)((long)pfVar6 + lVar8 + 0x800) * 127.5 + 128.0;
      if (ABS(fVar9) == INFINITY) goto LAB_0013d470;
      fVar9 = (float)NEON_fminnm((int)fVar9,0x437f0000);
      if (fVar9 <= 0.0) {
        fVar9 = 0.0;
      }
      *(char *)(*(long *)(this + 0x58) + lVar7 + 1) = (char)(int)fVar9;
      fVar9 = *(float *)((long)pfVar5 + lVar8 + 0x800) * 127.5 + 128.0;
      if (ABS(fVar9) == INFINITY) goto LAB_0013d470;
      lVar8 = lVar8 + 4;
      lVar1 = *(long *)(this + 0x58) + lVar7;
      lVar7 = lVar7 + 3;
      fVar9 = (float)NEON_fminnm((int)fVar9,0x437f0000);
      if (fVar9 <= 0.0) {
        fVar9 = 0.0;
      }
      *(char *)(lVar1 + 2) = (char)(int)fVar9;
    } while (lVar8 != 0);
    lVar2 = lVar2 + 1;
    pfVar5 = pfVar5 + 0x220;
    pfVar6 = pfVar6 + 0x220;
    pfVar4 = pfVar4 + 0x220;
    iVar3 = iVar3 + 0x1000;
    if (lVar2 == 0x200) {
      return;
    }
  } while( true );
}



/* 0013d4c0 leicaPixel */

/* m9::leicaPixel(unsigned char const*, unsigned char const*, float const*, int, int, int, int,
   float*) */

void m9::leicaPixel(uchar *param_1,uchar *param_2,float *param_3,int param_4,int param_5,int param_6
                   ,int param_7,float *param_8)

{
  long lVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  byte bVar9;
  byte bVar10;
  float fVar11;
  float fVar12;
  undefined8 uVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  
  bVar10 = *param_1;
  *param_8 = 0.0;
  bVar9 = param_1[1];
  param_8[1] = 0.0;
  fVar11 = (float)NEON_ucvtf((uint)bVar10);
  fVar12 = (float)NEON_ucvtf((uint)bVar9);
  fVar14 = (float)NEON_ucvtf((uint)param_1[2]);
  param_8[2] = 0.0;
  fVar11 = (fVar11 / 255.0) * 16.0;
  iVar8 = (int)fVar11;
  fVar12 = (fVar12 / 255.0) * 16.0;
  iVar5 = (int)fVar12;
  if (0xe < iVar5) {
    iVar5 = 0xf;
  }
  fVar14 = (fVar14 / 255.0) * 16.0;
  iVar6 = (int)fVar14;
  fVar12 = fVar12 - (float)iVar5;
  if (0xe < iVar6) {
    iVar6 = 0xf;
  }
  if (0xe < iVar8) {
    iVar8 = 0xf;
  }
  iVar4 = iVar8 * 0x11;
  iVar7 = (iVar5 + iVar4) * 0x11;
  fVar11 = fVar11 - (float)iVar8;
  fVar14 = fVar14 - (float)iVar6;
  iVar8 = iVar6 + iVar7;
  lVar1 = (long)iVar8 + (long)iVar8 * 2;
  fVar15 = 1.0 - fVar14;
  iVar8 = (int)lVar1;
  fVar18 = (1.0 - fVar11) * (1.0 - fVar12);
  fVar17 = (1.0 - fVar11) * fVar12;
  fVar16 = fVar11 * (1.0 - fVar12);
  fVar19 = (float)NEON_ucvtf((uint)param_2[(long)iVar8 + 2]);
  fVar21 = fVar18 * fVar15;
  fVar18 = fVar18 * fVar14;
  fVar20 = (fVar21 * fVar19) / 255.0 + 0.0;
  *param_8 = fVar20;
  fVar19 = (float)NEON_ucvtf((uint)param_2[iVar8 + 1]);
  fVar22 = (fVar21 * fVar19) / 255.0 + 0.0;
  param_8[1] = fVar22;
  iVar8 = iVar6 + 1;
  iVar7 = iVar8 + iVar7;
  fVar19 = (float)NEON_ucvtf((uint)param_2[lVar1]);
  lVar1 = (long)iVar7 + (long)iVar7 * 2;
  iVar7 = (int)lVar1;
  fVar19 = (fVar21 * fVar19) / 255.0 + 0.0;
  param_8[2] = fVar19;
  fVar21 = (float)NEON_ucvtf((uint)param_2[(long)iVar7 + 2]);
  fVar20 = fVar20 + (fVar18 * fVar21) / 255.0;
  *param_8 = fVar20;
  fVar21 = (float)NEON_ucvtf((uint)param_2[iVar7 + 1]);
  fVar22 = fVar22 + (fVar18 * fVar21) / 255.0;
  param_8[1] = fVar22;
  fVar21 = (float)NEON_ucvtf((uint)param_2[lVar1]);
  iVar2 = (iVar5 + 1 + iVar4) * 0x11;
  iVar3 = (iVar5 + iVar4 + 0x11) * 0x11;
  iVar7 = iVar6 + iVar2;
  iVar2 = iVar8 + iVar2;
  fVar23 = fVar17 * fVar15;
  lVar1 = (long)iVar7 + (long)iVar7 * 2;
  fVar17 = fVar17 * fVar14;
  iVar7 = (int)lVar1;
  fVar19 = fVar19 + (fVar18 * fVar21) / 255.0;
  param_8[2] = fVar19;
  fVar18 = (float)NEON_ucvtf((uint)param_2[(long)iVar7 + 2]);
  fVar20 = fVar20 + (fVar23 * fVar18) / 255.0;
  *param_8 = fVar20;
  fVar18 = (float)NEON_ucvtf((uint)param_2[iVar7 + 1]);
  fVar22 = fVar22 + (fVar23 * fVar18) / 255.0;
  param_8[1] = fVar22;
  fVar18 = (float)NEON_ucvtf((uint)param_2[lVar1]);
  lVar1 = (long)iVar2 + (long)iVar2 * 2;
  iVar7 = (int)lVar1;
  fVar19 = fVar19 + (fVar23 * fVar18) / 255.0;
  param_8[2] = fVar19;
  fVar18 = (float)NEON_ucvtf((uint)param_2[(long)iVar7 + 2]);
  fVar20 = fVar20 + (fVar17 * fVar18) / 255.0;
  *param_8 = fVar20;
  fVar18 = (float)NEON_ucvtf((uint)param_2[iVar7 + 1]);
  fVar22 = fVar22 + (fVar17 * fVar18) / 255.0;
  param_8[1] = fVar22;
  iVar7 = iVar6 + iVar3;
  iVar3 = iVar8 + iVar3;
  fVar18 = (float)NEON_ucvtf((uint)param_2[lVar1]);
  lVar1 = (long)iVar7 + (long)iVar7 * 2;
  iVar7 = (int)lVar1;
  fVar21 = fVar16 * fVar15;
  fVar16 = fVar16 * fVar14;
  fVar15 = fVar11 * fVar12 * fVar15;
  fVar14 = fVar11 * fVar12 * fVar14;
  fVar19 = fVar19 + (fVar17 * fVar18) / 255.0;
  param_8[2] = fVar19;
  fVar11 = (float)NEON_ucvtf((uint)param_2[(long)iVar7 + 2]);
  fVar20 = fVar20 + (fVar21 * fVar11) / 255.0;
  *param_8 = fVar20;
  fVar11 = (float)NEON_ucvtf((uint)param_2[iVar7 + 1]);
  fVar22 = fVar22 + (fVar21 * fVar11) / 255.0;
  param_8[1] = fVar22;
  fVar11 = (float)NEON_ucvtf((uint)param_2[lVar1]);
  lVar1 = (long)iVar3 + (long)iVar3 * 2;
  iVar7 = (int)lVar1;
  fVar19 = fVar19 + (fVar21 * fVar11) / 255.0;
  param_8[2] = fVar19;
  fVar11 = (float)NEON_ucvtf((uint)param_2[(long)iVar7 + 2]);
  fVar20 = fVar20 + (fVar16 * fVar11) / 255.0;
  *param_8 = fVar20;
  fVar11 = (float)NEON_ucvtf((uint)param_2[iVar7 + 1]);
  fVar22 = fVar22 + (fVar16 * fVar11) / 255.0;
  param_8[1] = fVar22;
  iVar5 = (iVar5 + 1 + iVar4 + 0x11) * 0x11;
  fVar11 = (float)NEON_ucvtf((uint)param_2[lVar1]);
  iVar6 = iVar6 + iVar5;
  lVar1 = (long)iVar6 + (long)iVar6 * 2;
  iVar6 = (int)lVar1;
  fVar19 = fVar19 + (fVar16 * fVar11) / 255.0;
  param_8[2] = fVar19;
  fVar11 = (float)NEON_ucvtf((uint)param_2[(long)iVar6 + 2]);
  fVar20 = fVar20 + (fVar15 * fVar11) / 255.0;
  *param_8 = fVar20;
  fVar11 = (float)NEON_ucvtf((uint)param_2[iVar6 + 1]);
  fVar22 = fVar22 + (fVar15 * fVar11) / 255.0;
  param_8[1] = fVar22;
  iVar8 = iVar8 + iVar5;
  fVar11 = (float)NEON_ucvtf((uint)param_2[lVar1]);
  lVar1 = (long)iVar8 + (long)iVar8 * 2;
  iVar5 = (int)lVar1;
  fVar19 = fVar19 + (fVar15 * fVar11) / 255.0;
  param_8[2] = fVar19;
  fVar11 = (float)NEON_ucvtf((uint)param_2[(long)iVar5 + 2]);
  fVar20 = fVar20 + (fVar14 * fVar11) / 255.0;
  *param_8 = fVar20;
  fVar11 = (float)NEON_ucvtf((uint)param_2[iVar5 + 1]);
  fVar22 = fVar22 + (fVar14 * fVar11) / 255.0;
  param_8[1] = fVar22;
  fVar11 = (float)NEON_ucvtf((uint)param_2[lVar1]);
  fVar12 = ((((float)param_4 + 0.5) / (float)param_6 + -0.5) * (float)param_6) / (float)param_7 +
           0.5 + -0.5;
  fVar15 = ((float)param_5 + 0.5) / (float)param_7 + -0.5;
  fVar19 = fVar19 + (fVar14 * fVar11) / 255.0;
  param_8[2] = fVar19;
  fVar11 = sinf((fVar15 + -0.5) * 78.233 + (fVar12 + -0.5) * 12.9898);
  fVar14 = param_3[6];
  fVar11 = (float)NEON_fminnm(((SQRT(fVar15 * fVar15 + fVar12 * fVar12) +
                               (fVar11 * 43758.55 - (float)(int)(fVar11 * 43758.55)) * 0.04 *
                               param_3[2]) - *param_3) / (param_3[1] - *param_3),0x3f800000);
  if (fVar11 <= 0.0) {
    fVar11 = 0.0;
  }
  fVar12 = expf(param_3[4] * (param_3[5] - (fVar20 * 0.499 + fVar22 * 0.387 + fVar19 * 0.114)));
  uVar13 = NEON_fmov(0x3f800000,4);
  fVar12 = param_3[7] + fVar14 / (fVar12 + 1.0);
  fVar11 = (fVar20 * 0.299 + fVar22 * 0.587 + fVar19 * 0.114) *
           (param_3[3] * (fVar12 + fVar11 * fVar11 * (3.0 - (fVar11 + fVar11)) * (1.0 - fVar12)) +
           -1.0);
  fVar12 = (float)NEON_fminnm(fVar11 + fVar19,0x3f800000);
  uVar13 = NEON_fminnm(CONCAT44(fVar11 + fVar22,fVar11 + fVar20),uVar13,4);
  if (fVar12 <= 0.0) {
    fVar12 = 0.0;
  }
  uVar13 = NEON_fmaxnm(uVar13,0,4);
  *(undefined8 *)param_8 = uVar13;
  param_8[2] = fVar12;
  return;
}



/* 0013daa0 RawApi */

/* RawApi::RawApi() */

void __thiscall RawApi::RawApi(RawApi *this)

{
  long lVar1;
  runtime_error *this_00;
  
  lVar1 = dlopen("libzxwdecoder.so",2);
  *(long *)this = lVar1;
  if (lVar1 != 0) {
    get<void*(*)(unsigned_int)>(this,(_func_void_ptr_uint *)(this + 8),"libraw_init");
    get<int(*)(void*,void_const*,unsigned_long)>
              (this,(_func_int_void_ptr_void_ptr_ulong *)(this + 0x10),"libraw_open_buffer");
    get<int(*)(void*)>(this,(_func_int_void_ptr *)(this + 0x18),"libraw_unpack");
    get<int(*)(void*)>(this,(_func_int_void_ptr *)(this + 0x20),"libraw_dcraw_process");
    get<MemImage*(*)(void*,int*)>
              (this,(_func_MemImage_ptr_void_ptr_int_ptr *)(this + 0x28),
               "libraw_dcraw_make_mem_image");
    get<void(*)(MemImage*)>(this,(_func_void_MemImage_ptr *)(this + 0x30),"libraw_dcraw_clear_mem");
    get<void(*)(void*)>(this,(_func_void_void_ptr *)(this + 0x38),"libraw_close");
    get<void(*)(void*,int,float)>
              (this,(_func_void_void_ptr_int_float *)(this + 0x40),"libraw_set_gamma");
    get<void(*)(void*,int,float)>
              (this,(_func_void_void_ptr_int_float *)(this + 0x48),"libraw_set_user_mul");
    get<void(*)(void*,int)>(this,(_func_void_void_ptr_int *)(this + 0x50),"libraw_set_output_bps");
    get<void(*)(void*,int)>(this,(_func_void_void_ptr_int *)(this + 0x58),"libraw_set_output_color")
    ;
    get<void(*)(void*,int)>(this,(_func_void_void_ptr_int *)(this + 0x60),"libraw_set_demosaic");
    get<void(*)(void*,int)>
              (this,(_func_void_void_ptr_int *)(this + 0x68),"libraw_set_no_auto_bright");
    get<void(*)(void*,int)>(this,(_func_void_void_ptr_int *)(this + 0x70),"libraw_set_highlight");
    get<float(*)(void*,int)>(this,(_func_float_void_ptr_int *)(this + 0x78),"libraw_get_cam_mul");
    return;
  }
  this_00 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013dc08 to 0013dc13 has its CatchHandler @ 0013dc2c */
  std::runtime_error::runtime_error(this_00,"Original RAW decoder unavailable");
                    /* WARNING: Subroutine does not return */
  __cxa_throw(this_00,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
}



/* 0013dc40 ~unique_ptr[abi:ne180000] */

/* std::__ndk1::unique_ptr<m9::Raw, std::__ndk1::default_delete<m9::Raw>
   >::~unique_ptr[abi:ne180000]() */

void __thiscall
std::__ndk1::unique_ptr<m9::Raw,std::__ndk1::default_delete<m9::Raw>>::~unique_ptr_abi_ne180000_
          (unique_ptr<m9::Raw,std::__ndk1::default_delete<m9::Raw>> *this)

{
  void *pvVar1;
  void *pvVar2;
  
  pvVar2 = *(void **)this;
  *(undefined8 *)this = 0;
  if (pvVar2 != (void *)0x0) {
    pvVar1 = *(void **)((long)pvVar2 + 0x20);
    if (pvVar1 != (void *)0x0) {
      *(void **)((long)pvVar2 + 0x28) = pvVar1;
      operator_delete(pvVar1);
    }
    pvVar1 = *(void **)((long)pvVar2 + 8);
    if (pvVar1 != (void *)0x0) {
      *(void **)((long)pvVar2 + 0x10) = pvVar1;
      operator_delete(pvVar1);
    }
    operator_delete(pvVar2);
    return;
  }
  return;
}



/* 0013dc94 gainmap */

/* m9::gainmap(m9::Raw const&, m9::Ipe const&, int, int, unsigned char*) */

void m9::gainmap(Raw *param_1,Ipe *param_2,int param_3,int param_4,uchar *param_5)

{
  long lVar1;
  int iVar2;
  ushort *puVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  void *__s;
  void *__s_00;
  void *__s_01;
  runtime_error *prVar10;
  uint uVar11;
  ulong uVar12;
  ulong uVar13;
  ulong uVar14;
  int iVar15;
  long lVar16;
  ulong uVar17;
  int iVar18;
  ulong uVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  int local_c4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  undefined8 local_90;
  
  uVar12 = (ulong)*(uint *)param_1;
  if (((0 < (int)*(uint *)param_1) && (0 < param_4)) && (0 < param_3)) {
    uVar11 = *(uint *)(param_1 + 4);
    uVar13 = (ulong)uVar11;
    if (0 < (int)uVar11) {
      uVar19 = uVar12 + 1 >> 1;
      uVar14 = uVar13 + 1 >> 1;
      __s = operator_new(uVar11 * uVar12);
      memset(__s,0,uVar11 * uVar12);
      uVar17 = uVar14 * uVar19;
                    /* try { // try from 0013dd28 to 0013dd2f has its CatchHandler @ 0013e510 */
      __s_00 = operator_new(uVar17);
      memset(__s_00,0,uVar17);
                    /* try { // try from 0013dd44 to 0013dd4b has its CatchHandler @ 0013e4ec */
      __s_01 = operator_new(uVar17);
      memset(__s_01,0,uVar17);
      uVar11 = 0;
      uVar17 = 0;
      local_c4 = 1;
      do {
        if (0 < (int)uVar12) {
          uVar13 = 0;
          lVar16 = 0;
          do {
            if ((long)uVar17 < (long)*(int *)(param_1 + 4)) {
              iVar15 = (int)lVar16;
              if (lVar16 < (int)uVar12) {
                iVar18 = iVar15 + (int)uVar17 * (int)uVar12;
                lVar1 = (long)iVar18 + (long)iVar18 * 2;
                if (*(long *)(param_1 + 0x20) == *(long *)(param_1 + 0x28)) {
                  pfVar4 = (float *)(*(long *)(param_1 + 8) + lVar1 * 4);
                  local_a0 = *pfVar4;
                  local_9c = pfVar4[1];
                  local_98 = pfVar4[2];
                }
                else {
                  puVar3 = (ushort *)(*(long *)(param_1 + 0x20) + lVar1 * 2);
                  local_a0 = (float)NEON_ucvtf((uint)*puVar3);
                  local_a0 = local_a0 / 65535.0;
                  local_9c = (float)NEON_ucvtf((uint)puVar3[1]);
                  local_9c = local_9c / 65535.0;
                  local_98 = (float)NEON_ucvtf((uint)puVar3[2]);
                  local_98 = local_98 / 65535.0;
                }
                    /* try { // try from 0013ded0 to 0013dedf has its CatchHandler @ 0013e570 */
                Ipe::yuv(param_2,&local_a0,&local_94);
                fVar21 = ABS(local_94 * 255.0);
                if ((INFINITY <= fVar21) && (fVar21 <= INFINITY)) goto LAB_0013df04;
                iVar7 = *(int *)param_1;
                fVar20 = (float)NEON_fminnm((int)(local_94 * 255.0),0x437f0000);
                fVar21 = (float)local_90 + 0.0;
                fVar22 = (float)((ulong)local_90 >> 0x20) + 0.0;
                if (fVar20 <= 0.0) {
                  fVar20 = 0.0;
                }
                *(char *)((long)__s + (long)iVar18) = (char)(int)fVar20;
                if (lVar16 + 1 < (long)iVar7) {
                  iVar7 = iVar15 + (int)uVar17 * iVar7 + 1;
                  lVar1 = (long)iVar7 + (long)iVar7 * 2;
                  if (*(long *)(param_1 + 0x20) == *(long *)(param_1 + 0x28)) {
                    pfVar4 = (float *)(*(long *)(param_1 + 8) + lVar1 * 4);
                    local_a0 = *pfVar4;
                    local_9c = pfVar4[1];
                    local_98 = pfVar4[2];
                  }
                  else {
                    puVar3 = (ushort *)(*(long *)(param_1 + 0x20) + lVar1 * 2);
                    local_a0 = (float)NEON_ucvtf((uint)*puVar3);
                    local_a0 = local_a0 / 65535.0;
                    local_9c = (float)NEON_ucvtf((uint)puVar3[1]);
                    local_9c = local_9c / 65535.0;
                    local_98 = (float)NEON_ucvtf((uint)puVar3[2]);
                    local_98 = local_98 / 65535.0;
                  }
                    /* try { // try from 0013dfec to 0013e0f3 has its CatchHandler @ 0013e570 */
                  Ipe::yuv(param_2,&local_a0,&local_94);
                  if (ABS(local_94 * 255.0) == INFINITY) goto LAB_0013df04;
                  iVar18 = 2;
                  fVar20 = (float)NEON_fminnm((int)(local_94 * 255.0),0x437f0000);
                  fVar21 = fVar21 + (float)local_90;
                  fVar22 = fVar22 + (float)((ulong)local_90 >> 0x20);
                  if (fVar20 <= 0.0) {
                    fVar20 = 0.0;
                  }
                  *(char *)((long)__s + (long)iVar7) = (char)(int)fVar20;
                  iVar7 = *(int *)(param_1 + 4);
                }
                else {
                  iVar18 = 1;
                  iVar7 = *(int *)(param_1 + 4);
                }
              }
              else {
                fVar21 = 0.0;
                fVar22 = 0.0;
                iVar18 = 0;
                iVar7 = *(int *)(param_1 + 4);
              }
              if (((long)(uVar17 | 1) < (long)iVar7) && (lVar16 < *(int *)param_1)) {
                iVar7 = iVar15 + local_c4 * *(int *)param_1;
                lVar1 = (long)iVar7 + (long)iVar7 * 2;
                if (*(long *)(param_1 + 0x20) == *(long *)(param_1 + 0x28)) {
                  pfVar4 = (float *)(*(long *)(param_1 + 8) + lVar1 * 4);
                  local_a0 = *pfVar4;
                  local_9c = pfVar4[1];
                  local_98 = pfVar4[2];
                }
                else {
                  puVar3 = (ushort *)(*(long *)(param_1 + 0x20) + lVar1 * 2);
                  local_a0 = (float)NEON_ucvtf((uint)*puVar3);
                  local_a0 = local_a0 / 65535.0;
                  local_9c = (float)NEON_ucvtf((uint)puVar3[1]);
                  local_9c = local_9c / 65535.0;
                  local_98 = (float)NEON_ucvtf((uint)puVar3[2]);
                  local_98 = local_98 / 65535.0;
                }
                Ipe::yuv(param_2,&local_a0,&local_94);
                if (ABS(local_94 * 255.0) == INFINITY) {
LAB_0013df04:
                  prVar10 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013df10 to 0013df1f has its CatchHandler @ 0013e560 */
                  std::runtime_error::runtime_error(prVar10,"Non-finite image sample");
                    /* try { // try from 0013e468 to 0013e483 has its CatchHandler @ 0013e558 */
                    /* WARNING: Subroutine does not return */
                  __cxa_throw(prVar10,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
                }
                iVar8 = *(int *)param_1;
                fVar20 = (float)NEON_fminnm((int)(local_94 * 255.0),0x437f0000);
                fVar21 = fVar21 + (float)local_90;
                fVar22 = fVar22 + (float)((ulong)local_90 >> 0x20);
                if (fVar20 <= 0.0) {
                  fVar20 = 0.0;
                }
                *(char *)((long)__s + (long)iVar7) = (char)(int)fVar20;
                if (lVar16 + 1 < (long)iVar8) {
                  iVar15 = iVar15 + local_c4 * iVar8 + 1;
                  lVar1 = (long)iVar15 + (long)iVar15 * 2;
                  if (*(long *)(param_1 + 0x20) == *(long *)(param_1 + 0x28)) {
                    pfVar4 = (float *)(*(long *)(param_1 + 8) + lVar1 * 4);
                    local_a0 = *pfVar4;
                    local_9c = pfVar4[1];
                    local_98 = pfVar4[2];
                  }
                  else {
                    puVar3 = (ushort *)(*(long *)(param_1 + 0x20) + lVar1 * 2);
                    local_a0 = (float)NEON_ucvtf((uint)*puVar3);
                    local_a0 = local_a0 / 65535.0;
                    local_9c = (float)NEON_ucvtf((uint)puVar3[1]);
                    local_9c = local_9c / 65535.0;
                    local_98 = (float)NEON_ucvtf((uint)puVar3[2]);
                    local_98 = local_98 / 65535.0;
                  }
                    /* try { // try from 0013e26c to 0013e27b has its CatchHandler @ 0013e570 */
                  Ipe::yuv(param_2,&local_a0,&local_94);
                  if (ABS(local_94 * 255.0) == INFINITY) goto LAB_0013df04;
                  iVar18 = iVar18 + 2;
                  fVar20 = (float)NEON_fminnm((int)(local_94 * 255.0),0x437f0000);
                  fVar21 = fVar21 + (float)local_90;
                  fVar22 = fVar22 + (float)((ulong)local_90 >> 0x20);
                  if (fVar20 <= 0.0) {
                    fVar20 = 0.0;
                  }
                  *(char *)((long)__s + (long)iVar15) = (char)(int)fVar20;
                }
                else {
                  iVar18 = iVar18 + 1;
                }
              }
            }
            else {
              fVar21 = 0.0;
              fVar22 = 0.0;
              iVar18 = 0;
            }
            if ((uVar17 >> 1 < uVar14) && (uVar13 < uVar19)) {
              fVar21 = (fVar21 / (float)iVar18) * 255.0 + 128.0;
              fVar20 = ABS(fVar21);
              if ((INFINITY <= fVar20) && (fVar20 <= INFINITY)) {
                prVar10 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013e490 to 0013e49b has its CatchHandler @ 0013e540 */
                std::runtime_error::runtime_error(prVar10,"Non-finite image sample");
LAB_0013e49c:
                    /* try { // try from 0013e4a4 to 0013e4bb has its CatchHandler @ 0013e550 */
                    /* WARNING: Subroutine does not return */
                __cxa_throw(prVar10,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
              }
              fVar21 = (float)NEON_fminnm((int)fVar21,0x437f0000);
              if (fVar21 <= 0.0) {
                fVar21 = 0.0;
              }
              *(char *)((long)__s_00 + uVar13 + uVar11) = (char)(int)fVar21;
              fVar21 = (fVar22 / (float)iVar18) * 255.0 + 128.0;
              fVar22 = ABS(fVar21);
              if ((INFINITY <= fVar22) && (fVar22 <= INFINITY)) {
                prVar10 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013e23c to 0013e247 has its CatchHandler @ 0013e53c */
                std::runtime_error::runtime_error(prVar10,"Non-finite image sample");
                goto LAB_0013e49c;
              }
              fVar21 = (float)NEON_fminnm((int)fVar21,0x437f0000);
              if (fVar21 <= 0.0) {
                fVar21 = 0.0;
              }
              *(char *)((long)__s_01 + uVar13 + uVar11) = (char)(int)fVar21;
            }
            uVar12 = (ulong)*(uint *)param_1;
            lVar16 = lVar16 + 2;
            uVar13 = uVar13 + 1;
          } while ((int)lVar16 < (int)*(uint *)param_1);
          uVar13 = (ulong)*(uint *)(param_1 + 4);
        }
        uVar17 = uVar17 + 2;
        iVar18 = (int)uVar19;
        uVar11 = uVar11 + iVar18;
        local_c4 = local_c4 + 2;
        if ((int)uVar13 <= (int)uVar17) {
          if ((0 < param_4) && (0 < param_3)) {
            uVar11 = 0;
            uVar12 = 0;
            uVar13 = (ulong)(uint)param_4;
            uVar17 = (ulong)(uint)param_3;
            iVar15 = (int)uVar14 + -1;
            do {
              uVar14 = 0;
              do {
                iVar8 = *(int *)param_1;
                iVar7 = 0;
                if (uVar17 != 0) {
                  iVar7 = (int)(((long)(int)((uint)uVar14 & 0x7ffffffe) * (long)iVar8) /
                               (long)uVar17);
                }
                iVar5 = 0;
                if (uVar13 != 0) {
                  iVar5 = (int)((long)(uVar12 * (long)*(int *)(param_1 + 8)) / (long)uVar13);
                }
                iVar2 = ((uint)uVar14 & 1) + iVar7;
                iVar6 = iVar8 + -1;
                if (iVar2 <= iVar8 + -1) {
                  iVar6 = iVar2;
                }
                iVar8 = iVar8 * iVar5;
                if (iVar5 < 0) {
                  iVar5 = iVar5 + 1;
                }
                iVar2 = iVar15;
                if (iVar5 >> 1 <= iVar15) {
                  iVar2 = iVar5 >> 1;
                }
                if (iVar7 < 0) {
                  iVar7 = iVar7 + 1;
                }
                iVar5 = iVar18 + -1;
                if (iVar7 >> 1 <= iVar18 + -1) {
                  iVar5 = iVar7 >> 1;
                }
                iVar5 = iVar5 + iVar2 * iVar18;
                iVar7 = *(byte *)((long)__s_01 + (long)iVar5) - 0x80;
                iVar2 = *(byte *)((long)__s_00 + (long)iVar5) - 0x80;
                iVar5 = iVar7 * 0x167;
                iVar9 = iVar2 * 0x1c6;
                iVar2 = iVar2 * -0x58 + iVar7 * -0xb7;
                iVar7 = iVar9;
                if (iVar9 <= iVar2) {
                  iVar7 = iVar2;
                }
                iVar2 = (iVar5 + iVar9 + iVar2 >> 8) * 0x5556;
                if (iVar5 <= iVar7) {
                  iVar5 = iVar7;
                }
                iVar7 = iVar5 >> 8;
                if (iVar5 < 1) {
                  iVar7 = 0;
                }
                fVar21 = (float)NEON_fminnm((float)((uint)*(byte *)((long)__s +
                                                                   (long)(iVar6 + iVar8)) +
                                                   (((iVar2 >> 0x10) - (iVar2 >> 0x1f)) + iVar7 >> 1
                                                   )),0x437f0000);
                if (fVar21 <= 0.0) {
                  fVar21 = 0.0;
                }
                param_5[uVar14 + uVar11] = (uchar)(int)fVar21;
                uVar14 = uVar14 + 1;
              } while (uVar17 != uVar14);
              uVar12 = uVar12 + 1;
              uVar11 = uVar11 + param_3;
            } while (uVar12 != uVar13);
          }
          operator_delete(__s_01);
          operator_delete(__s_00);
          operator_delete(__s);
          return;
        }
      } while( true );
    }
  }
  prVar10 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013e4c8 to 0013e4d3 has its CatchHandler @ 0013e528 */
  std::runtime_error::runtime_error(prVar10,"Gain map dimensions");
                    /* WARNING: Subroutine does not return */
  __cxa_throw(prVar10,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
}



/* 0013e59c get<void*(*)(unsigned_int)> */

/* void RawApi::get<void* (*)(unsigned int)>(void* (*&)(unsigned int), char const*) */

void __thiscall
RawApi::get<void*(*)(unsigned_int)>(RawApi *this,_func_void_ptr_uint *param_1,char *param_2)

{
  long lVar1;
  runtime_error *this_00;
  undefined8 *puVar2;
  basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>> abStack_68 [24];
  undefined8 local_50;
  undefined8 uStack_48;
  undefined8 local_40;
  
  lVar1 = dlsym(*(undefined8 *)this,param_2);
  *(long *)param_1 = lVar1;
  if (lVar1 != 0) {
    return;
  }
  this_00 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013e5ec to 0013e5fb has its CatchHandler @ 0013e698 */
  _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2B8ne180000ILi0EEEPKc
            (abStack_68,"RAW ABI missing ");
                    /* try { // try from 0013e5fc to 0013e607 has its CatchHandler @ 0013e680 */
  puVar2 = (undefined8 *)
           std::__ndk1::
           basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>::append
                     (abStack_68,param_2);
  local_40 = puVar2[2];
  uStack_48 = puVar2[1];
  local_50 = *puVar2;
  puVar2[1] = 0;
  puVar2[2] = 0;
  *puVar2 = 0;
                    /* try { // try from 0013e624 to 0013e64b has its CatchHandler @ 0013e64c */
  std::runtime_error::runtime_error(this_00,(basic_string *)&local_50);
                    /* WARNING: Subroutine does not return */
  __cxa_throw(this_00,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
}



/* 0013e6ac get<int(*)(void*,void_const*,unsigned_long)> */

/* void RawApi::get<int (*)(void*, void const*, unsigned long)>(int (*&)(void*, void const*,
   unsigned long), char const*) */

void __thiscall
RawApi::get<int(*)(void*,void_const*,unsigned_long)>
          (RawApi *this,_func_int_void_ptr_void_ptr_ulong *param_1,char *param_2)

{
  long lVar1;
  runtime_error *this_00;
  undefined8 *puVar2;
  basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>> abStack_68 [24];
  undefined8 local_50;
  undefined8 uStack_48;
  undefined8 local_40;
  
  lVar1 = dlsym(*(undefined8 *)this,param_2);
  *(long *)param_1 = lVar1;
  if (lVar1 != 0) {
    return;
  }
  this_00 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013e6fc to 0013e70b has its CatchHandler @ 0013e7a8 */
  _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2B8ne180000ILi0EEEPKc
            (abStack_68,"RAW ABI missing ");
                    /* try { // try from 0013e70c to 0013e717 has its CatchHandler @ 0013e790 */
  puVar2 = (undefined8 *)
           std::__ndk1::
           basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>::append
                     (abStack_68,param_2);
  local_40 = puVar2[2];
  uStack_48 = puVar2[1];
  local_50 = *puVar2;
  puVar2[1] = 0;
  puVar2[2] = 0;
  *puVar2 = 0;
                    /* try { // try from 0013e734 to 0013e75b has its CatchHandler @ 0013e75c */
  std::runtime_error::runtime_error(this_00,(basic_string *)&local_50);
                    /* WARNING: Subroutine does not return */
  __cxa_throw(this_00,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
}



/* 0013e7bc get<int(*)(void*)> */

/* void RawApi::get<int (*)(void*)>(int (*&)(void*), char const*) */

void __thiscall RawApi::get<int(*)(void*)>(RawApi *this,_func_int_void_ptr *param_1,char *param_2)

{
  long lVar1;
  runtime_error *this_00;
  undefined8 *puVar2;
  basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>> abStack_68 [24];
  undefined8 local_50;
  undefined8 uStack_48;
  undefined8 local_40;
  
  lVar1 = dlsym(*(undefined8 *)this,param_2);
  *(long *)param_1 = lVar1;
  if (lVar1 != 0) {
    return;
  }
  this_00 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013e80c to 0013e81b has its CatchHandler @ 0013e8b8 */
  _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2B8ne180000ILi0EEEPKc
            (abStack_68,"RAW ABI missing ");
                    /* try { // try from 0013e81c to 0013e827 has its CatchHandler @ 0013e8a0 */
  puVar2 = (undefined8 *)
           std::__ndk1::
           basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>::append
                     (abStack_68,param_2);
  local_40 = puVar2[2];
  uStack_48 = puVar2[1];
  local_50 = *puVar2;
  puVar2[1] = 0;
  puVar2[2] = 0;
  *puVar2 = 0;
                    /* try { // try from 0013e844 to 0013e86b has its CatchHandler @ 0013e86c */
  std::runtime_error::runtime_error(this_00,(basic_string *)&local_50);
                    /* WARNING: Subroutine does not return */
  __cxa_throw(this_00,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
}



/* 0013e8cc get<MemImage*(*)(void*,int*)> */

/* void RawApi::get<MemImage* (*)(void*, int*)>(MemImage* (*&)(void*, int*), char const*) */

void __thiscall
RawApi::get<MemImage*(*)(void*,int*)>
          (RawApi *this,_func_MemImage_ptr_void_ptr_int_ptr *param_1,char *param_2)

{
  long lVar1;
  runtime_error *this_00;
  undefined8 *puVar2;
  basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>> abStack_68 [24];
  undefined8 local_50;
  undefined8 uStack_48;
  undefined8 local_40;
  
  lVar1 = dlsym(*(undefined8 *)this,param_2);
  *(long *)param_1 = lVar1;
  if (lVar1 != 0) {
    return;
  }
  this_00 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013e91c to 0013e92b has its CatchHandler @ 0013e9c8 */
  _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2B8ne180000ILi0EEEPKc
            (abStack_68,"RAW ABI missing ");
                    /* try { // try from 0013e92c to 0013e937 has its CatchHandler @ 0013e9b0 */
  puVar2 = (undefined8 *)
           std::__ndk1::
           basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>::append
                     (abStack_68,param_2);
  local_40 = puVar2[2];
  uStack_48 = puVar2[1];
  local_50 = *puVar2;
  puVar2[1] = 0;
  puVar2[2] = 0;
  *puVar2 = 0;
                    /* try { // try from 0013e954 to 0013e97b has its CatchHandler @ 0013e97c */
  std::runtime_error::runtime_error(this_00,(basic_string *)&local_50);
                    /* WARNING: Subroutine does not return */
  __cxa_throw(this_00,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
}



/* 0013e9dc get<void(*)(MemImage*)> */

/* void RawApi::get<void (*)(MemImage*)>(void (*&)(MemImage*), char const*) */

void __thiscall
RawApi::get<void(*)(MemImage*)>(RawApi *this,_func_void_MemImage_ptr *param_1,char *param_2)

{
  long lVar1;
  runtime_error *this_00;
  undefined8 *puVar2;
  basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>> abStack_68 [24];
  undefined8 local_50;
  undefined8 uStack_48;
  undefined8 local_40;
  
  lVar1 = dlsym(*(undefined8 *)this,param_2);
  *(long *)param_1 = lVar1;
  if (lVar1 != 0) {
    return;
  }
  this_00 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013ea2c to 0013ea3b has its CatchHandler @ 0013ead8 */
  _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2B8ne180000ILi0EEEPKc
            (abStack_68,"RAW ABI missing ");
                    /* try { // try from 0013ea3c to 0013ea47 has its CatchHandler @ 0013eac0 */
  puVar2 = (undefined8 *)
           std::__ndk1::
           basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>::append
                     (abStack_68,param_2);
  local_40 = puVar2[2];
  uStack_48 = puVar2[1];
  local_50 = *puVar2;
  puVar2[1] = 0;
  puVar2[2] = 0;
  *puVar2 = 0;
                    /* try { // try from 0013ea64 to 0013ea8b has its CatchHandler @ 0013ea8c */
  std::runtime_error::runtime_error(this_00,(basic_string *)&local_50);
                    /* WARNING: Subroutine does not return */
  __cxa_throw(this_00,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
}



/* 0013eaec get<void(*)(void*)> */

/* void RawApi::get<void (*)(void*)>(void (*&)(void*), char const*) */

void __thiscall RawApi::get<void(*)(void*)>(RawApi *this,_func_void_void_ptr *param_1,char *param_2)

{
  long lVar1;
  runtime_error *this_00;
  undefined8 *puVar2;
  basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>> abStack_68 [24];
  undefined8 local_50;
  undefined8 uStack_48;
  undefined8 local_40;
  
  lVar1 = dlsym(*(undefined8 *)this,param_2);
  *(long *)param_1 = lVar1;
  if (lVar1 != 0) {
    return;
  }
  this_00 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013eb3c to 0013eb4b has its CatchHandler @ 0013ebe8 */
  _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2B8ne180000ILi0EEEPKc
            (abStack_68,"RAW ABI missing ");
                    /* try { // try from 0013eb4c to 0013eb57 has its CatchHandler @ 0013ebd0 */
  puVar2 = (undefined8 *)
           std::__ndk1::
           basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>::append
                     (abStack_68,param_2);
  local_40 = puVar2[2];
  uStack_48 = puVar2[1];
  local_50 = *puVar2;
  puVar2[1] = 0;
  puVar2[2] = 0;
  *puVar2 = 0;
                    /* try { // try from 0013eb74 to 0013eb9b has its CatchHandler @ 0013eb9c */
  std::runtime_error::runtime_error(this_00,(basic_string *)&local_50);
                    /* WARNING: Subroutine does not return */
  __cxa_throw(this_00,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
}



/* 0013ebfc get<void(*)(void*,int,float)> */

/* void RawApi::get<void (*)(void*, int, float)>(void (*&)(void*, int, float), char const*) */

void __thiscall
RawApi::get<void(*)(void*,int,float)>
          (RawApi *this,_func_void_void_ptr_int_float *param_1,char *param_2)

{
  long lVar1;
  runtime_error *this_00;
  undefined8 *puVar2;
  basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>> abStack_68 [24];
  undefined8 local_50;
  undefined8 uStack_48;
  undefined8 local_40;
  
  lVar1 = dlsym(*(undefined8 *)this,param_2);
  *(long *)param_1 = lVar1;
  if (lVar1 != 0) {
    return;
  }
  this_00 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013ec4c to 0013ec5b has its CatchHandler @ 0013ecf8 */
  _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2B8ne180000ILi0EEEPKc
            (abStack_68,"RAW ABI missing ");
                    /* try { // try from 0013ec5c to 0013ec67 has its CatchHandler @ 0013ece0 */
  puVar2 = (undefined8 *)
           std::__ndk1::
           basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>::append
                     (abStack_68,param_2);
  local_40 = puVar2[2];
  uStack_48 = puVar2[1];
  local_50 = *puVar2;
  puVar2[1] = 0;
  puVar2[2] = 0;
  *puVar2 = 0;
                    /* try { // try from 0013ec84 to 0013ecab has its CatchHandler @ 0013ecac */
  std::runtime_error::runtime_error(this_00,(basic_string *)&local_50);
                    /* WARNING: Subroutine does not return */
  __cxa_throw(this_00,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
}



/* 0013ed0c get<void(*)(void*,int)> */

/* void RawApi::get<void (*)(void*, int)>(void (*&)(void*, int), char const*) */

void __thiscall
RawApi::get<void(*)(void*,int)>(RawApi *this,_func_void_void_ptr_int *param_1,char *param_2)

{
  long lVar1;
  runtime_error *this_00;
  undefined8 *puVar2;
  basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>> abStack_68 [24];
  undefined8 local_50;
  undefined8 uStack_48;
  undefined8 local_40;
  
  lVar1 = dlsym(*(undefined8 *)this,param_2);
  *(long *)param_1 = lVar1;
  if (lVar1 != 0) {
    return;
  }
  this_00 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013ed5c to 0013ed6b has its CatchHandler @ 0013ee08 */
  _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2B8ne180000ILi0EEEPKc
            (abStack_68,"RAW ABI missing ");
                    /* try { // try from 0013ed6c to 0013ed77 has its CatchHandler @ 0013edf0 */
  puVar2 = (undefined8 *)
           std::__ndk1::
           basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>::append
                     (abStack_68,param_2);
  local_40 = puVar2[2];
  uStack_48 = puVar2[1];
  local_50 = *puVar2;
  puVar2[1] = 0;
  puVar2[2] = 0;
  *puVar2 = 0;
                    /* try { // try from 0013ed94 to 0013edbb has its CatchHandler @ 0013edbc */
  std::runtime_error::runtime_error(this_00,(basic_string *)&local_50);
                    /* WARNING: Subroutine does not return */
  __cxa_throw(this_00,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
}



/* 0013ee1c get<float(*)(void*,int)> */

/* void RawApi::get<float (*)(void*, int)>(float (*&)(void*, int), char const*) */

void __thiscall
RawApi::get<float(*)(void*,int)>(RawApi *this,_func_float_void_ptr_int *param_1,char *param_2)

{
  long lVar1;
  runtime_error *this_00;
  undefined8 *puVar2;
  basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>> abStack_68 [24];
  undefined8 local_50;
  undefined8 uStack_48;
  undefined8 local_40;
  
  lVar1 = dlsym(*(undefined8 *)this,param_2);
  *(long *)param_1 = lVar1;
  if (lVar1 != 0) {
    return;
  }
  this_00 = (runtime_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013ee6c to 0013ee7b has its CatchHandler @ 0013ef18 */
  _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2B8ne180000ILi0EEEPKc
            (abStack_68,"RAW ABI missing ");
                    /* try { // try from 0013ee7c to 0013ee87 has its CatchHandler @ 0013ef00 */
  puVar2 = (undefined8 *)
           std::__ndk1::
           basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>::append
                     (abStack_68,param_2);
  local_40 = puVar2[2];
  uStack_48 = puVar2[1];
  local_50 = *puVar2;
  puVar2[1] = 0;
  puVar2[2] = 0;
  *puVar2 = 0;
                    /* try { // try from 0013eea4 to 0013eecb has its CatchHandler @ 0013eecc */
  std::runtime_error::runtime_error(this_00,(basic_string *)&local_50);
                    /* WARNING: Subroutine does not return */
  __cxa_throw(this_00,PTR_PTR_0018db68,PTR__underflow_error_0018db70);
}



/* 0013ef2c __append */

/* std::__ndk1::vector<unsigned short, std::__ndk1::allocator<unsigned short> >::__append(unsigned
   long) */

void __thiscall
std::__ndk1::vector<unsigned_short,std::__ndk1::allocator<unsigned_short>>::__append
          (vector<unsigned_short,std::__ndk1::allocator<unsigned_short>> *this,ulong param_1)

{
  void *pvVar1;
  undefined2 *puVar2;
  undefined8 *puVar3;
  void *pvVar4;
  ulong uVar5;
  ulong uVar6;
  undefined2 *__s;
  undefined8 *puVar7;
  undefined8 *puVar8;
  ulong uVar9;
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
LAB_0013f0d8:
                    /* WARNING: Subroutine does not return */
    __throw_bad_array_new_length_abi_ne180000_();
  }
  uVar5 = *(long *)(this + 0x10) - (long)puVar10;
  uVar9 = uVar5;
  if (uVar5 <= uVar6) {
    uVar9 = uVar6;
  }
  if (0x7ffffffffffffffd < uVar5) {
    uVar9 = 0x7fffffffffffffff;
  }
  if (uVar9 == 0) {
    pvVar4 = (void *)0x0;
  }
  else {
    if ((long)uVar9 < 0) goto LAB_0013f0d8;
    pvVar4 = operator_new(uVar9 << 1);
  }
  __s = (undefined2 *)((long)pvVar4 + lVar11 * 2);
  pvVar1 = (void *)((long)pvVar4 + uVar9 * 2);
  memset(__s,0,param_1 * 2);
  puVar2 = __s + param_1;
  if ((long)__s_00 - (long)puVar10 == 0) {
    *(undefined2 **)this = __s;
    *(undefined2 **)(this + 8) = puVar2;
    *(void **)(this + 0x10) = pvVar1;
    if (puVar10 == (undefined2 *)0x0) {
      return;
    }
    goto LAB_0013f084;
  }
  uVar6 = ((long)__s_00 - (long)puVar10) - 2;
  if ((uVar6 < 0x1e) ||
     ((ulong)((long)__s_00 + (-((long)__s_00 - (long)puVar10) - (long)pvVar4)) < 0x20)) {
LAB_0013f068:
    do {
      __s_00 = __s_00 + -1;
      __s = __s + -1;
      *__s = *__s_00;
    } while (__s_00 != puVar10);
  }
  else {
    puVar7 = (undefined8 *)(__s + -8);
    puVar8 = (undefined8 *)(__s_00 + -8);
    uVar6 = (uVar6 >> 1) + 1;
    uVar5 = uVar6 & 0xfffffffffffffff0;
    __s_00 = __s_00 + -uVar5;
    __s = __s + -uVar5;
    uVar9 = uVar5;
    do {
      puVar3 = puVar8 + -1;
      uVar14 = puVar8[-2];
      uVar13 = puVar8[1];
      uVar12 = *puVar8;
      uVar9 = uVar9 - 0x10;
      puVar8 = puVar8 + -4;
      puVar7[-1] = *puVar3;
      puVar7[-2] = uVar14;
      puVar7[1] = uVar13;
      *puVar7 = uVar12;
      puVar7 = puVar7 + -4;
    } while (uVar9 != 0);
    if (uVar6 != uVar5) goto LAB_0013f068;
  }
  *(undefined2 **)this = __s;
  *(undefined2 **)(this + 8) = puVar2;
  *(void **)(this + 0x10) = pvVar1;
  if (puVar10 == (undefined2 *)0x0) {
    return;
  }
LAB_0013f084:
  operator_delete(puVar10);
  return;
}



/* 0013f0dc __throw_length_error[abi:ne180000] */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* std::__ndk1::vector<unsigned short, std::__ndk1::allocator<unsigned short>
   >::__throw_length_error[abi:ne180000]() const */

void std::__ndk1::vector<unsigned_short,std::__ndk1::allocator<unsigned_short>>::
     __throw_length_error_abi_ne180000_(void)

{
                    /* WARNING: Subroutine does not return */
  __ndk1::__throw_length_error_abi_ne180000_("vector");
}



/* 0013f0f0 __throw_length_error[abi:ne180000] */

/* std::__ndk1::__throw_length_error[abi:ne180000](char const*) */

void std::__ndk1::__throw_length_error_abi_ne180000_(char *param_1)

{
  length_error *this;
  
  this = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 0013f10c to 0013f113 has its CatchHandler @ 0013f12c */
  length_error::length_error_abi_ne180000_(this,param_1);
                    /* WARNING: Subroutine does not return */
  __cxa_throw(this,PTR_PTR_0018db78,PTR__out_of_range_0018db80);
}



/* 0013f140 length_error[abi:ne180000] */

/* std::length_error::length_error[abi:ne180000](char const*) */

void __thiscall std::length_error::length_error_abi_ne180000_(length_error *this,char *param_1)

{
  logic_error::logic_error((logic_error *)this,param_1);
  *(undefined **)this = PTR_vtable_0018db88 + 0x10;
  return;
}



/* 0013f170 __throw_bad_array_new_length[abi:ne180000] */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* std::__throw_bad_array_new_length[abi:ne180000]() */

void std::__throw_bad_array_new_length_abi_ne180000_(void)

{
  bad_array_new_length *this;
  
  this = (bad_array_new_length *)__cxa_allocate_exception(8);
  bad_array_new_length::bad_array_new_length(this);
                    /* WARNING: Subroutine does not return */
  __cxa_throw(this,PTR_PTR_0018db90,PTR__bad_array_new_length_0018db98);
}



/* 0013f1a4 __throw_length_error[abi:ne180000] */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* std::__ndk1::vector<float, std::__ndk1::allocator<float> >::__throw_length_error[abi:ne180000]()
   const */

void std::__ndk1::vector<float,std::__ndk1::allocator<float>>::__throw_length_error_abi_ne180000_
               (void)

{
                    /* WARNING: Subroutine does not return */
  __ndk1::__throw_length_error_abi_ne180000_("vector");
}



/* 0013f1b8 yuv */

/* m9::Ipe::yuv(float const*, float*) const */

void __thiscall m9::Ipe::yuv(Ipe *this,float *param_1,float *param_2)

{
  float *pfVar1;
  float *pfVar2;
  uint uVar3;
  long lVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  float *pfVar8;
  float *pfVar9;
  int iVar10;
  long lVar11;
  ulong uVar12;
  ulong uVar13;
  ulong uVar14;
  ulong uVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  undefined8 uVar19;
  undefined8 uVar20;
  undefined8 uVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  
  fVar16 = *(float *)this;
  fVar23 = *param_1 * fVar16 * 0.299 + param_1[1] * fVar16 * 0.587 + param_1[2] * fVar16 * 0.114;
  fVar18 = (float)NEON_fminnm(fVar23,0x3f800000);
  if (fVar18 <= 0.0) {
    fVar18 = 0.0;
  }
  iVar7 = (int)(fVar18 * 4095.0);
  if (0xffd < iVar7) {
    iVar7 = 0xffe;
  }
  pfVar1 = (float *)(*(long *)(this + 0x28) + (long)iVar7 * 4);
  fVar25 = *pfVar1;
  pfVar8 = *(float **)(this + 8);
  fVar24 = 1e-06;
  if (1e-06 <= fVar23) {
    fVar24 = fVar23;
  }
  fVar24 = (fVar25 + (pfVar1[1] - fVar25) * (fVar18 * 4095.0 - (float)iVar7)) / fVar24;
  fVar23 = fVar24 * *param_1 * fVar16;
  fVar18 = fVar24 * param_1[1] * fVar16;
  fVar24 = fVar24 * param_1[2] * fVar16;
  fVar16 = pfVar8[3] * fVar23 + pfVar8[4] * fVar18 + pfVar8[5] * fVar24;
  fVar25 = pfVar8[6] * fVar23 + pfVar8[7] * fVar18 + pfVar8[8] * fVar24;
  if (fVar16 <= 0.0) {
    fVar16 = 0.0;
  }
  if (fVar25 <= 0.0) {
    fVar25 = 0.0;
  }
  fVar18 = *pfVar8 * fVar23 + pfVar8[1] * fVar18 + pfVar8[2] * fVar24;
  if (fVar18 <= 0.0) {
    fVar18 = 0.0;
  }
  fVar23 = fVar25;
  if (fVar25 <= fVar16) {
    fVar23 = fVar16;
  }
  if (fVar23 <= fVar18) {
    fVar23 = fVar18;
  }
  fVar24 = fVar25;
  if (fVar16 <= fVar25) {
    fVar24 = fVar16;
  }
  if (fVar18 <= fVar24) {
    fVar24 = fVar18;
  }
  fVar24 = fVar23 - fVar24;
  fVar22 = 1e-06;
  if (1e-06 <= fVar23) {
    fVar22 = fVar23;
  }
  fVar17 = 0.0;
  if (1e-07 < fVar24) {
    if (fVar23 == fVar18) {
      fVar17 = ((fVar16 - fVar25) * 60.0) / fVar24;
    }
    else if (fVar23 == fVar16) {
      fVar17 = ((fVar25 - fVar18) * 60.0) / fVar24 + 120.0;
    }
    else {
      fVar17 = ((fVar18 - fVar16) * 60.0) / fVar24 + 240.0;
    }
    if (fVar17 < 0.0) {
      fVar17 = fVar17 + 360.0;
    }
  }
  fVar16 = fVar17 / 15.0;
  fVar18 = (fVar24 / fVar22) * 15.0;
  fVar25 = fVar18 - (float)(int)fVar18;
  fVar26 = 1.0 - fVar25;
  iVar7 = (int)fVar16 % 0x18 + 1;
  iVar5 = ((int)fVar16 % 0x18) * 0x10;
  uVar6 = (char)iVar7 * 0x2b;
  iVar10 = (int)fVar18;
  fVar16 = fVar16 - (float)(int)fVar16;
  uVar6 = iVar7 + ((uVar6 >> 0xf & 1) + (uVar6 >> 10)) * -0x18;
  iVar7 = iVar10;
  if (0xe < iVar10) {
    iVar7 = 0xf;
  }
  uVar3 = iVar5 + iVar7;
  if (0xd < iVar10) {
    iVar10 = 0xe;
  }
  lVar11 = *(long *)(this + 0x10);
  uVar12 = -(ulong)(uVar3 >> 0x1f) & 0xfffffffc00000000 | (ulong)uVar3 << 2;
  uVar3 = -(uVar6 >> 7 & 1) & 0xfffff000 | (uVar6 & 0xff) << 4;
  uVar6 = iVar5 + iVar10 + 1;
  uVar13 = -(ulong)(uVar6 >> 0x1f) & 0xfffffffc00000000 | (ulong)uVar6 << 2;
  uVar6 = uVar3 + iVar7;
  uVar3 = uVar3 + iVar10 + 1;
  uVar14 = -(ulong)(uVar6 >> 0x1f) & 0xfffffffc00000000 | (ulong)uVar6 << 2;
  uVar15 = -(ulong)(uVar3 >> 0x1f) & 0xfffffffc00000000 | (ulong)uVar3 << 2;
  fVar18 = fmodf(fVar17 + (1.0 - fVar16) *
                          (fVar26 * *(float *)(lVar11 + uVar12) +
                          fVar25 * *(float *)(lVar11 + uVar13)) +
                          fVar16 * (fVar26 * *(float *)(lVar11 + uVar14) +
                                   fVar25 * *(float *)(lVar11 + uVar15)) + 720.0,360.0);
  lVar11 = *(long *)(this + 0x18);
  fVar16 = (float)NEON_fminnm((fVar24 / fVar22) *
                              ((1.0 - fVar16) *
                               (fVar26 * *(float *)(lVar11 + uVar12) +
                               fVar25 * *(float *)(lVar11 + uVar13)) +
                               fVar16 * (fVar26 * *(float *)(lVar11 + uVar14) +
                                        fVar25 * *(float *)(lVar11 + uVar15)) + 1.0),0x3f800000);
  if (fVar16 <= 0.0) {
    fVar16 = 0.0;
  }
  fVar16 = fVar23 * fVar16;
  fVar24 = fmodf(fVar18 / 60.0,2.0);
  iVar7 = (int)(fVar18 / 60.0);
  fVar24 = (1.0 - ABS(fVar24 + -1.0)) * fVar16;
  fVar18 = fVar16;
  if (iVar7 < 2) {
    if (iVar7 == 0) {
      fVar25 = 0.0;
      goto LAB_0013f5b0;
    }
    if (iVar7 == 1) {
      fVar25 = 0.0;
      fVar18 = fVar24;
      fVar24 = fVar16;
      goto LAB_0013f5b0;
    }
  }
  else {
    if (iVar7 == 2) {
      fVar25 = fVar24;
      fVar18 = 0.0;
      fVar24 = fVar16;
      goto LAB_0013f5b0;
    }
    fVar25 = fVar16;
    if (iVar7 == 3) {
      fVar18 = 0.0;
      goto LAB_0013f5b0;
    }
    if (iVar7 == 4) {
      fVar18 = fVar24;
      fVar24 = 0.0;
      goto LAB_0013f5b0;
    }
  }
  fVar25 = fVar24;
  fVar24 = 0.0;
LAB_0013f5b0:
  fVar23 = fVar23 - fVar16;
  uVar19 = NEON_fmov(0x3f800000,4);
  fVar16 = (float)NEON_fminnm(fVar23 + fVar24,0x3f800000);
  uVar19 = NEON_fminnm(CONCAT44(fVar23 + fVar18,fVar23 + fVar25),uVar19,4);
  if (fVar16 <= 0.0) {
    fVar16 = 0.0;
  }
  uVar19 = NEON_fmaxnm(uVar19,0,4);
  iVar7 = (int)(fVar16 * 256.0);
  uVar20 = NEON_fcvtzs(uVar19,8,4);
  if (0xfe < iVar7) {
    iVar7 = 0xff;
  }
  lVar11 = *(long *)(this + 0x20);
  uVar20 = NEON_smin(uVar20,0xff000000ff,4);
  pfVar1 = (float *)(lVar11 + (long)iVar7 * 4);
  uVar21 = NEON_scvtf(uVar20,4);
  fVar24 = *pfVar1;
  pfVar9 = *(float **)(this + 0x30);
  pfVar8 = (float *)(lVar11 + (long)(int)uVar20 * 4);
  pfVar2 = (float *)(lVar11 + (long)(int)((ulong)uVar20 >> 0x20) * 4);
  fVar18 = *pfVar8;
  fVar23 = *pfVar2;
  fVar24 = fVar24 + (pfVar1[1] - fVar24) * (fVar16 * 256.0 - (float)iVar7);
  fVar18 = fVar18 + (pfVar8[1] - fVar18) * ((float)uVar19 * 256.0 - (float)uVar21);
  fVar23 = fVar23 + (pfVar2[1] - fVar23) *
                    ((float)((ulong)uVar19 >> 0x20) * 256.0 - (float)((ulong)uVar21 >> 0x20));
  fVar25 = fVar18 - fVar24;
  fVar16 = fVar23 - fVar24;
  uVar19 = NEON_fcmge(CONCAT44(fVar16,fVar25),0,4);
  uVar12 = NEON_bsl(uVar19,DAT_00119ae0,DAT_00119b08,1);
  fVar22 = fVar25 + pfVar9[uVar12 & 0xffffffff] * fVar16;
  fVar16 = fVar16 + pfVar9[uVar12 >> 0x20] * fVar25;
  *param_2 = *pfVar9 * fVar23 + fVar24 * pfVar9[1] + pfVar9[2] * fVar18;
  lVar11 = 0x10;
  if (fVar22 < 0.0) {
    lVar11 = 0x14;
  }
  lVar4 = 0x20;
  if (fVar16 < 0.0) {
    lVar4 = 0x24;
  }
  param_2[1] = fVar22 * *(float *)((long)pfVar9 + lVar11);
  param_2[2] = fVar16 * *(float *)((long)pfVar9 + lVar4);
  return;
}



/* 0013f754 __nth_element[abi:ne180000]<std::__ndk1::_ClassicAlgPolicy,std::__ndk1::__less<void,void>&,std::__ndk1::__wrap_iter<float*>> */

/* void std::__ndk1::__nth_element[abi:ne180000]<std::__ndk1::_ClassicAlgPolicy,
   std::__ndk1::__less<void, void>&, std::__ndk1::__wrap_iter<float*>
   >(std::__ndk1::__wrap_iter<float*>, std::__ndk1::__wrap_iter<float*>,
   std::__ndk1::__wrap_iter<float*>, std::__ndk1::__less<void, void>&) */

void std::__ndk1::
     __nth_element_abi_ne180000_<std::__ndk1::_ClassicAlgPolicy,std::__ndk1::__less<void,void>&,std::__ndk1::__wrap_iter<float*>>
               (__wrap_iter param_1,__wrap_iter param_2,__wrap_iter param_3,__less *param_4)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  ulong uVar4;
  float *pfVar5;
  float *pfVar6;
  int iVar7;
  float *pfVar8;
  float *pfVar9;
  float *pfVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  
  pfVar2 = (float *)(ulong)param_2;
  pfVar1 = (float *)(ulong)param_1;
  pfVar6 = (float *)(ulong)param_3;
code_r0x0013f754:
  while( true ) {
    pfVar3 = pfVar6;
    if (pfVar3 == pfVar2) {
      return;
    }
    uVar4 = (long)pfVar3 - (long)pfVar1 >> 2;
    if (uVar4 < 2) {
      return;
    }
    if (uVar4 == 3) {
      fVar11 = *pfVar1;
      fVar12 = pfVar1[1];
      fVar13 = pfVar3[-1];
      if (fVar11 <= fVar12) {
        if (fVar12 <= fVar13) {
          return;
        }
        pfVar1[1] = fVar13;
        pfVar3[-1] = fVar12;
        fVar11 = *pfVar1;
        if (fVar11 <= pfVar1[1]) {
          return;
        }
        *pfVar1 = pfVar1[1];
        pfVar1[1] = fVar11;
        return;
      }
      if (fVar13 < fVar12) {
        *pfVar1 = fVar13;
        pfVar3[-1] = fVar11;
        return;
      }
      *pfVar1 = fVar12;
      pfVar1[1] = fVar11;
      if (fVar11 <= pfVar3[-1]) {
        return;
      }
      pfVar1[1] = pfVar3[-1];
      pfVar3[-1] = fVar11;
      return;
    }
    if (uVar4 == 2) {
      fVar11 = *pfVar1;
      if (fVar11 <= pfVar3[-1]) {
        return;
      }
      *pfVar1 = pfVar3[-1];
      pfVar3[-1] = fVar11;
      return;
    }
    if ((long)uVar4 < 8) {
      while (pfVar6 = pfVar1, pfVar3 + -1 != pfVar6) {
        pfVar1 = pfVar6 + 1;
        if ((pfVar6 != pfVar3) && (pfVar1 != pfVar3)) {
          fVar12 = *pfVar6;
          pfVar2 = pfVar6;
          pfVar5 = pfVar1;
          fVar11 = fVar12;
          do {
            pfVar8 = pfVar5 + 1;
            pfVar9 = pfVar5;
            fVar13 = *pfVar5;
            if (fVar11 <= *pfVar5) {
              pfVar9 = pfVar2;
              fVar13 = fVar11;
            }
            fVar11 = fVar13;
            pfVar2 = pfVar9;
            pfVar5 = pfVar8;
          } while (pfVar8 != pfVar3);
          if (pfVar9 != pfVar6) {
            *pfVar6 = *pfVar9;
            *pfVar9 = fVar12;
          }
        }
      }
      return;
    }
    fVar11 = *pfVar1;
    pfVar6 = pfVar3 + -1;
    fVar13 = *pfVar6;
    pfVar5 = pfVar1 + (uVar4 >> 1);
    fVar12 = *pfVar5;
    pfVar9 = pfVar6;
    if (fVar11 <= fVar12) break;
    if (fVar13 < fVar12) {
      *pfVar1 = fVar13;
      iVar7 = 1;
      *pfVar6 = fVar11;
      fVar11 = *pfVar1;
      fVar12 = *pfVar5;
      if (fVar12 <= fVar11) goto LAB_0013f8c0;
      goto LAB_0013f854;
    }
    *pfVar1 = fVar12;
    *pfVar5 = fVar11;
    if (fVar11 <= *pfVar6) {
LAB_0013f8a8:
      iVar7 = 1;
      fVar11 = *pfVar1;
      fVar12 = *pfVar5;
      if (fVar12 <= fVar11) goto LAB_0013f8c0;
      goto LAB_0013f854;
    }
    iVar7 = 2;
    *pfVar5 = *pfVar6;
    *pfVar6 = fVar11;
    fVar11 = *pfVar1;
    fVar12 = *pfVar5;
    if (fVar11 < fVar12) goto LAB_0013f854;
LAB_0013f8c0:
    while (pfVar9 = pfVar9 + -1, pfVar9 != pfVar1) {
      if (*pfVar9 < fVar12) goto code_r0x0013f8d8;
    }
    pfVar5 = pfVar1 + 1;
    pfVar9 = pfVar5;
    if (*pfVar6 <= fVar11) {
      while( true ) {
        if (pfVar9 == pfVar6) {
          return;
        }
        fVar12 = *pfVar9;
        if (fVar11 < fVar12) break;
        pfVar9 = pfVar9 + 1;
      }
      pfVar5 = pfVar9 + 1;
      *pfVar9 = *pfVar6;
      *pfVar6 = fVar12;
    }
    if (pfVar5 == pfVar6) {
      return;
    }
    while( true ) {
      do {
        pfVar9 = pfVar5;
        pfVar5 = pfVar9 + 1;
        fVar11 = *pfVar9;
      } while (fVar11 <= *pfVar1);
      do {
        pfVar6 = pfVar6 + -1;
      } while (*pfVar1 < *pfVar6);
      if (pfVar6 <= pfVar9) break;
      *pfVar9 = *pfVar6;
      *pfVar6 = fVar11;
    }
    pfVar1 = pfVar9;
    pfVar6 = pfVar3;
    if (pfVar2 < pfVar9) {
      return;
    }
  }
  if (fVar12 <= fVar13) {
    iVar7 = 0;
    fVar11 = *pfVar1;
    fVar12 = *pfVar5;
    if (fVar12 <= fVar11) goto LAB_0013f8c0;
  }
  else {
    *pfVar5 = fVar13;
    *pfVar6 = fVar12;
    fVar11 = *pfVar1;
    if (fVar11 <= *pfVar5) goto LAB_0013f8a8;
    *pfVar1 = *pfVar5;
    iVar7 = 2;
    *pfVar5 = fVar11;
    fVar11 = *pfVar1;
    fVar12 = *pfVar5;
    if (fVar12 <= fVar11) goto LAB_0013f8c0;
  }
LAB_0013f854:
  if (pfVar6 <= pfVar1 + 1) goto LAB_0013f8f0;
  goto LAB_0013f864;
code_r0x0013f8d8:
  iVar7 = iVar7 + 1;
  *pfVar1 = *pfVar9;
  *pfVar9 = fVar11;
  if (pfVar1 + 1 < pfVar9) {
LAB_0013f864:
    pfVar10 = pfVar1 + 1;
    pfVar8 = pfVar5;
    while( true ) {
      pfVar5 = pfVar8;
      do {
        pfVar6 = pfVar10;
        pfVar10 = pfVar6 + 1;
        fVar11 = *pfVar6;
      } while (fVar11 < *pfVar5);
      do {
        pfVar9 = pfVar9 + -1;
      } while (*pfVar5 <= *pfVar9);
      if (pfVar9 <= pfVar6) break;
      *pfVar6 = *pfVar9;
      iVar7 = iVar7 + 1;
      *pfVar9 = fVar11;
      pfVar8 = pfVar9;
      if (pfVar6 != pfVar5) {
        pfVar8 = pfVar5;
      }
    }
  }
  else {
LAB_0013f8f0:
    pfVar6 = pfVar1 + 1;
  }
  if (pfVar6 != pfVar5) {
    fVar11 = *pfVar6;
    if (*pfVar5 < fVar11) {
      iVar7 = iVar7 + 1;
      *pfVar6 = *pfVar5;
      *pfVar5 = fVar11;
    }
  }
  if (pfVar6 == pfVar2) {
    return;
  }
  if (iVar7 == 0) {
    pfVar5 = pfVar1;
    pfVar9 = pfVar6;
    if (pfVar2 < pfVar6) {
      do {
        pfVar9 = pfVar5 + 1;
        if (pfVar9 == pfVar6) {
          return;
        }
        fVar11 = *pfVar5;
        pfVar5 = pfVar9;
      } while (fVar11 <= *pfVar9);
    }
    else {
      do {
        pfVar5 = pfVar9 + 1;
        if (pfVar5 == pfVar3) {
          return;
        }
        fVar11 = *pfVar9;
        pfVar9 = pfVar5;
      } while (fVar11 <= *pfVar5);
    }
  }
  if (pfVar6 <= pfVar2) {
    pfVar1 = pfVar6 + 1;
    pfVar6 = pfVar3;
  }
  goto code_r0x0013f754;
}



/* 0013fafc __throw_length_error[abi:ne180000] */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char>
   >::__throw_length_error[abi:ne180000]() const */

void std::__ndk1::basic_string<char,std::__ndk1::char_traits<char>,std::__ndk1::allocator<char>>::
     __throw_length_error_abi_ne180000_(void)

{
                    /* WARNING: Subroutine does not return */
  __ndk1::__throw_length_error_abi_ne180000_("basic_string");
}



/* 0013fb10 ~vector[abi:ne180000] */

/* std::__ndk1::vector<std::__ndk1::thread, std::__ndk1::allocator<std::__ndk1::thread>
   >::~vector[abi:ne180000]() */

void __thiscall
std::__ndk1::vector<std::__ndk1::thread,std::__ndk1::allocator<std::__ndk1::thread>>::
~vector_abi_ne180000_(vector<std::__ndk1::thread,std::__ndk1::allocator<std::__ndk1::thread>> *this)

{
  thread *ptVar1;
  thread *this_00;
  thread *ptVar2;
  
  ptVar2 = *(thread **)this;
  if (ptVar2 != (thread *)0x0) {
    this_00 = *(thread **)(this + 8);
    ptVar1 = ptVar2;
    if (this_00 != ptVar2) {
      do {
        this_00 = this_00 + -8;
        thread::~thread(this_00);
      } while (this_00 != ptVar2);
      ptVar1 = *(thread **)this;
    }
    *(thread **)(this + 8) = ptVar2;
    operator_delete(ptVar1);
    return;
  }
  return;
}



/* 0013fb78 __throw_length_error[abi:ne180000] */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* std::__ndk1::vector<std::__ndk1::thread, std::__ndk1::allocator<std::__ndk1::thread>
   >::__throw_length_error[abi:ne180000]() const */

void std::__ndk1::vector<std::__ndk1::thread,std::__ndk1::allocator<std::__ndk1::thread>>::
     __throw_length_error_abi_ne180000_(void)

{
                    /* WARNING: Subroutine does not return */
  __ndk1::__throw_length_error_abi_ne180000_("vector");
}



/* 0013fb8c ~__split_buffer */

/* std::__ndk1::__split_buffer<std::__ndk1::thread,
   std::__ndk1::allocator<std::__ndk1::thread>&>::~__split_buffer() */

void __thiscall
std::__ndk1::__split_buffer<std::__ndk1::thread,std::__ndk1::allocator<std::__ndk1::thread>&>::
~__split_buffer(__split_buffer<std::__ndk1::thread,std::__ndk1::allocator<std::__ndk1::thread>&>
                *this)

{
  long lVar1;
  long lVar2;
  
  lVar1 = *(long *)(this + 8);
  lVar2 = *(long *)(this + 0x10);
  while (lVar2 != lVar1) {
    *(thread **)(this + 0x10) = (thread *)(lVar2 + -8);
    thread::~thread((thread *)(lVar2 + -8));
    lVar2 = *(long *)(this + 0x10);
  }
  if (*(void **)this == (void *)0x0) {
    return;
  }
  operator_delete(*(void **)this);
  return;
}



/* 0013fbe0 ~unique_ptr[abi:ne180000] */

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
    __thread_struct::~__thread_struct(this_00);
    operator_delete(this_00);
    return;
  }
  return;
}



/* 0013fc1c __sort<std::__ndk1::__less<char,char>&,char*> */

/* void std::__ndk1::__sort<std::__ndk1::__less<char, char>&, char*>(char*, char*,
   std::__ndk1::__less<char, char>&) */

void std::__ndk1::__sort<std::__ndk1::__less<char,char>&,char*>
               (char *param_1,char *param_2,__less *param_3)

{
  bool in_w5;
  
  __introsort<std::__ndk1::_ClassicAlgPolicy,std::__ndk1::ranges::less,char*,false>
            ((__ndk1 *)param_1,param_2,(char *)param_3,
             (int)LZCOUNT((long)param_2 - (long)param_1) * -2 + 0x7e,1,in_w5);
  return;
}



/* 0013fc38 __introsort<std::__ndk1::_ClassicAlgPolicy,std::__ndk1::ranges::less,char*,false> */

/* void std::__ndk1::__introsort<std::__ndk1::_ClassicAlgPolicy, std::__ndk1::ranges::less, char*,
   false>(char*, char*, std::__ndk1::ranges::less,
   std::__ndk1::iterator_traits<char*>::difference_type, bool) */

void __thiscall
std::__ndk1::__introsort<std::__ndk1::_ClassicAlgPolicy,std::__ndk1::ranges::less,char*,false>
          (__ndk1 *this,char *param_1,char *param_2,less param_3,difference_type param_4,
          bool param_5)

{
  long lVar1;
  bool bVar2;
  bool bVar3;
  __ndk1 _Var4;
  ulong uVar5;
  ulong uVar6;
  ulong uVar7;
  long lVar8;
  __ndk1 *p_Var9;
  __ndk1 *p_Var10;
  long lVar11;
  __ndk1 *p_Var12;
  ulong uVar13;
  __ndk1 *p_Var14;
  __ndk1 _Var15;
  __ndk1 _Var16;
  __ndk1 *p_Var17;
  __ndk1 *p_Var18;
  __ndk1 _Var19;
  undefined local_34;
  
  uVar6 = (ulong)param_5;
  uVar5 = (ulong)param_3;
  local_34 = SUB81(param_2,0);
LAB_0013fc6c:
  do {
    p_Var12 = this;
    uVar7 = (long)param_1 - (long)p_Var12;
    if ((long)uVar7 < 3) {
      if (uVar7 < 2) {
        return;
      }
      if (uVar7 == 2) {
        _Var15 = *p_Var12;
        if ((byte)_Var15 <= (byte)((__ndk1 *)param_1)[-1]) {
          return;
        }
        *p_Var12 = ((__ndk1 *)param_1)[-1];
        ((__ndk1 *)param_1)[-1] = _Var15;
        return;
      }
    }
    else {
      if (uVar7 == 3) {
        _Var15 = p_Var12[1];
        _Var16 = *p_Var12;
        _Var19 = ((__ndk1 *)param_1)[-1];
        if ((byte)_Var15 < (byte)_Var16) {
          if ((byte)_Var19 < (byte)_Var15) {
            *p_Var12 = _Var19;
          }
          else {
            *p_Var12 = _Var15;
            p_Var12[1] = _Var16;
            if ((byte)_Var16 <= (byte)((__ndk1 *)param_1)[-1]) {
              return;
            }
            p_Var12[1] = ((__ndk1 *)param_1)[-1];
          }
          ((__ndk1 *)param_1)[-1] = _Var16;
          return;
        }
        if ((byte)_Var15 <= (byte)_Var19) {
          return;
        }
        p_Var12[1] = _Var19;
        ((__ndk1 *)param_1)[-1] = _Var15;
        _Var15 = *p_Var12;
        if ((byte)_Var15 <= (byte)p_Var12[1]) {
          return;
        }
        *p_Var12 = p_Var12[1];
        p_Var12[1] = _Var15;
        return;
      }
      if (uVar7 == 4) {
        _Var19 = *p_Var12;
        p_Var9 = p_Var12 + 1;
        _Var15 = *p_Var9;
        p_Var14 = p_Var12 + 2;
        _Var16 = *p_Var14;
        p_Var10 = p_Var12;
        if ((byte)_Var15 < (byte)_Var19) {
          p_Var17 = p_Var14;
          _Var4 = _Var19;
          if ((byte)_Var15 <= (byte)_Var16) {
            *p_Var12 = _Var15;
            p_Var12[1] = _Var19;
            p_Var10 = p_Var9;
            if ((byte)_Var19 <= (byte)_Var16) goto LAB_00140324;
          }
LAB_001402c0:
          *p_Var10 = _Var16;
          *p_Var17 = _Var19;
          _Var15 = _Var4;
        }
        else {
          if ((byte)_Var15 <= (byte)_Var16) {
LAB_00140324:
            _Var19 = ((__ndk1 *)param_1)[-1];
            _Var15 = _Var16;
            if ((byte)_Var16 <= (byte)_Var19) {
              return;
            }
            goto LAB_00140334;
          }
          *p_Var9 = _Var16;
          *p_Var14 = _Var15;
          p_Var17 = p_Var9;
          _Var4 = _Var15;
          if ((byte)_Var16 < (byte)_Var19) goto LAB_001402c0;
        }
        _Var19 = ((__ndk1 *)param_1)[-1];
        if ((byte)_Var15 <= (byte)_Var19) {
          return;
        }
LAB_00140334:
        *p_Var14 = _Var19;
        ((__ndk1 *)param_1)[-1] = _Var15;
        _Var15 = *p_Var14;
        _Var16 = *p_Var9;
        if ((byte)_Var16 <= (byte)_Var15) {
          return;
        }
        _Var19 = *p_Var12;
        p_Var12[1] = _Var15;
        p_Var12[2] = _Var16;
        if ((byte)_Var19 <= (byte)_Var15) {
          return;
        }
        *p_Var12 = _Var15;
        p_Var12[1] = _Var19;
        return;
      }
      if (uVar7 == 5) {
        __sort5_abi_ne180000_<std::__ndk1::_ClassicAlgPolicy,std::__ndk1::ranges::less,char*>
                  ((char *)p_Var12,(char *)(p_Var12 + 1),(char *)(p_Var12 + 2),(char *)(p_Var12 + 3)
                   ,(char *)((__ndk1 *)param_1 + -1),(less)uVar6);
        return;
      }
    }
    if ((long)uVar7 < 0x18) {
      p_Var10 = p_Var12 + 1;
      if ((param_4 & 1) == 0) {
        if (p_Var12 == (__ndk1 *)param_1 || p_Var10 == (__ndk1 *)param_1) {
          return;
        }
        do {
          p_Var9 = p_Var10;
          _Var15 = p_Var12[1];
          _Var16 = *p_Var12;
          p_Var12 = p_Var9;
          if ((byte)_Var15 < (byte)_Var16) {
            do {
              *p_Var12 = _Var16;
              _Var16 = p_Var12[-2];
              p_Var12 = p_Var12 + -1;
            } while ((byte)_Var15 < (byte)_Var16);
            *p_Var12 = _Var15;
          }
          p_Var10 = p_Var9 + 1;
          p_Var12 = p_Var9;
        } while (p_Var9 + 1 != (__ndk1 *)param_1);
        return;
      }
      if (p_Var12 == (__ndk1 *)param_1 || p_Var10 == (__ndk1 *)param_1) {
        return;
      }
      lVar8 = 0;
      p_Var9 = p_Var12;
      do {
        p_Var14 = p_Var10;
        _Var15 = p_Var9[1];
        _Var16 = *p_Var9;
        lVar1 = lVar8;
        if ((byte)_Var15 < (byte)_Var16) {
          do {
            lVar11 = lVar1;
            p_Var12[lVar11 + 1] = _Var16;
            p_Var10 = p_Var12;
            if (lVar11 == 0) goto LAB_001401fc;
            _Var16 = p_Var12[lVar11 + -1];
            lVar1 = lVar11 + -1;
          } while ((byte)_Var15 < (byte)_Var16);
          p_Var10 = p_Var12 + lVar11;
LAB_001401fc:
          *p_Var10 = _Var15;
        }
        p_Var10 = p_Var14 + 1;
        lVar8 = lVar8 + 1;
        p_Var9 = p_Var14;
        if (p_Var10 == (__ndk1 *)param_1) {
          return;
        }
      } while( true );
    }
    if (uVar5 == 0) {
      if (p_Var12 == (__ndk1 *)param_1) {
        return;
      }
      __partial_sort_impl_abi_ne180000_<std::__ndk1::_ClassicAlgPolicy,std::__ndk1::ranges::less&,char*,char*>
                ((char *)p_Var12,param_1,param_1,(less *)&local_34);
      return;
    }
    uVar13 = uVar7 >> 1;
    _Var15 = ((__ndk1 *)param_1)[-1];
    p_Var10 = p_Var12 + uVar13;
    if (uVar7 < 0x81) {
      _Var16 = *p_Var12;
      _Var19 = *p_Var10;
      if ((byte)_Var16 < (byte)_Var19) {
        if ((byte)_Var15 < (byte)_Var16) {
          *p_Var10 = _Var15;
        }
        else {
          *p_Var10 = _Var16;
          *p_Var12 = _Var19;
          if ((byte)_Var19 <= (byte)((__ndk1 *)param_1)[-1]) goto LAB_0013fdf4;
          *p_Var12 = ((__ndk1 *)param_1)[-1];
        }
        ((__ndk1 *)param_1)[-1] = _Var19;
      }
      else if ((byte)_Var15 < (byte)_Var16) {
        *p_Var12 = _Var15;
        ((__ndk1 *)param_1)[-1] = _Var16;
        _Var15 = *p_Var10;
        if ((byte)*p_Var12 < (byte)_Var15) {
          *p_Var10 = *p_Var12;
          *p_Var12 = _Var15;
          goto joined_r0x0014004c;
        }
      }
LAB_0013fdf4:
      _Var15 = *p_Var12;
    }
    else {
      _Var16 = *p_Var10;
      _Var19 = *p_Var12;
      if ((byte)_Var16 < (byte)_Var19) {
        if ((byte)_Var15 < (byte)_Var16) {
          *p_Var12 = _Var15;
        }
        else {
          *p_Var12 = _Var16;
          *p_Var10 = _Var19;
          if ((byte)_Var19 <= (byte)((__ndk1 *)param_1)[-1]) goto LAB_0013fd84;
          *p_Var10 = ((__ndk1 *)param_1)[-1];
        }
        ((__ndk1 *)param_1)[-1] = _Var19;
      }
      else if ((byte)_Var15 < (byte)_Var16) {
        *p_Var10 = _Var15;
        ((__ndk1 *)param_1)[-1] = _Var16;
        _Var15 = *p_Var12;
        if ((byte)*p_Var10 < (byte)_Var15) {
          *p_Var12 = *p_Var10;
          *p_Var10 = _Var15;
        }
      }
LAB_0013fd84:
      _Var16 = p_Var12[1];
      _Var19 = ((__ndk1 *)param_1)[-2];
      p_Var9 = p_Var12 + (uVar13 - 1);
      _Var15 = *p_Var9;
      if ((byte)_Var15 < (byte)_Var16) {
        if ((byte)_Var19 < (byte)_Var15) {
          p_Var12[1] = _Var19;
        }
        else {
          p_Var12[1] = _Var15;
          *p_Var9 = _Var16;
          if ((byte)_Var16 <= (byte)((__ndk1 *)param_1)[-2]) goto LAB_0013fe20;
          *p_Var9 = ((__ndk1 *)param_1)[-2];
        }
        ((__ndk1 *)param_1)[-2] = _Var16;
      }
      else if ((byte)_Var19 < (byte)_Var15) {
        *p_Var9 = _Var19;
        ((__ndk1 *)param_1)[-2] = _Var15;
        _Var15 = p_Var12[1];
        if ((byte)*p_Var9 < (byte)_Var15) {
          p_Var12[1] = *p_Var9;
          *p_Var9 = _Var15;
        }
      }
LAB_0013fe20:
      _Var16 = p_Var12[2];
      _Var19 = ((__ndk1 *)param_1)[-3];
      p_Var14 = p_Var12 + uVar13 + 1;
      _Var15 = *p_Var14;
      if ((byte)_Var15 < (byte)_Var16) {
        if ((byte)_Var19 < (byte)_Var15) {
          p_Var12[2] = _Var19;
        }
        else {
          p_Var12[2] = _Var15;
          *p_Var14 = _Var16;
          if ((byte)_Var16 <= (byte)((__ndk1 *)param_1)[-3]) goto LAB_0013fe90;
          *p_Var14 = ((__ndk1 *)param_1)[-3];
        }
        ((__ndk1 *)param_1)[-3] = _Var16;
      }
      else if ((byte)_Var19 < (byte)_Var15) {
        *p_Var14 = _Var19;
        ((__ndk1 *)param_1)[-3] = _Var15;
        _Var15 = p_Var12[2];
        if ((byte)*p_Var14 < (byte)_Var15) {
          p_Var12[2] = *p_Var14;
          *p_Var14 = _Var15;
        }
      }
LAB_0013fe90:
      _Var15 = *p_Var10;
      _Var16 = *p_Var9;
      _Var19 = *p_Var14;
      if ((byte)_Var15 < (byte)_Var16) {
        if ((byte)_Var15 <= (byte)_Var19) {
          *p_Var9 = _Var15;
          *p_Var10 = _Var16;
          p_Var9 = p_Var10;
          _Var15 = _Var19;
          if ((byte)_Var16 <= (byte)_Var19) {
            _Var15 = *p_Var12;
            *p_Var12 = _Var16;
            *p_Var10 = _Var15;
            _Var15 = *p_Var12;
            goto joined_r0x0014004c;
          }
        }
LAB_0013ff04:
        *p_Var9 = _Var19;
        *p_Var14 = _Var16;
      }
      else if ((byte)_Var19 < (byte)_Var15) {
        *p_Var14 = _Var15;
        *p_Var10 = _Var19;
        p_Var14 = p_Var10;
        _Var15 = _Var16;
        if ((byte)_Var19 < (byte)_Var16) goto LAB_0013ff04;
        _Var15 = *p_Var12;
        *p_Var12 = _Var19;
        *p_Var10 = _Var15;
        _Var15 = *p_Var12;
        goto joined_r0x0014004c;
      }
      _Var16 = *p_Var12;
      *p_Var12 = _Var15;
      *p_Var10 = _Var16;
      _Var15 = *p_Var12;
    }
joined_r0x0014004c:
    this = p_Var12;
    if (((param_4 & 1) == 0) && ((byte)_Var15 <= (byte)p_Var12[-1])) {
      if ((byte)_Var15 < (byte)((__ndk1 *)param_1)[-1]) {
        do {
          this = this + 1;
        } while ((byte)*this <= (byte)_Var15);
      }
      else {
        do {
          this = this + 1;
          if (param_1 <= this) break;
        } while ((byte)*this <= (byte)_Var15);
      }
      p_Var10 = (__ndk1 *)param_1;
      if (this < param_1) {
        do {
          p_Var10 = p_Var10 + -1;
        } while ((byte)_Var15 < (byte)*p_Var10);
      }
      if (this < p_Var10) {
        _Var16 = *this;
        _Var19 = *p_Var10;
        do {
          *this = _Var19;
          *p_Var10 = _Var16;
          do {
            this = this + 1;
            _Var16 = *this;
          } while ((byte)_Var16 <= (byte)_Var15);
          do {
            p_Var10 = p_Var10 + -1;
            _Var19 = *p_Var10;
          } while ((byte)_Var15 < (byte)_Var19);
        } while (this < p_Var10);
      }
      p_Var10 = this + -1;
      if (p_Var10 != p_Var12) {
        *p_Var12 = *p_Var10;
      }
      param_4 = 0;
      *p_Var10 = _Var15;
      uVar5 = uVar5 - 1;
      goto LAB_0013fc6c;
    }
    uVar5 = uVar5 - 1;
    lVar8 = 0;
    do {
      lVar1 = lVar8 + 1;
      _Var16 = p_Var12[lVar8 + 1];
      lVar8 = lVar1;
    } while ((byte)_Var16 < (byte)_Var15);
    p_Var10 = p_Var12 + lVar1;
    p_Var9 = (__ndk1 *)param_1;
    if (lVar1 == 1) {
      do {
        if (p_Var9 <= p_Var10) break;
        p_Var9 = p_Var9 + -1;
      } while ((byte)_Var15 <= (byte)*p_Var9);
    }
    else {
      do {
        p_Var9 = p_Var9 + -1;
      } while ((byte)_Var15 <= (byte)*p_Var9);
    }
    if (p_Var10 < p_Var9) {
      _Var19 = *p_Var9;
      p_Var17 = p_Var10;
      p_Var18 = p_Var9;
      do {
        *p_Var17 = _Var19;
        *p_Var18 = _Var16;
        do {
          p_Var14 = p_Var17;
          p_Var17 = p_Var14 + 1;
          _Var16 = *p_Var17;
        } while ((byte)_Var16 < (byte)_Var15);
        do {
          p_Var18 = p_Var18 + -1;
          _Var19 = *p_Var18;
        } while ((byte)_Var15 <= (byte)_Var19);
      } while (p_Var17 < p_Var18);
    }
    else {
      p_Var14 = p_Var10 + -1;
    }
    if (p_Var14 != p_Var12) {
      *p_Var12 = *p_Var14;
    }
    *p_Var14 = _Var15;
    if (p_Var10 < p_Var9) {
LAB_00140014:
      __introsort<std::__ndk1::_ClassicAlgPolicy,std::__ndk1::ranges::less,char*,false>
                (p_Var12,(char *)p_Var14,param_2,(less)uVar5,param_4 & 1,SUB81(uVar6,0));
      param_4 = 0;
      this = p_Var14 + 1;
    }
    else {
      bVar2 = __insertion_sort_incomplete_abi_ne180000_<std::__ndk1::_ClassicAlgPolicy,std::__ndk1::ranges::less,char*>
                        ((char *)p_Var12,(char *)p_Var14,(less)param_2);
      bVar3 = __insertion_sort_incomplete_abi_ne180000_<std::__ndk1::_ClassicAlgPolicy,std::__ndk1::ranges::less,char*>
                        ((char *)(p_Var14 + 1),param_1,(less)param_2);
      if (bVar3) {
        param_1 = (char *)p_Var14;
        if (bVar2) {
          return;
        }
      }
      else {
        this = p_Var14 + 1;
        if (!bVar2) goto LAB_00140014;
      }
    }
  } while( true );
}


