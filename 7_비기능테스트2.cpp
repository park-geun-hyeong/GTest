// 7_비기능테스트2.cpp

#include <iostream>
#include <string>

class Image {
    std::string url;

public:
    Image(const std::string& s)
        : url(s)
    {
    }

    void Draw() const
    {
        std::cout << "Draw Image: " << url << std::endl;
    }

    // * 객체에 대한 메모리 할당/해지의 동작을 재정의해주어야 합니다.
    // new Image
    // 1) 메모리 할당 => operator new
    // 2) 생성자 호출

    // * 테스트 코드에서 메모리 검증을 위해서는 아래 코드가
    //   제품 코드에 미리 정의되어 있어야 합니다.
    static int alloc;

    void* operator new(size_t size)
    {
        ++alloc;
        return malloc(size);
    }

    // delete p;
    // 1) 소멸자 호출
    // 2) 메모리 해지 => operator delete
    void operator delete(void* p, size_t)
    {
        free(p);
        --alloc;
    }
};
int Image::alloc = 0;

void DrawImage(const std::string& url)
{
    Image* image = new Image(url);
    image->Draw();

    // new Image(url);
    // new Image(url);

    // delete image;
}

//----
#include <gtest/gtest.h>

// DrawImage를 수행할 때, Image 객체의 메모리 해지가
// 제대로 되는지 여부를 검증하고 싶다.
TEST(ImageTest, DrawImage)
{
    int alloc = Image::alloc;
    DrawImage("https://a.com/a.jpg");
    int diff = Image::alloc - alloc;
    EXPECT_EQ(diff, 0) << diff << " object(s) leaked";
}