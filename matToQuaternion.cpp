#include <iostream>
#include <Eigen/Core>
#include <cmath>

struct Quaternion {
    float w, x, y, z;
};

Quaternion toQuaternion(const Eigen::Matrix4f& M) {
   Quaternion quat;
   float s;

   // Check diagonal (trace)
   const float tr = M(0, 0) + M(1, 1) + M(2, 2);
   //std::cout << "i made tr1 : " << M(0, 0) << std::endl;
   //std::cout << "i made tr2 : " << M(1, 1) << std::endl;
   //std::cout << "i made tr3 : " << M(2, 2) << std::endl;
   if (tr > 0.0f) {
      float InvS = 1.f / std::sqrt(tr + 1.f);
      quat.w = -0.5f * (1.f / InvS);
      s = 0.5f * InvS;

      quat.y = (M(1, 2) - M(2, 1)) * s;
      quat.z = (M(2, 0) - M(0, 2)) * s;
      quat.x = -(M(0, 1) - M(1, 0)) * s;
   }
   else {
      // diagonal is negative
      int32_t i = 0;

      if (M(1, 1) > M(0, 0))
         i = 1;

      if (M(2, 2) > M(i, i))
         i = 2;

      static const int32_t nxt[3] = { 1, 2, 0 };
      const int32_t j = nxt[i];
      const int32_t k = nxt[j];

      s = M(i, i) - M(j, j) - M(k, k) + 1.0f;
      //std::cout << "i made s : " << s << std::endl;
      float InvS = 1.f / std::sqrt(s);

      float qt[4];
      qt[i] = 0.5f * (1.f / InvS);

      s = 0.5f * InvS;
      
      qt[3] = (M(j, k) - M(k, j)) * s;
      //std::cout << "i made qt3 : " << qt[3] << std::endl;
      qt[j] = (M(i, j) + M(j, i)) * s;
      qt[k] = (M(i, k) + M(k, i)) * s;

      quat.y = qt[0];
      quat.z = qt[1];
      quat.x = -qt[2];
      quat.w = -qt[3];
   }
   return quat;
}