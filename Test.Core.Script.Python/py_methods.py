import Sekai

tc1 = Sekai.TestClass()
tc1.Method1()

assert(tc1.methodID == 1)

tc2 = Sekai.TestClass()
tc2.Method2()

assert(tc2.methodID == 2)

tc1.Method1()
tc2.Method1()

assert(tc1.methodID == 1)

assert(tc2.methodID == 1)
