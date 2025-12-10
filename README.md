고려대 SW아카데미 9조 – Cornell Grasp + Shared AlexNet + Arduino Gripper

1. 프로젝트 개요

이 저장소는 **Cornell Grasp Dataset**을 사용해

- 16개 물체 카테고리 분류(`classification`)와  
- Grasp 파라미터 6차원 회귀(`regression`: cx, cy, h, w, sin(2θ), cos(2θ))

를 동시에 수행하는 **Shared AlexNet** 모델을 구현하고,  
예측된 그리퍼 폭을 **아두이노 서보 모터 각도**로 변환하여  
실제 물체를 집어보는 **엔드 투 엔드 시스템**을 포함합니다.

구성:
1. Colab에서 학습 및 CSV/라벨 전처리 (`colab_1grasp.ipynb`)
2. 로컬 Jupyter에서 웹캠 + PyTorch 모델 + 아두이노 시리얼 제어 (`githubsubmit/1grasp.ipynb`)
3. 아두이노에서 서보 모터 제어 (`githubsubmit/arduino/1grasp.ino`)


2. 폴더 및 파일 구조

```text
.
├─ colab_1grasp.ipynb              # Colab용 학습/전처리 노트북
├─ Re_cornell_class_labels_16.csv  # Cornell 이미지별 16-class 라벨 CSV
├─ githubsubmit/
│   ├─ 1grasp.ipynb                # 로컬 Jupyter: 웹캠 + 모델 + 아두이노 제어
│   └─ arduino/
│       └─ 1grasp.ino              # 아두이노 서보 제어 코드
└─ shared_alexnet_grasp.pth        # 학습된 모델 가중치 (아래 3번 링크 참고)


3. 모델 가중치 다운로드
학습된 Shared AlexNet + Grasp 모델 가중치 파일:
shared_alexnet_grasp.pth
Google Drive 링크:
https://drive.google.com/file/d/1nkgaymh36XQ_nHE7BLBczche0KVdfAqB/view?usp=sharing
로컬에서 실행할 때는 위 파일을 다운로드해서,
githubsubmit/1grasp.ipynb 안의 CKPT_PATH를 자신의 경로로 설정하면 됩니다.

4. 실행 방법
4.1. Colab에서 학습 (선택)
colab_1grasp.ipynb를 Colab에서 연다.
Google Drive에 Cornell Grasp Dataset 원본을 archive/ 구조로 넣어 둔다.
노트북 상단의 경로(ARCHIVE_ROOT, LABEL_CSV)를 자신의 드라이브 경로에 맞게 수정한다.
셀을 순서대로 실행해서
cornell_labels_16_with_grasp.csv 생성
Shared AlexNet 학습
shared_alexnet_grasp.pth 저장
학습이 끝난 shared_alexnet_grasp.pth를 로컬로 다운로드한다.
(현재 드라이브 링크에 올라간 파일은 이 과정을 통해 생성한 가중치이다.)

4.2. 로컬 Jupyter + 아두이노
Python 패키지 설치 (터미널 / Anaconda Prompt):

bash
코드 복사
pip install torch torchvision opencv-python pillow numpy pyserial
shared_alexnet_grasp.pth를 로컬 적당한 위치에 둔다. (예: C:\Users\USER\Downloads\workspace\shared_alexnet_grasp.pth)
아두이노를 USB로 연결하고, Arduino IDE에서 포트를 확인한다. (예: COM4)
githubsubmit/arduino/1grasp.ino를 Arduino IDE로 열어 업로드한다.
Jupyter Notebook에서 githubsubmit/1grasp.ipynb를 열고, 상단의 설정을 자신의 환경에 맞게 수정한다.

python
코드 복사
CKPT_PATH = r"C:\Users\USER\Downloads\workspace\shared_alexnet_grasp.pth"
PORT      = "COM4"  # 실제 아두이노 포트
노트북 셀을 위에서 아래로 순서대로 실행한다.
OpenCV 창이 뜨면 웹캠에 물체를 보여주고,
창에 표시되는 w, grip 값 변화와 실제 그리퍼 움직임을 확인한다.
종료할 때는 OpenCV 창에 포커스를 두고 q 키를 누른다.

5. 데이터셋
원본 Cornell Grasp Dataset은 라이선스 문제로 이 저장소에 포함하지 않았습니다.
공식 Cornell Grasp Dataset 페이지에서 직접 다운로드 후,
Colab 노트북(colab_1grasp.ipynb)의 ARCHIVE_ROOT 경로에 맞게 배치하여 사용합니다.
