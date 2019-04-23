# Multi-camera object tracking using surprisal observations in visual sensor networks Open Access 使用多摄像机对象跟踪在视觉传感器中的惊人观察网络

## Abstract

#### In this work, we propose a multi-camera object tracking method with surprisal observations based on the cubature information filter in visual sensor networks. In multi-camera object tracking approaches, multiple cameras observe an object and exchange the object’s local information with each other to compute the global state of the object. The information exchange among the cameras suffers from certain bandwidth and energy constraints. Thus, allowing only a desired number of cameras with the most informative observations to participate in the information exchange is an efficient way to meet the stringent requirements of bandwidth and energy. In this paper, the concept of surprisal is used to calculate the amount of information associated with the observations of each camera. Furthermore, a surprisal selection mechanism is proposed to facilitate the cameras to take independent decision on whether their observations are informative or not. If the observations are informative, the cameras calculate the local information vector and matrix based on the cubature information filter and transmit them to the fusion center. These cameras are called as surprisal cameras. The fusion center computes the global state of the object by fusing the local information from the surprisal cameras. Moreover, the proposed scheme also ensures that on average, only a desired number of cameras participate in the information exchange. The proposed method shows a significant improvement in tracking accuracy over the multi-camera object tracking with randomly selected or fixed cameras for the same number of average transmissions to the fusion center.

#### 在这项工作中，我们提出了一种基于视觉传感器网络中的立方体信息过滤器的具有惊人观察的多相机物体跟踪方法。在多相机对象跟踪方法中，多个相机观察对象并相互交换对象的本地信息以计算对象的全局状态。摄像机之间的信息交换受到一定的带宽和能量限制。因此，仅允许具有最丰富信息的观察的所需数量的摄像机参与信息交换是满足带宽和能量的严格要求的有效方式。在本文中，惊人的概念用于计算与每个摄像机的观察相关的信息量。此外，提出了一种令人惊讶的选择机制，以便于摄像机独立决定他们的观察是否有信息。如果观察结果是信息性的，则摄像机基于立方体信息滤波器计算局部信息矢量和矩阵，并将它们发送到融合中心。这些相机被称为惊人的相机。融合中心通过融合来自惊人相机的本地信息来计算对象的全局状态。此外，所提出的方案还确保平均而言，只有期望数量的摄像机参与信息交换。所提出的方法显示了对于使用随机选择的或固定的摄像机进行多摄像机对象跟踪的跟踪精度的显着改进，用于与融合中心的相同数量的平均传输。



### 1. Introduction
Object tracking is an extensively studied topic in visual sensor networks (VSN). A VSN is a network composed of smart cameras; they capture, process, and analyze the image data locally and exchange extracted information with each other [1]. The main applications of a VSN are indoor and/or outdoor surveillance, e.g., airports, massive waiting rooms, forests, deserts, inaccessible locations, and natural environments [2]. In general, the typical task of a VSN is to detect and track specific objects. The objects are usually described by a state that includes various characteristics of the objects such as position, velocity, appearance, behavior, shape, and color. These states can be used to detect and track the objects. Recursive state estimation algorithms are predominantly used to track objects in a VSN [3].

对象跟踪是视觉传感器网络（VSN）中广泛研究的主题。 VSN是由智能相机组成的网络;他们在本地捕获，处理和分析图像数据，并相互交换提取的信息[1]。 VSN的主要应用是室内和/或室外监视，例如机场，大型候车室，森林，沙漠，难以到达的位置和自然环境[2]。通常，VSN的典型任务是检测和跟踪特定对象。物体通常由包括物体的各种特征的状态描述，例如位置，速度，外观，行为，形状和颜色。这些状态可用于检测和跟踪对象。递归状态估计算法主要用于跟踪VSN中的对象[3]。

In [4–11], the authors presented several Kalman filter (KF)-based object tracking methods. Extended Kalman filter (EKF)-based object tracking method is proposed in [12]. The unscented Kalman filter (UKF) is applied for visual contour tracking in [13] and object tracking in [14]. In terms of object tracking in a VSN, the cubature Kalman filter (CKF) is primarily applied in our previous work [15]. In [16–24], the authors presented particle filter (PF)-based object tracking. The object tracking methods based on these conventional Bayesian filters have a varying degree of complexity and accuracy.

在[4-11]中，作者提出了几种基于卡尔曼滤波器（KF）的物体跟踪方法。在[12]中提出了基于扩展卡尔曼滤波器（EKF）的目标跟踪方法。无迹卡尔曼滤波器（UKF）应用于[13]中的视觉轮廓跟踪和[14]中的物体跟踪。在VSN中的目标跟踪方面，立方卡尔曼滤波器（CKF）主要应用于我们以前的工作[15]。在[16-24]中，作者提出了基于粒子滤波器（PF）的对象跟踪。基于这些传统贝叶斯滤波器的对象跟踪方法具有不同程度的复杂性和准确性。




In general, the performance of the tracking algorithms suffers from different adverse effects such as distance or orientation of the camera, and occlusions. However, a VSN with overlapping field of views (FOVs) is capa- ble of providing multiple observations of the same object simultaneously. The authors in [25] presented a dis- tributed and collaborative sensing mechanism to improve the observability of the objects by dynamically changing the camera’s pan, tilt, and zoom. Other examples of dis- tributed object tracking methods are presented in [26] and [27].

Recently, information filters have emerged as suitable methods for multi-sensor state estimation [28]. In infor- mation filtering, the information vector and matrix are computed and propagated over time instead of the state vector and its error covariance. The information matrix is the inverse of the state error covariance matrix. The infor- mation vector is the product of the information matrix and state vector. The information filters have an inher- ent information fusion mechanism which makes them more suitable for multi-camera object tracking. A more detailed description of information filters is given in Section 3. The authors in [29] and [30] presented informa- tion weighted consensus-based distributed object track- ing with an underlying KF or a distributed maximum likelihood estimation. In our work [31], we have pre- sented a robust cubature information filter (CIF)-based distributed object tracking in VSNs. However, the limited processing, communication, and energy capabilities of the cameras in a VSN present a major challenge.

Nowadays, VSNs tend to evolve into large-scale net- works with limited bandwidth and energy reservoirs. This allows a large number of cameras to observe a single object. In spite of the improved tracking accuracy, the information exchange of the large number of observations among the cameras increases the communication over- head and energy consumption. Hence, allowing only a desired number of cameras to participate in the informa- tion exchange is a way to meet the stringent requirements of bandwidth and energy.

Estimating an object’s state with a selected set of cam- eras is a well-investigated topic. Several camera selection mechanisms have been proposed in literature to minimize and/or maximize different metrics such as estimation accuracy, monitoring area, number of transmissions, and amount of data transfer. In [32], the authors presented an object tracking method based on fuzzy automaton in handing over to expand the monitoring area. This method selects a single best camera to control and track the objects by comparing its rank with the neighboring cam- eras. This method fails to select multiple cameras, and cameras have to communicate with each other to select the best camera. In [33], the authors presented an effi- cient camera-tasking approach to minimize the visual hull

area (maximal area that could be occupied by objects) for a given number of objects and cameras. They also presented several methods to select a subset of cameras based on the positions of the objects and cameras to min- imize the visual hull area. If the objects are recognized in the vicinity of a certain location, then a subset of cam- eras that is best suited to observe this location performs the tracking. This method is capable of selecting multi- ple cameras but not the desired number of cameras on average. In [34], the authors presented a framework for dynamically selecting a subset of cameras to track people in a VSN with limited network resources to achieve the best possible tracking performance. However, the camera selection decision is made at the FC based on training data and the selection is broadcast to the cameras in the VSN. Hence, this selection process does not depend on the true observations.

The observations received by the cameras in the VSN are typically realizations of a random variable. Hence, they contain a varying degree of information about the state of the object. They can be broadly classified into informative and uninformative observations. The non- informative observations do not contribute significantly to the tracking accuracy. Hence, a camera selection strat- egy that allows only a desired number of cameras with most informative observations to participate in the infor- mation exchange and discards the cameras with non- informative observations is an efficient way to meet the requirements of bandwidth and energy.

In [35], the authors presented an entropy-based algo- rithm that dynamically selects multiple cameras to reduce transmission errors and subsequently communication bandwidth. In this work, the cameras in the VSN use the extended information filter (EIF) as the local filter and calculate the expected information gain (EIG) in the form of a logarithmic ratio of the expected and posterior information matrices. If the information gain is greater than the cost of transmissions, then the cameras par- ticipate in the information fusion. The calculated EIG in this method does not depend on the measurements directly, and the cluster head has to run an optimiza- tion step to select the best possible cameras at each step. Moreover, this method is not capable of selecting only a desired number of cameras on average. In [36], a cam- era set is selected based on an individual image quality metric (IQM) for spherical objects. The cameras that detect the spherical target are ranked in ascending order based on their value of the local IQM, and the required number of cameras with highest IQM are chosen. This approach is limited to spherical objects. However, it can be easily extended to non-spherical objects. The major disadvantage of this method is either all the cameras in the VSN or the FC should know IQM of all the other cameras in the VSN. Hence, this method does not ensurecameras to take independent decisions thus restricting the scalability.

In our work, a multi-camera object tracking method based on the CIF is proposed in which the cameras can take independent decisions on whether or not to partici- pate in information exchange. Furthermore, the proposed method also ensures that on average, only a desired num- ber of cameras participate in the information exchange to meet bandwidth requirements. We model the state of an object utilizing a dynamic state representation that includes its position and velocity on the ground plane. Further, we consider a VSN with overlapping FOVs; thus, multiple cameras can observe an object simultaneously. Each camera in the VSN has a local CIF on board. Hence, they can calculate the local information metrics (infor- mation contribution vector and matrix) based on their observations. The cameras that can observe a specific object form a cluster (observation cluster) with an elected fusion center (FC). In this paper, we consider the concept of surprisal [37] to evaluate the amount of information in the observations received by the cameras in the VSN. The surprisal of the measurement residual indicates the amount of new information received from the corre- sponding observation. The observations of a camera are informative only if the corresponding surprisal of the mea- surement residual is greater than a threshold. The thresh- old is calculated as a function of the ratio of the number of desirable cameras and the total number of cameras in the observation cluster. This ensures that on average, only the desired number of cameras are selected as the cam- eras with informative observations (surprisal cameras). The surprisal cameras calculate the local information met- rics based on the CIF and transmit them to the FC. Then, the FC fuses the surprisal local information metrics to achieve the global state by using the inherent fusion mechanism of the CIF. The proposed selection mecha- nism only requires the knowledge of the total number of cameras in the observation cluster and the desired number of cameras. Further, we compare the proposed multi-camera object tracking method with surprisal cam- eras with multi-camera object tracking with random and fixed cameras using simulated and experimental data.

The paper is organized as follows: Section 2 describes the considered VSN with motion and observation mod- els. Section 3 presents theoretical concepts of information filtering. Section 4 describes the camera selection based on the surprisal of the measurement residual and the calculation of the surprisal threshold. Section 5 explains the proposed CIF-based multi-camera object tracking with surprisal cameras. Section 6 evaluates the pro- posed method based on simulation and experimental data. Finally, Section 7 presents the conclusions.


### 2. System model
In this work, we consider a VSN consisting of a fixed set
of calibrated smart cameras ci, where i ∈ {1, 2, · · · , M},
with overlapping FOVs as illustrated in Fig. 1. The task of
the cameras in the VSN is to monitor the given environ-
ment and to identify and track an object. As these cameras
are calibrated, there exists a homography to calculate the
object’s position on the ground plane. The cameras ci that
can observe the object at time k form the observation
cluster Ck. The state of the object comprises its position
(xk, yk) and the velocity (x ̇k, y ̇k) on the ground plane. Thus,
thestateattimekisdescribedasx =􏰀x y x ̇ y ̇􏰁T. k kkkk
The motion model of the object at camera ci at time k is given as
xk = fi,k xk−1, wi,k
⎡ δ2⎤
3.1 Time update
The information form of the predicted state and the cor- responding information matrix are computed as
−1
Yi,k|k−1 = Pi,k|k−1, (7)
􏰄yi,k|k−1 = Yi,k|k−1􏰄xi,k|k−1, (8) where 􏰄xi,k|k−1 and Pi,k|k−1 are the predicted state vector
and the error covariance matrix, respectively.
3.2 Measurement update
Upon receiving the measurement zi,k, the information contribution matrix Ii,k and information contribution vec- tor ii,k are computed as
xk−1 + δx ̇k−1 + 2 x ̈i,k ⎢y +δy ̇ +δ2y ̈ ⎥
 =⎢k−1 k−1 2i,k⎥, ⎣ x ̇ k − 1 + δ x ̈ i , k ⎦
(1)
 x ̇k−1 + δy ̈i,k
where x ̈ and y ̈ represent the acceleration of the object in x
and y directions that are modeled by the independent and
identically distributed (IID) white Gaussian noise vector
w = 􏰀x ̈ y ̈ 􏰁T with covariance Q = diag (qx , qy ). i,k i,k i,k i,k i i
δ is time interval between two observations. The state transition model (1) can be further written as
⎡10δ0⎤ ⎢ 0 1 0 δ ⎥
xk=⎣0010⎦xk−1+wsi,k, (2) 0001
Ii,k = Yi,k|k−1Pxz,i,kR−1PT YT , i,k xz,i,k i,k|k−1
ii,k = Yi,k|k−1Pxz,i,kR−1 􏰅i,k
(9)
(10)
where wsi,k is IID white Gaussian noise vector with
covariance⎡
qxiδ4 0 qxiδ3 0
⎢ ⎢ 4 qyiδ4 2 qyiδ3 Qs =⎢ 0 4 0 2 i,k ⎢⎣ qxiδ3 0 qxiδ2 0
3 qyiδ3
0 3 0 qyiδ
⎤ ⎥ ⎥
⎥. ⎥⎦
􏰆
  ei,k + PTxz,i,k􏰄yi,k|k−1
where Pxz,i,k , Ri,k , and ei,k are the cross-covariance of the
state and measurement vector, the measurement noise variance, and the measurement residual, respectively. The measurement residual is defined as
ei,k = zi,k −􏰄zi,k|k−1, (11)
where􏰄zi,k|k−1 is the predicted measurement. In this work, the CIF is used at the cameras to track the objects locally. We refer to Appendices 1 and 2 and [38] for the CIF algorithm.
3.3 Information fusion
In multi-camera networks, multiple cameras have an over- lapping FOV and thus can observe an object simultane- ously. Hence, each camera ci where i ∈ Ck that observes the object computes its own information contribution vector ii,k and information contribution matrix Ii,k as shown in (9) and (10), respectively. Let us consider that each camera sends their local information metrics to an elected FC, then the global information equivalents of the estimated state and error covariances at the FC co, where o ∈ Ck are calculated as
,
  (3)
 The state of the object is estimated from observations taken at each time step k. The observation model of the object at camera ci and time k is given as
zi,k = hi,k (xk) + vi,k, (4)
where vi,k is an IID measurement noise vector with covari- ance Ri,k . The measurement function hi,k is the non-linear homography function which converts the object’s coordi- nates from the ground to the image plane. The considered motion model (1) and measurement model (4) are adapted from [27].
3 Information filtering
The information filter is an alternative version of the Bayesian state estimation methods. In informa- tion filtering, the information vector and the infor- mation matrix are computed and propagated instead of the estimated state vector and the error covari- ance. The estimated global information matrix Yk−1|k−1 and information vector 􏰄yk−1|k−1 at time k − 1 are given as
where􏰄xk−1|k−1 and Pk−1|k−1 are the estimated global state vector and error covariance matrix at time k − 1. At time k and camera ci, the information filter has two steps: time and measurement update.
|C | k
Yk−1|k−1 = P−1 , k−1|k−1
Yk|k = Yo,k|k−1 + Ii,k, (12) i=1
(5) 􏰄y=Y􏰄x, (6)
|Ck | 􏰇
i=1
k−1|k−1 k−1|k−1 k−1|k−1
2
 􏰄yk|k =􏰄yo,k|k−1 +
ii,k, (13)
􏰇
where 􏰄yo,k|k−1 and Yo,k|k−1 are the predicted information vector and matrix at the FC, respectively.













