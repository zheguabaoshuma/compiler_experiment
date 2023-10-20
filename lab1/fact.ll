define i32 @factorial(i32) {
entry:
  %eq = icmp eq i32 %0, 0   
  br i1 %eq, label %then, label %else

then:                                             ; preds = %entry
  br label %ifcont

else:                                             ; preds = %entry
  %sub = sub i32 %0, 1   
  %1 = call i32 @factorial(i32 %sub) 
  %mult = mul i32 %0, %1  
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  %iftmp = phi i32 [ 1, %then ], [ %mult, %else ]
  ret i32 %iftmp
}

define i32 @main(){
  %result= call i32 @factorial(i32 9)
  ret i32 %result
}
