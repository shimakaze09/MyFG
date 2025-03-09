//
// Created by Admin on 9/03/2025.
//

#include <MyFG/DX12/Executor.h>

 #include <MyFG/DX12/RsrcMngr.h>

 using namespace My::DX12;

void FG::Executor::Execute(const My::FG::Compiler::Result& crst, RsrcMngr& rsrcMngr)
{
  rsrcMngr.DHReserve();
  rsrcMngr.AllocateHandle();
  for (auto passNodeIdx : crst.sortedPasses) {
    const auto& passinfo = crst.idx2info.find(passNodeIdx)->second;

    for (const auto& rsrc : passinfo.constructRsrcs)
      rsrcMngr.Construct(rsrc);

    auto passRsrcs = rsrcMngr.RequestPassRsrcs(passNodeIdx);
    passFuncs[passNodeIdx](passRsrcs);

    for (const auto& rsrc : passinfo.destructRsrcs)
      rsrcMngr.Destruct(rsrc);
  }
}
