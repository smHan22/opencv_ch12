# opencv_ch12-1 레이블링과 외곽선 검출

실습과제 1)

-labelex.png 영상파일(컬러영상)에서 레이블링을 수행하고 객체의 면적이 최대, 최소인 객체를 찾고 아래처럼 콘솔창에 정보를 출력하고 원본영상에 바운딩 박스를 그리시오

● 이미지를 흑백으로 불러와서 이진화하여 객체를 검출하고, 그 객체 라벨링

● minSize변수를 int형의 최대값으로 초기화하여, 발견된 객체중에서 가장 작은 크기를 저장. maxSize는 0으로 초기화하여 발견된 객체중 가장 큰 크기를 저장.

● 초기값이 -1인 이유는 가장 작은 객체를 찾지 못했기 때문이며, minIdx에는 발견된 객체중에서 가장 작은 크기를 가진 객체의 레이블을 저장.

● 반복문을 통해 객체의 인덱스를 1부터 시작하여 마지막 객체까지 확인. (0번 인덱스는 배경이므로 무시)

● 조건문에서는 현재 객체의 크기를 비교하여 minSize와 minIdx에는 가장 작은 크기를 가진 객체의 크기와 레이블이 저장되고, maxSize와 maxIdx에는 가장 큰 크기를 가진 객체의 크기와 레이블이 저장.

● 최대 크기 객체가 존재하는 경우 해당 객체의 중심좌표를 계산해서 최대 크기 객체에 빨간색 바운딩 박스 그림. 최소 크기 객체가 존재하는 경우에는 해당 객체에 바운딩 박스 그림.


![캡처](https://github.com/smHan22/opencv_ch12-1/assets/90818408/9dab093d-5e79-4a8c-bec1-37c227d2ab29)





실습과제 2)

-polygon.bmp 영상파일에서 레이블링을 수행하고 다음 처럼 콘솔창에 아래와 같은 정보를 출력하고 영상원본에 바운딩 박스와 레이블값을 그려주는 코드를 작성하시오. color는 무게중심 좌표에서 원본 영상의 컬러를 출력할 것.

● 주어진 이미지에서 다른값을 사용하면 도형 하나가 인식이 안 돼서 150을 사용함.

● 레이블, 통계, 중심점 저장

● 반복문에서 분석한 각 요소에 대해 반복하며, 임계값을 20으로 주어 너무 작은 요소는 무시함.

● rectangle함수 사용하여 주어진 좌표와 크기로 노란색 사각형 그린 후, 각 요소의 좌표와 크기, 넓이 출력

● putText 함수 사용하여 레이블 번호를 도형 중심에 표시

![2](https://github.com/smHan22/opencv_ch12-1/assets/90818408/969029af-f2e9-4272-a4cd-2865b30be30c)





실습과제 3)

-polygon.bmp 영상파일에서 레이블링을 수행하고 각 객체의 무게중심을 직접 계산하여 아래 처럼 화면에 출력하시오.

● 각 객체의 무게 중심을 계산하기 위해 첫 번째 반복문 수행

● 픽셀 개수와 좌표의 합을 저장해줄 변수 초기화

● 객체 내부 모든 픽셀에 대한 반복 시행 후 이진화 이미지에서 흰색 픽셀인 경우 픽셀 개수와 좌표의 합 증가

● 무게 중심 좌표 출력

![3](https://github.com/smHan22/opencv_ch12-1/assets/90818408/acc398d3-b9e5-4f70-bca6-6fee6a12c806)





실습과제 4)

-자동차의 번호판 영역을 검출하여 빨간색으로 표시하라.

●  connectedComponentsWithStats 함수를 사용하여 이진화된 이미지에서 연결된 객체들의 특성을 추출.

● 이진화된 이미지에서 연결된 객체의 개수와 각 객체의 레이블, 통계 정보, 좌표를 반환.

● 객체들에 대한 반복문을 수행하고 stats 행렬에서 i번째 행의 4번째 열의 값을 읽어와 area변수에 저장.

● 객체의 크기 조건을 설정한 후, 바운딩 박스의 좌상단 x, y, width, height를 stats에서 가져옴.

● Point를 사용하여 좌상단과 우하단 좌표를 지정하고 빨간색으로 번호판에 바운딩 박스를 그림.

![4](https://github.com/smHan22/opencv_ch12-1/assets/90818408/795dcc75-a6ce-4018-a767-0d2d08b2c1ca)


# opencv_ch12-2 레이블링과 외곽선 검출

실습과제 1)

-polygon.bmp 영상파일에서 아래 처럼 객체의 외곽선을 그려주는 프로그램을 작성하시오.

● 이미지를 그레이스케일로 변환한 이미지와 이진화된 이미지를 저장할 Mat 객체 생성

● contours는 윤곽선을 저장할 벡터를 생성

● 이진화된 이미지에서 윤곽선을 찾아 contours에 저장 (RETR_TREE는 윤곽선을 찾을 방법을 지정하고, CHAIN_APPROX_NONE는 윤곽선을 표현할 방법을 지정)

● 반복문에서는 찾은 윤곽선을 확인하면서 각 윤곽선을 랜덤한 색상으로 그려줌

<img width="609" alt="image" src="https://github.com/smHan22/opencv_ch12/assets/90818408/8d18e0fa-3c64-4be8-845b-1917cb40f7d9">

<img width="508" alt="image" src="https://github.com/smHan22/opencv_ch12/assets/90818408/599c4da5-6086-4e1c-a8ff-9cccf6072fb1">


실습과제 2)

-코드 12-1의 Mat 객체에 저장된 영상에 대하여 모든 외곽선을 찾아서 각 외곽선을 구성하는 점들을 모두 화면에 출력해 보시오.

● 이진화된 이미지 데이터를 사용하여 Mat객체 생성, 이진화된 이미지 데이터의 값을 0과 255사이로 조정하기 위해 *255사용

● 윤곽선을 저장할 벡터를 생성

● findContours로 이진화된 이미지에서 윤곽선을 찾아 contours에 저장

● 첫 번째 반복문에서 모든 윤곽선에 대해 반복하고, 중첩 반복문에서는 현재 윤곽선을 이루는 점들의 좌표를 출력

<img width="629" alt="image" src="https://github.com/smHan22/opencv_ch12/assets/90818408/4e6b27ad-6b1c-4371-adb5-f4e11c0d6faa">

<img width="654" alt="image" src="https://github.com/smHan22/opencv_ch12/assets/90818408/6bf3cff0-c58c-405e-b7f3-dddcf95aca3b">


실습과제 3)

-labelex.png 영상에서 drawContours() 함수를 사용하지 말고 외곽선을 직접 그려주는 코드를 작성하시오.

-외곽선을 구성하는 모든 이웃하는 2개의 점을 직선(line 함수)으로 이어주면 됨.

● 이미지를 그레이스케일로 변환한 이미지와 이진화된 이미지를 저장할 Mat 객체 생성

● contours는 윤곽선을 저장할 벡터를 생성

● 이진화된 이미지에서 윤곽선을 찾아 contours에 저장 (RETR_TREE는 윤곽선을 찾을 방법을 지정하고, CHAIN_APPROX_NONE는 윤곽선을 표현할 방법을 지정)

● 첫 번째 반복문 contours.size()는 벡터의 크기, 윤곽선의 개수이며, 중첩 반복문의 contours[i].size()는 contours 벡터의 i 번째 요소에 해당하는 윤곽선의 점의 개수. -1을 한 이유는 각 선분을 연결할 때 마지막 점과 첫 번째 점을 연결하는 것인데 마지막 점은 처리하지 않기 위해서

● 첫 번째 line 함수의 contours[i][j]는 i번째 윤곽선의 j번째 점에서 시작한다는 것이고, contours[i][j+1]은 j+1번째 점까지 연결한다는 것. (순차적으로 연결하여 윤곽선을 그리기 위함)

● 두 번째 line 함수의 contours[i]는 i번째 윤곽선, contours[i].size() - 1은 윤곽선의 마지막 점. contours[i][0]은 해당 윤곽선의 첫 번째 점.

<img width="626" alt="image" src="https://github.com/smHan22/opencv_ch12/assets/90818408/df4ca8ba-fcd0-43ea-9ed6-024506692572">

<img width="323" alt="image" src="https://github.com/smHan22/opencv_ch12/assets/90818408/5abcbba2-aeb0-4c1f-9b25-ceaa44f460e0">


실습과제 4)

-labelex.png 영상에서 외곽선의 길이를 출력하고 외곽선의 길이가 최대인 외곽선을 찾아서 외곽선을 그리시오.

-외곽선의 길이는 외곽선을 구성하는 점의 개수로 정의한다.

● 이미지를 그레이스케일, 이진화로 변환

● findContours는 이진화된 이미지에서 외곽선을 검출

● 첫 번째 반복 루프에서는 외곽선을 반복하며, 포인트 수를 출력

● maxlong 변수는 첫 번째 외곽선의 크기로 초기화

● 두 번째 반복 루프에서는 각 외곽선을 반복하며, 가장 긴 외곽선을 찾음.

● drawContours는 가장 긴 외곽선을 원본 이미지에 빨간색으로 그림

<img width="634" alt="image" src="https://github.com/smHan22/opencv_ch12/assets/90818408/aa11e736-6e89-4268-b672-52a70792faf0">

<img width="587" alt="image" src="https://github.com/smHan22/opencv_ch12/assets/90818408/512723a8-3a38-46b4-902f-b4e5bd6e359b">



실습과제 5)

-char_c.png 영상에서 열려있는 방향을 구하시오. 열린방향이 왼쪽이면 외곽선을 파란색으로 그려주고 열린방향이 오른쪽이면 외곽선을 빨간색으로 그리시오.

● 이미지를 그레이스케일, 이진화로 변환

● findContours로 이진화된 이미지에서 외곽선을 검출

● connectedComponentsWithStats로 이진화된 이미지에서 연결된 구성 요소를 찾고 각 구성 요소의 통계 및 중심점을 계산

● 각 구성 요소의 중심점 x좌표를 centroids에서 읽어와 x벡터에 추가

● 중심점 x[i]가 해당 외곽선의 바운딩 박스의 중앙 x좌표보다 큰 경우 파란색으로 그리고, 작은 경우에는 빨간색으로 그림

<img width="365" alt="image" src="https://github.com/smHan22/opencv_ch12/assets/90818408/74175642-b1fd-4844-927c-2b4d49bdf276">

<img width="554" alt="image" src="https://github.com/smHan22/opencv_ch12/assets/90818408/72b06e35-c7f0-437d-8916-23b21826850e">

opencv_ch12-3 레이블링과 외곽선 검출

실습과제 1)

● 이미지 그레이스케일, 이진화 변환

● findContours는 이진화된 이미지에서 외곽선을 검출

● boundingRect는 외곽선을 포함하는 최소 직사각형을 계산

● minAreaRect는 외곽선을 포함한느 최소 면적의 회전 직사각형을 계산, points 메서드는 회전 직사각형의 네 점을 rect_points 배열에 저장

● minEnclosingCircle은 외곽선을 포함하는 최소 원을 계산하여 중심과 반지름을 반환

<img width="361" alt="image" src="https://github.com/smHan22/opencv_ch12/assets/90818408/0b12902b-f60f-4d3c-9dc8-70028cc06496">

<img width="277" alt="image" src="https://github.com/smHan22/opencv_ch12/assets/90818408/ca780918-fa4b-4647-885a-914376c18ff7">

실습과제 2)

● 이미지 그레이스케일, 이진화 변환

● findContours는 이진화된 이미지에서 외곽선을 검출

● 첫 번째 반복 루프에서 minAreaRect는 외곽선을 포함하는 최소 면적의 회전 직사각형을 계산

● getRotationMatrix2D는 중심점을 기준으로 주어진 각도 angle만큼의 회전 변환 행렬을 생성, 1.0은 스케일 값을 의미하며, 크기 변경 없이 회전만 수행

● warpAffine는 주어진 회전 변환 행렬 rot_mat을 사용하여 원본 이미지를 회전시겨 rotated에 저장

<img width="370" alt="image" src="https://github.com/smHan22/opencv_ch12/assets/90818408/008dc709-8336-47cc-812e-7cc9aeee5096">

<img width="1039" alt="image" src="https://github.com/smHan22/opencv_ch12/assets/90818408/296da031-392e-4bd3-8299-fe0e61139c8f">

실습과제 3)

● 이미지 그레이스케일 및 이진화 변환

● findContours는 이진화된 이미지에서 외곽선 검출

● arcLength는 외곽선의 둘레를 계산, true는 외관선이 닫혀 있음을 나타냄

● approxPolyDP는 외곽선을 다각형으로 근사화. 0.04 * peri는 근사화 정밀도를 결정하는 매개변수

● approx.size()를 통해 다각형의 꼭짓점 수를 확인하여 도형 구분, 그 외의 경우 contourArea로 외곽선의 면적을 계산하고, arcLength로 둘레를 다시 계산한 후, 원형도를 계산.

● 값이 0.85 이상이면 원으로 간주

<img width="371" alt="image" src="https://github.com/smHan22/opencv_ch12/assets/90818408/9a062edd-8dfa-4166-9d10-55aa8bf34f93">

<img width="551" alt="image" src="https://github.com/smHan22/opencv_ch12/assets/90818408/ed0c57a5-c41e-480a-b0e6-89bc5c4490fc">

실습과제 4)

● 이미지 그레이스케일, 이진화 변환

● findContours는 이진화된 이미지에서 외곽선을 검출

● arcLength는 외곽선의 둘레를 계산. true는 외곽선이 닫혀 있음을 나타냄. approxPolyDP는 외곽선을 다각형으로 근사화. 0.04 * peri는 근사화 정밀도를 결정하는 매개변수

● approx.size()를 통해 다각형의 꼭짓점 수를 확인하여 도형 구분

● 각 도형의 경우, 둘레 길이와 면적을 계산하여 각 변수에 저장. 그 외의 경우, 원형도를 계산하여 원으로 분류

<img width="370" alt="image" src="https://github.com/smHan22/opencv_ch12/assets/90818408/d6da43b1-478d-49ab-af1c-3ec75776b5e7">

<img width="557" alt="image" src="https://github.com/smHan22/opencv_ch12/assets/90818408/9471177b-5bff-4996-b22e-a8885af8ebaa">

실습과제 5)

● 






