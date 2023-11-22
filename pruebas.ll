; ModuleID = 'SHELL'
source_filename = "SHELL"

define void @_anonIFELSE_() {
entry:
  br i1 true, label %then_Block, label %else_Block

then_Block:                                       ; preds = %entry

else_Block:                                       ; preds = %entry

merge_Block:                                      ; preds = %entry, %entry
}

define double @_anon_() {
entry:
  ret double 1.000000e+01
  br label %merge_Block
}

define double @_anon_.1() {
entry:
  ret double 8.000000e+00
  br label %merge_Block
}
