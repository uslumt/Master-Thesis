primfn(DRAM_1_3: handle, DRAM_1_4: handle, DRAM_1_5: handle) -> ()
  attr = {"from_legacy_te_schedule": True, "global_symbol": "TVM-Mod", "tir.noalias": True}
  buffers = {DRAM_1_2: Buffer(DRAM_1_6: Pointer(int16), int16, [64896], []),
             DRAM_1_1: Buffer(DRAM_1_7: Pointer(int16), int16, [884736], []),
             DRAM_1: Buffer(DRAM_1_8: Pointer(int16), int16, [57600], [])}
  buffer_map = {DRAM_1_3: DRAM_1, DRAM_1_4: DRAM_1_1, DRAM_1_5: DRAM_1_2} {
  allocate(Filter_Buffer_1: Pointer(local int16), int16, [3456]), storage_scope = local;
  allocate(Input_Buffer_1: Pointer(local int16), int16, [57600]), storage_scope = local;
  allocate(Filter_RF_1: Pointer(wmma.matrix_b int16), int16, [884736]), storage_scope = wmma.matrix_b;
  allocate(Input_RF_1: Pointer(wmma.matrix_a int16), int16, [43264]), storage_scope = wmma.matrix_a;
  allocate(Output_RF_1: Pointer(wmma.accumulator int16), int16, [64896]), storage_scope = wmma.accumulator;
  allocate(Output_Buffer_1: Pointer(local int16), int16, [64896]), storage_scope = local {
    for (i0: int32, 0, 384) {
      @tir.tvm_call_packed("dma_copy_Filter_DMA_131", dtype=int32)
    }
    for (i3: int32, 0, 256) {
      @tir.tvm_call_packed("dma_copy_Input_DMA_155", dtype=int32)
    }
    attr [IterVar(i0_1: int32, (nullptr), "DataPar", "")] "pragma_Parallel" = 1 {
      for (kkw: int32, 0, 3) {
        for (kkh: int32, 0, 3) {
          for (kinput_c: int32, 0, 256) {
            for (output_c: int32, 0, 384) {
              @tir.tvm_call_packed("noc_copy_Filter_NoC_115", dtype=int32)
            }
          }
        }
      }
      for (ikw: int32, 0, 3) {
        for (ikh: int32, 0, 3) {
          for (input_c: int32, 0, 256) {
            for (ioutput_c: int32, 0, 384) {
              @tir.tvm_call_packed("noc_copy_Input_NoC_155", dtype=int32)
            }
          }
        }
      }
      for (output_h: int32, 0, 13) {
        for (kh: int32, 0, 3) {
          for (output_c_1: int32, 0, 384) {
            for (input_c_1: int32, 0, 256) {
              @tir.tvm_call_packed("mac_compute61", dtype=int32)
            }
          }
        }
      }
      for (kw: int32, 0, 3) {
        for (kh_1: int32, 0, 3) {
          for (input_c_2: int32, 0, 256) {
            for (output_c_2: int32, 0, 384) {
              @tir.tvm_call_packed("noc_copy_Output_NoC_136", dtype=int32)
            }
          }
        }
      }
      for (i3_1: int32, 0, 384) {
        @tir.tvm_call_packed("dma_copy_Output_DMA_146", dtype=int32)
      }
    }
  }
}
