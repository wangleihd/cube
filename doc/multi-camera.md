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

通常，跟踪算法的性能受到不同的不利影响，例如相机的距离或取向以及遮挡。 然而，具有重叠视场（FOV）的VSN能够同时提供对同一对象的多个观察。 [25]中的作者提出了一种分布式和协作感知机制，通过动态改变摄像机的摇摄，倾斜和变焦来提高物体的可观察性。 [26]和[27]中介绍了分布式目标跟踪方法的其他示例。

Recently, information filters have emerged as suitable methods for multi-sensor state estimation [28]. In infor- mation filtering, the information vector and matrix are computed and propagated over time instead of the state vector and its error covariance. The information matrix is the inverse of the state error covariance matrix. The infor- mation vector is the product of the information matrix and state vector. The information filters have an inher- ent information fusion mechanism which makes them more suitable for multi-camera object tracking. A more detailed description of information filters is given in Section 3. The authors in [29] and [30] presented informa- tion weighted consensus-based distributed object track- ing with an underlying KF or a distributed maximum likelihood estimation. In our work [31], we have pre- sented a robust cubature information filter (CIF)-based distributed object tracking in VSNs. However, the limited processing, communication, and energy capabilities of the cameras in a VSN present a major challenge.

最近，信息过滤器已成为多传感器状态估计的合适方法[28]。在信息过滤中，信息向量和矩阵随时间计算和传播，而不是状态向量及其误差协方差。信息矩阵是状态误差协方差矩阵的逆。信息向量是信息矩阵和状态向量的乘积。信息过滤器具有可靠的信息融合机制，使其更适合多摄像机对象跟踪。第3节给出了信息过滤器的更详细描述。[29]和[30]中的作者提出了基于信息加权共识的分布式对象跟踪以及基础KF或分布式最大似然估计。在我们的工作[31]中，我们在VSN中提出了一种基于稳健的立方体信息过滤器（CIF）的分布式对象跟踪。然而，VSN中相机的有限处理，通信和能量能力是一项重大挑战。


Nowadays, VSNs tend to evolve into large-scale net- works with limited bandwidth and energy reservoirs. This allows a large number of cameras to observe a single object. In spite of the improved tracking accuracy, the information exchange of the large number of observations among the cameras increases the communication over- head and energy consumption. Hence, allowing only a desired number of cameras to participate in the informa- tion exchange is a way to meet the stringent requirements of bandwidth and energy.

如今，VSN倾向于演变成具有有限带宽和能量储存的大规模网络。 这允许大量相机观察单个物体。 尽管跟踪精度有所提高，但摄像机之间大量观测的信息交换增加了通信开销和能耗。 因此，仅允许所需数量的摄像机参与信息交换是满足带宽和能量的严格要求的一种方式。

Estimating an object’s state with a selected set of cam- eras is a well-investigated topic. Several camera selection mechanisms have been proposed in literature to minimize and/or maximize different metrics such as estimation accuracy, monitoring area, number of transmissions, and amount of data transfer. In [32], the authors presented an object tracking method based on fuzzy automaton in handing over to expand the monitoring area. This method selects a single best camera to control and track the objects by comparing its rank with the neighboring cam- eras. This method fails to select multiple cameras, and cameras have to communicate with each other to select the best camera. In [33], the authors presented an effi- cient camera-tasking approach to minimize the visual hull area (maximal area that could be occupied by objects) for a given number of objects and cameras. They also presented several methods to select a subset of cameras based on the positions of the objects and cameras to min- imize the visual hull area. If the objects are recognized in the vicinity of a certain location, then a subset of cam- eras that is best suited to observe this location performs the tracking. This method is capable of selecting multi- ple cameras but not the desired number of cameras on average. In [34], the authors presented a framework for dynamically selecting a subset of cameras to track people in a VSN with limited network resources to achieve the best possible tracking performance. However, the camera selection decision is made at the FC based on training data and the selection is broadcast to the cameras in the VSN. Hence, this selection process does not depend on the true observations.

使用一组选定的摄像机估计对象的状态是一个经过深入研究的主题。在文献中已经提出了几种相机选择机制，以最小化和/或最大化不同的度量，例如估计精度，监视区域，传输次数和数据传输量。在[32]中，作者提出了一种基于模糊自动机的目标跟踪方法，用于交接扩展监控区域。此方法通过将其等级与相邻摄像机进行比较，选择单个最佳摄像机来控制和跟踪对象。该方法无法选择多个摄像机，摄像机必须相互通信才能选择最佳摄像机。在[33]中，作者提出了一种有效的摄像机任务方法，以最大限度地减少给定数量的物体和摄像机的视觉船体区域（可被物体占据的最大区域）。他们还提出了几种基于物体和摄像机位置选择摄像机子集的方法，以最小化视觉船体区域。如果在某个位置附近识别出物体，则最适合观察该位置的摄像机子集执行跟踪。此方法能够选择多个摄像机，但平均不能选择所需数量的摄像机。在[34]中，作者提出了一个框架，用于动态选择摄像机子集，以跟踪具有有限网络资源的VSN中的人，以实现最佳的跟踪性能。然而，基于训练数据在FC处进行摄像机选择决定，并且将选择广播到VSN中的摄像机。因此，这种选择过程不依赖于真实的观察结果。

The observations received by the cameras in the VSN are typically realizations of a random variable. Hence, they contain a varying degree of information about the state of the object. They can be broadly classified into informative and uninformative observations. The non- informative observations do not contribute significantly to the tracking accuracy. Hence, a camera selection strat- egy that allows only a desired number of cameras with most informative observations to participate in the infor- mation exchange and discards the cameras with non- informative observations is an efficient way to meet the requirements of bandwidth and energy.

VSN中的摄像机接收的观察结果通常是随机变量的实现。 因此，它们包含关于对象状态的不同程度的信息。 它们可以大致分为信息性和无信息性的观察。 非信息性观察对跟踪精度没有显着贡献。 因此，摄像机选择策略只允许所需数量的具有最丰富信息的观测摄像机参与信息交换，并通过非信息观测丢弃摄像机，这是满足带宽和能量要求的有效方式。

In [35], the authors presented an entropy-based algo- rithm that dynamically selects multiple cameras to reduce transmission errors and subsequently communication bandwidth. In this work, the cameras in the VSN use the extended information filter (EIF) as the local filter and calculate the expected information gain (EIG) in the form of a logarithmic ratio of the expected and posterior information matrices. If the information gain is greater than the cost of transmissions, then the cameras par- ticipate in the information fusion. The calculated EIG in this method does not depend on the measurements directly, and the cluster head has to run an optimiza- tion step to select the best possible cameras at each step. Moreover, this method is not capable of selecting only a desired number of cameras on average. In [36], a cam- era set is selected based on an individual image quality metric (IQM) for spherical objects. The cameras that detect the spherical target are ranked in ascending order based on their value of the local IQM, and the required number of cameras with highest IQM are chosen. This approach is limited to spherical objects. However, it can be easily extended to non-spherical objects. The major disadvantage of this method is either all the cameras in the VSN or the FC should know IQM of all the other cameras in the VSN. Hence, this method does not ensurecameras to take independent decisions thus restricting the scalability.

在[35]中，作者提出了一种基于熵的算法，可以动态选择多个摄像机，以减少传输错误和随后的通信带宽。在这项工作中，VSN中的摄像机使用扩展信息滤波器（EIF）作为局部滤波器，并以预期信息矩阵和后验信息矩阵的对数比的形式计算预期信息增益（EIG）。如果信息增益大于传输成本，则摄像机参与信息融合。此方法中计算的EIG不直接依赖于测量值，并且簇头必须运行优化步骤以在每个步骤中选择最佳可能的摄像机。而且，该方法不能平均仅选择所需数量的摄像机。在[36]中，基于球形物体的单个图像质量度量（IQM）选择摄像机组。检测球形目标的摄像机根据其局部IQM的值按升序排列，并选择所需的具有最高IQM的摄像机数量。这种方法仅限于球形物体。但是，它可以很容易地扩展到非球形物体。这种方法的主要缺点是VSN中的所有摄像机或FC都应该知道VSN中所有其他摄像机的IQM。因此，该方法不能确保摄像机采取独立决策，从而限制了可伸缩性。


In our work, a multi-camera object tracking method based on the CIF is proposed in which the cameras can take independent decisions on whether or not to partici- pate in information exchange. Furthermore, the proposed method also ensures that on average, only a desired num- ber of cameras participate in the information exchange to meet bandwidth requirements. We model the state of an object utilizing a dynamic state representation that includes its position and velocity on the ground plane. Further, we consider a VSN with overlapping FOVs; thus, multiple cameras can observe an object simultaneously. Each camera in the VSN has a local CIF on board. Hence, they can calculate the local information metrics (infor- mation contribution vector and matrix) based on their observations. The cameras that can observe a specific object form a cluster (observation cluster) with an elected fusion center (FC). In this paper, we consider the concept of surprisal [37] to evaluate the amount of information in the observations received by the cameras in the VSN. The surprisal of the measurement residual indicates the amount of new information received from the corre- sponding observation. The observations of a camera are informative only if the corresponding surprisal of the mea- surement residual is greater than a threshold. The thresh- old is calculated as a function of the ratio of the number of desirable cameras and the total number of cameras in the observation cluster. This ensures that on average, only the desired number of cameras are selected as the cam- eras with informative observations (surprisal cameras). The surprisal cameras calculate the local information met- rics based on the CIF and transmit them to the FC. Then, the FC fuses the surprisal local information metrics to achieve the global state by using the inherent fusion mechanism of the CIF. The proposed selection mecha- nism only requires the knowledge of the total number of cameras in the observation cluster and the desired number of cameras. Further, we compare the proposed multi-camera object tracking method with surprisal cam- eras with multi-camera object tracking with random and fixed cameras using simulated and experimental data.

在我们的工作中，提出了一种基于CIF的多摄像机目标跟踪方法，其中摄像机可以独立决定是否参与信息交换。此外，所提出的方法还确保平均而言，只有期望数量的摄像机参与信息交换以满足带宽要求。我们利用动态状态表示来模拟对象的状态，该动态状态表示包括其在地平面上的位置和速度。此外，我们考虑具有重叠FOV的VSN;因此，多个摄像机可以同时观察物体。 VSN中的每个摄像头都有一个本地CIF。因此，他们可以根据观察结果计算局部信息度量（信息贡献向量和矩阵）。可以观察特定物体的相机形成具有选定的融合中心（FC）的群集（观察群集）。在本文中，我们考虑了惊人的概念[37]来评估VSN中摄像机收到的观测中的信息量。测量残差的惊人数据表明从相应的观察中收到的新信息量。只有当测量残差的相应惊人值大于阈值时，摄像机的观测才能提供信息。阈值是根据所需摄像机数量与观测组中摄像机总数之比的函数计算的。这确保了平均而言，仅选择所需数量的摄像机作为具有信息观察的摄像机（惊人的摄像机）。令人惊讶的摄像机根据CIF计算本地信息记录并将其传输到FC。然后，FC通过使用CIF的固有融合机制来融合惊人的本地信息度量以实现全局状态。建议的选择机制只需要知道观测组中摄像机的总数和所需的摄像机数量。此外，我们将提出的多相机物体跟踪方法与具有多相机物体跟踪的惊人相机与使用模拟和实验数据的随机和固定相机进行比较。

The paper is organized as follows: Section 2 describes the considered VSN with motion and observation mod- els. Section 3 presents theoretical concepts of information filtering. Section 4 describes the camera selection based on the surprisal of the measurement residual and the calculation of the surprisal threshold. Section 5 explains the proposed CIF-based multi-camera object tracking with surprisal cameras. Section 6 evaluates the pro- posed method based on simulation and experimental data. Finally, Section 7 presents the conclusions.


本文的结构如下：第2节描述了所考虑的具有运动和观察模型的VSN。 第3节介绍了信息过滤的理论概念。 第4节描述了基于测量残差的惊人度和惊人阈值的计算的摄像机选择。 第5节解释了提出的基于CIF的多相机物体跟踪与惊人的相机。 第6节基于模拟和实验数据评估了提出的方法。 最后，第7节提出了结论。

### 2. System model
In this work, we consider a VSN consisting of a fixed set
of calibrated smart cameras ci, where i ∈ {1, 2, · · · , M},
with overlapping FOVs as illustrated in Fig. 1. The task of
the cameras in the VSN is to monitor the given environ-
ment and to identify and track an object. As these cameras
are calibrated, there exists a homography to calculate the
object’s position on the ground plane. The cameras ci that
can observe the object at time k form the observation
cluster Ck. 

在这项工作中，我们考虑一个由固定集组成的VSN
校准的智能相机ci，其中i∈{1,2，...，M}，
具有重叠的FOV，如图1所示
VSN中的摄像头用于监控给定的环境
识别和跟踪对象。 作为这些相机
校准后，存在单应性来计算
物体在地平面上的位置。 相机ci
可以在时间k观察物体观察
集群Ck。


#### 3.1 Time update
The information form of the predicted state and the cor- responding information matrix are computed as
−1
Yi,k|k−1 = Pi,k|k−1, (7)
􏰄yi,k|k−1 = Yi,k|k−1􏰄xi,k|k−1, (8) where 􏰄xi,k|k−1 and Pi,k|k−1 are the predicted state vector
and the error covariance matrix, respectively.


#### 3.2 Measurement update
Upon receiving the measurement zi,k, the information contribution matrix Ii,k and information contribution vec- tor ii,k are computed as

where x ̈ and y ̈ represent the acceleration of the object in x
and y directions that are modeled by the independent and
identically distributed (IID) white Gaussian noise vector

where Pxz,i,k , Ri,k , and ei,k are the cross-covariance of the
state and measurement vector, the measurement noise variance, and the measurement residual, respectively. The measurement residual is defined as


where􏰄zi,k|k−1 is the predicted measurement. In this work, the CIF is used at the cameras to track the objects locally. We refer to Appendices 1 and 2 and [38] for the CIF algorithm.

#### 3.3 Information fusion
In multi-camera networks, multiple cameras have an over- lapping FOV and thus can observe an object simultane- ously. Hence, each camera ci where i ∈ Ck that observes the object computes its own information contribution vector ii,k and information contribution matrix Ii,k as shown in (9) and (10), respectively. Let us consider that each camera sends their local information metrics to an elected FC, then the global information equivalents of the estimated state and error covariances at the FC co, where o ∈ Ck are calculated as

在多摄像机网络中，多个摄像机具有重叠的FOV，因此可以同时观察物体。 因此，观察对象的i∈Ck的每个相机ci分别计算其自身的信息贡献矢量ii，k和信息贡献矩阵Ii，k，如（9）和（10）所示。 让我们考虑每个摄像机将其本地信息度量发送到选定的FC，然后是FC co处的估计状态和误差协方差的全局信息等价，其中o∈Ck被计算为


 
The state of the object is estimated from observations taken at each time step k. The observation model of the object at camera ci and time k is given as

根据在每个时间步k获得的观察来估计对象的状态。 摄像机ci和时间k的物体观测模型如下
 

where vi,k is an IID measurement noise vector with covari- ance Ri,k . The measurement function hi,k is the non-linear homography function which converts the object’s coordi- nates from the ground to the image plane. The considered motion model (1) and measurement model (4) are adapted from [27].

其中vi，k是具有协方差Ri，k的IID测量噪声向量。 测量函数hi，k是非线性单应函数，它将对象的坐标从地面转换为图像平面。 考虑的运动模型（1）和测量模型（4）改编自[27]。

### 3 Information filtering
The information filter is an alternative version of the Bayesian state estimation methods. In informa- tion filtering, the information vector and the infor- mation matrix are computed and propagated instead of the estimated state vector and the error covari- ance. The estimated global information matrix Yk−1|k−1 and information vector yk−1|k−1 at time k − 1 are given as

信息过滤器是贝叶斯状态估计方法的替代版本。 在信息过滤中，信息向量和信息矩阵被计算和传播，而不是估计的状态向量和误差协方差。 在时刻k-1的估计全局信息矩阵Yk-1 | k-1和信息矢量yk-1 | k-1被给出为

where xk−1|k−1 and Pk−1|k−1 are the estimated global state vector and error covariance matrix at time k − 1. At time k and camera ci, the information filter has two steps: time and measurement update.

其中xk-1 | k-1和Pk-1 | k-1是在时间k-1估计的全局状态向量和误差协方差矩阵。在时间k和摄像机ci，信息过滤器有两个步骤：时间和测量更新。












