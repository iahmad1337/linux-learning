# systemd

Articles:
- https://www.sobyte.net/post/2022-09/systemd-and-cgroup

# Quick rundown

- *service*: denotes a background service process managed by systemd, such as
  docker, and is the most commonly used unit type.
- *target*: represents a logical grouping of other units, where the user can
  control a group of units through a target. systemd predefines a large number
  of targets, such as multi-user.target.
- *scope*: External process created by systemd-run or by calling the systemd
  interface.
- *slice*: Represents a set of scope/service. systemd maps a node in the cgroup
  Hierarchy via slice.
- *socket*: encapsulates a socket, each socket unit has a corresponding service
  unit.
- *device*: Encapsulates a Linux device.
- *mount*: encapsulates a mount point of the file system, systemd will monitor and
  manage the mount point, such as starting an automount, etc.
- *automount*: Similar to the mount unit, systemd automatically performs mount
  actions when the mount point is accessed.
- *swap*: Similar to mount unit, but manages swap.
- *timer*: Timed task configuration, replaces crond
- *snapshot*: The snapshot unit manages a set of configuration units that hold the
  current operational state of the system.
- *path*: A file or directory on the system.


