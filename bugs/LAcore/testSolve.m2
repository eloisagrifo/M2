testSolve = (n,F) -> (
    M := matrix fillMatrix mutableMatrix(F,n,n);
    b := matrix fillMatrix mutableMatrix(F,n,1);
    elapsedTime x := solve(M, b, ClosestFit => true);
    norm(b - M*x)
    )
end--

restart
load "testSolve.m2"

testSolve(10, CC_100)
 -- 0.0811792 seconds elapsed
    -- 8.38570644846520377471431308894e-30
testSolve(100, CC_100)
 -- 9.53715 seconds elapsed
    -- 2.58867804138806926438240058111e-28
testSolve(10, CC_500)
 -- 0.147878 seconds elapsed
    -- 1.09427398375168651037881303470217169142582156335187465730640040262045674692139949525577397600850856973767817696582326126443125610249223071196741115092e-149
testSolve(100, CC_500)
 -- 19.1503 seconds elapsed
    -- 1.34257415168664592567817742806711438060451543867114556623965902973386881690195349503392712637111273083176445131345392247230352805675895311865196098888e-148
testSolve(100,CC_53)
 -- 0.0318108 seconds elapsed
    -- 2.64263982371124e-14
testSolve(500,CC_53)
 -- 0.896753 seconds elapsed
    -- 4.30006541585593e-14