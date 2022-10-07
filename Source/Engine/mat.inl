#include <corecrt_math.h>

namespace sl{

    template <size_t Dim, typename T> mat<Dim, T> operator*(const mat<Dim, T>& l, const mat<Dim, T>& r){
        mat<Dim,T> ret{};
        for(size_t i=0;i<Dim;++i){
            for(size_t j=0;j<Dim;++j){
                float dot=0;
                vec<Dim,T> col=r.Col(j);
                for(size_t d=0;d<Dim;++d){
                    dot+=l.rows[i][d]*col[d];
                }
                ret.rows[i][j]=dot;
            }
        }
        return ret;
    }

    template <size_t Dim, typename T> vec<Dim, T> operator*(const mat<Dim, T>& m, const vec<Dim,T>& f){
        vec<Dim,T> ret{};
        for(size_t i=0;i<Dim;++i){
            ret[0]=Dot(m.rows[i],f);
        }
        return ret;
    }
    
    template<size_t Dim,typename T>
    mat<Dim,T> operator*(const mat<Dim,T>& m, float f){
        mat<Dim,T> ret{};
        for(size_t i=0;i<Dim;++i){
            for(size_t j=0;j<Dim;++j){
                ret.rows[i][j]=m.rows[i][j]*f;
            }
        }
        return ret;
    }

    template <size_t Dim, typename T> bool operator==(const mat<Dim, T>& l, const mat<Dim, T>& r){
        for(size_t i=0;i<Dim;++i){
            for(size_t j=0;j<Dim;++j){
                if(fabsf(l.rows[i][j]-r.rows[i][j])>MAT_EPSILON){
                    return false;
                }
            }
        }
        return true;
    }

    template <size_t Dim, typename T> bool operator!=(const mat<Dim, T>& l, const mat<Dim, T>& r){
        return !operator==(l,r);
    }

    template <size_t Dim, typename T> mat<Dim, T> Transposed(const mat<Dim, T>& m){
        mat<Dim,T> ret{};
        for(size_t i=0;i<Dim;++i){
            for(size_t j=0;j<Dim;++j){
                ret.rows[i][j]=m.rows[j][i];
            }
        }
        return ret;
    }

    template <size_t Dim, typename T> mat<Dim - 1, T> Cut(const mat<Dim, T>& m, int r, int c){
        assert(r<Dim&&c<Dim);
        mat<Dim-1,T> ret{};
        for(size_t i=0;i<Dim-1;++i){
            for(size_t j=0;j<Dim-1;++j){
                ret.rows[i][j]=m.rows[i<r ? i:i+1][j<c ? j:j+1];
            }
        }
        return ret;
    }

    template <size_t Dim, typename T> mat<Dim, T> Minor(const mat<Dim, T>& m){
        mat<Dim,T> ret{};
        for(size_t i=0;i<Dim;++i){
            for(size_t j=0;j<Dim;++j){
                ret.rows[i][j]=Determinant(Cut(m,i,j));
            }
        }
        return ret;
    }

    template <size_t Dim, typename T> mat<Dim, T> Cofactor(const mat<Dim, T>& m){
        auto minor=Minor(m);
        for(size_t i=0;i<Dim;++i){
            for(size_t j=0;j<Dim;++j){
                minor.rows[i][j]=minor.rows[i][j]*((i+j)%2==0 ? 1: -1);
            }
        }
        return minor;
    }

    template <size_t Dim, typename T> float Determinant(const mat<Dim, T>& m){
        auto confactor=Cofactor(m);
        float sum=0;
        for(size_t j=0;j<Dim;++j){
            sum+=confactor.rows[0][j]*m.rows[0][j];
        }
        return sum;
    }
    
    template <typename T> float Determinant(const mat<1, T>& m){
        return m.rows[0][0];
    }
    
    template <typename T> float Determinant(const mat<2, T>& m){
        return m.rows[0][0]*m.rows[1][1]-m.rows[0][1]*m.rows[1][0];
    }
    

    template <size_t Dim, typename T> mat<Dim, T> Adjugate(const mat<Dim, T>& m){
        return Transposed(Cofactor(m));
    }

    template <size_t Dim, typename T> mat<Dim, T> Inverse(const mat<Dim, T>& m){
        float det = Determinant(m);

        if (det < 0.0000001f && det > -0.0000001f) {
            std::cout << "ERROR: Can't invert 4x4 matrix with no determinant\n";
            return {};
        }

        auto adjugate = Adjugate(m);
        float invDet = 1.0f / det;

        auto ret = adjugate * invDet;
        return ret;
    }
}
