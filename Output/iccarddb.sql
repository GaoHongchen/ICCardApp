-- phpMyAdmin SQL Dump
-- version 4.1.14
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: Jun 26, 2016 at 10:54 AM
-- Server version: 5.6.17
-- PHP Version: 5.5.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `iccarddb`
--

-- --------------------------------------------------------

--
-- Table structure for table `tablechargestd`
--

CREATE TABLE IF NOT EXISTS `tablechargestd` (
  `楼层下限` int(11) NOT NULL,
  `楼层上限` int(11) NOT NULL,
  `单次收费` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `tablelift`
--

CREATE TABLE IF NOT EXISTS `tablelift` (
  `电梯编号` int(11) NOT NULL AUTO_INCREMENT,
  `电梯名称` text NOT NULL,
  `电梯类型` text NOT NULL,
  `总楼层数` int(11) NOT NULL,
  `起始楼层` int(11) NOT NULL,
  `公用楼层` int(11) NOT NULL,
  `电梯数量` int(11) NOT NULL,
  `备注` text NOT NULL,
  PRIMARY KEY (`电梯编号`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=6 ;

--
-- Dumping data for table `tablelift`
--

INSERT INTO `tablelift` (`电梯编号`, `电梯名称`, `电梯类型`, `总楼层数`, `起始楼层`, `公用楼层`, `电梯数量`, `备注`) VALUES
(1, 'dadf', '贯通门电梯', 5, 1, 0, 2, 'ertr'),
(2, 'qwer', '普通电梯', 9, 1, 0, 1, ''),
(3, '金顶阳光', '普通电梯', 12, 1, 0, 2, ''),
(4, 'asdf', '贯通门电梯', 8, 1, 0, 2, 'qw'),
(5, '海特', '普通电梯', 20, 1, 0, 2, '123qw');

-- --------------------------------------------------------

--
-- Table structure for table `tablesysswitchcard`
--

CREATE TABLE IF NOT EXISTS `tablesysswitchcard` (
  `卡号` text NOT NULL,
  `卡类型` text NOT NULL,
  `是否为补办卡` text NOT NULL,
  `第几次补办` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `tableuserinfo`
--

CREATE TABLE IF NOT EXISTS `tableuserinfo` (
  `用户名` text NOT NULL,
  `用户级别` text NOT NULL,
  `密码` text NOT NULL,
  `充值上限` int(11) NOT NULL,
  `密码问题` text NOT NULL,
  `密码问题答案` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `tableuserinfo`
--

INSERT INTO `tableuserinfo` (`用户名`, `用户级别`, `密码`, `充值上限`, `密码问题`, `密码问题答案`) VALUES
('a', '普通用户', '123', 100, '您高中学校的名字？', '禹城一中'),
('abc', '系统管理员', '123456', 200, '您父亲的名字？', '高玉爱'),
('b', '普通用户', '123', 300, '您大学辅导员的名字？', '王男'),
('c', '普通用户', '123', 500, '您大学的名字？', '燕山大学'),
('高洪臣', '系统管理员', '123456', 1000, '您大学的名字？', '燕山大学');

-- --------------------------------------------------------

--
-- Table structure for table `tableusrcard`
--

CREATE TABLE IF NOT EXISTS `tableusrcard` (
  `卡号` text NOT NULL,
  `业主姓名` text NOT NULL,
  `业主门牌` text NOT NULL,
  `联系电话` text NOT NULL,
  `限制日期` text NOT NULL,
  `可用电梯` text NOT NULL,
  `可用楼层` text NOT NULL,
  `房间编号` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `tableusrcard`
--

INSERT INTO `tableusrcard` (`卡号`, `业主姓名`, `业主门牌`, `联系电话`, `限制日期`, `可用电梯`, `可用楼层`, `房间编号`) VALUES
('00001', '张三', '022', '18244532213', '2016.06.19-2016.06.19', '1', 'A门：2,4,5;', '0805'),
('00002', '李四', '012', '18244532213', '2016.06.19-2016.06.19', '2', 'A门：1,3,4,6;', '0401'),
('10003', 'qwe', '1234', '12645238961', '2015.06.19-2020.06.19', '4', 'A门：1,3,5,7,8;', '0110'),
('00006', 'ghc', '126', '18265432150', '2016.06.19-2025.06.19', '5', 'A门：1,4,5,7,8,10,11,12,13,14,15,18,20;', '0215');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
